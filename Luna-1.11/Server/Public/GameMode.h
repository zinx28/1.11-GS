#pragma once
#include "..\framework.h"
#include "Inventory.h"
#include "Player.h"
#include "Looting.h"

static UNetDriver* (*CreateNetDriver)(UEngine* Engine, UWorld*, FName NetDriverDefinition) = decltype(CreateNetDriver)(ImageBase + 0x1D0CB60);
static bool (*InitListen)(UNetDriver* IpNetDriver, UWorld* InNotify, FURL& LocalURL, bool bReuseAddressAndPort, FString& Error) = decltype(InitListen)(ImageBase + 0x2A72B50);
static void (*SetWorld)(UNetDriver* Driver, UWorld* World) = decltype(SetWorld)(ImageBase + 0x1AEFA50);

namespace GameMode {
	static bool bWorldisReady = false;
	inline bool (*ReadyToStartMatch_OG)(AFortGameModeAthena* GameMode);
	inline bool ReadyToStartMatch(AFortGameModeAthena* GameMode) {
		auto GameState = (AFortGameStateAthena*)GameMode->GameState;

		if (!GameState->MapInfo) return false;

		if (GameMode->NumTeams <= 0) return false;

		if (GameState->TeamCount <= 0) return false;

		if (GameState->Teams.Num() <= 0) return false;

		if (GameState->TeamSize <= 0) return false;

		if (!bWorldisReady) {

			FName GameNetDriver = FName(282);
			UNetDriver* NetDriver = CreateNetDriver(UEngine::GetEngine(), UWorld::GetWorld(), GameNetDriver);
			NetDriver->NetDriverName = GameNetDriver;

			FURL URL{};
			URL.Port = 7777;

			FString Error;

			if (!InitListen(NetDriver, UWorld::GetWorld(), URL, false, Error)) {
				std::cout << "Failed To Listen: " << Error.ToString() << std::endl;
				return false;
			}

			SetWorld(NetDriver, UWorld::GetWorld());

			UWorld::GetWorld()->NetDriver = NetDriver;

			for (auto& LC : UWorld::GetWorld()->LevelCollections) {
				LC.NetDriver = NetDriver;
			}

			GameMode->bWorldIsReady = true;

			GameMode->CurrentPlaylistId = 10;

			if (!GameMode->GameSession) GameMode->GameSession = SpawnActor<AFortGameSession>();
			GameMode->GameSession->MaxPlayers = 100;

			GameMode->StartMatch();
			GameMode->StartPlay();

			EAthenaGamePhase OldGp = GameState->GamePhase;
			GameState->GamePhase = EAthenaGamePhase::Warmup;

			GameState->OnRep_GamePhase(OldGp);

			SetConsoleTitleA("Luna || Started Listening");


			TArray<AActor*> WarmupActors;
			static UClass* WarmupClass = StaticLoadObject<UClass>("/Game/Athena/Environments/Blueprints/Tiered_Athena_FloorLoot_Warmup.Tiered_Athena_FloorLoot_Warmup_C");
			UGameplayStatics::GetAllActorsOfClass(UWorld::GetWorld(), WarmupClass, &WarmupActors);

			for (int i = 0; i < WarmupActors.Num(); i++) {
				ABuildingContainer*& Container = (ABuildingContainer*&)WarmupActors[i];
				auto Entrys = Looting::PickLootDrops(Container->SearchLootTierGroup);
				FVector CurrentLoc = Container->K2_GetActorLocation();
				CurrentLoc.Z += 50;
				for (auto& item : Entrys) {
					if(item.Count > 0)
						Inventory::SpawnPickup(item.ItemDefinition, CurrentLoc, item.Count);
				}
				Container->K2_DestroyActor();
			}
			WarmupActors.Clear(); // we are meant to free

			TArray<AActor*> FloorLootActors;
			static UClass* FloorlootClass = StaticLoadObject<UClass>("/Game/Athena/Environments/Blueprints/Tiered_Athena_FloorLoot_01.Tiered_Athena_FloorLoot_01_C");
			UGameplayStatics::GetAllActorsOfClass(UWorld::GetWorld(), FloorlootClass, &FloorLootActors);

			for (int i = 0; i < FloorLootActors.Num(); i++) {
				ABuildingContainer*& Container = (ABuildingContainer*&)FloorLootActors[i];
				auto Entrys = Looting::PickLootDrops(Container->SearchLootTierGroup);
				FVector CurrentLoc = Container->K2_GetActorLocation();
				CurrentLoc.Z += 50;
				for (auto& item : Entrys) {
					if (item.Count > 0)
						Inventory::SpawnPickup(item.ItemDefinition, CurrentLoc, item.Count);
				}
				Container->K2_DestroyActor();
			}
			FloorLootActors.Clear();

			bWorldisReady = true;
		}

		bool Ret = ReadyToStartMatch_OG(GameMode);

		return Ret;
	}

	inline APawn* SpawnDefaultPawnFor(AFortGameModeAthena* GameMode, AFortPlayerControllerAthena* Controller, AActor* StartSpot) {

		auto P = (AFortPlayerPawnAthena*)GameMode->SpawnDefaultPawnAtTransform(Controller, StartSpot->GetTransform());

		auto PlayerState = (AFortPlayerStateAthena*)Controller->PlayerState;

		// pretty sure this gets called every time a user respawns...
		Controller->WorldInventory->Inventory.ReplicatedEntries.Clear();
		Controller->WorldInventory->Inventory.ItemInstances.Clear();

		AFortQuickBars* QuickBars = SpawnActor<AFortQuickBars>(Controller);
		QuickBars->SetOwner(Controller);

		Controller->QuickBars = QuickBars;

		Inventory::Update(Controller);

		// Now we clear the quickbars since its not auto in season 1.11


		//instead of writing an essay bro just tell me it dont work
		/*for (auto& Slot : Controller->QuickBars->PrimaryQuickBar.Slots)
		{
			if (Slot.Items.Data != nullptr)
			{
				for (auto& Item : Slot.Items)
				{
					FFortItemEntry Entry = Inventory::GetEntryInInv(Controller, Item);
					Inventory::RemoveItem(Controller, Entry.ItemGuid, false, Entry.Count);
				}
			}
		}

		for (auto& Slot2 : Controller->QuickBars->SecondaryQuickBar.Slots)
		{
			if (Slot2.Items.Data != nullptr)
			{
				for (auto& Item : Slot2.Items)
				{
					FFortItemEntry Entry = Inventory::GetEntryInInv(Controller, Item);
					Inventory::RemoveItem(Controller, Entry.ItemGuid, false, Entry.Count);
				}
			}
		}*/
	


		//for (int i = 0; i < Controller->WorldInventory->Inventory.ItemInstances.Num(); i++) {
		//	UFortWorldItem* Item = Controller->WorldInventory->Inventory.ItemInstances[i];
		//	if (Item) {
		//		//if (Item->CanBeDropped()) {
		//		if(!Item->ItemEntry.ItemDefinition->IsA(UFortBuildingItemDefinition::StaticClass()))
		//			Inventory::RemoveItem(Controller, Item->GetItemGuid(), false);
		//		//}
		//	}
		//}
		
		//RemoveItem
	/*	for (int i = 0; i < Controller->QuickBars->PrimaryQuickBar.Slots.Num(); i++) {
			Controller->QuickBars->PrimaryQuickBar.Slots[i].Items.Data = nullptr;
			Controller->QuickBars->PrimaryQuickBar.Slots[i].Items.Clear();
		}
		for (int i = 0; i < Controller->QuickBars->SecondaryQuickBar.Slots.Num(); i++) {
			Controller->QuickBars->SecondaryQuickBar.Slots[i].Items.Data = nullptr;
			Controller->QuickBars->SecondaryQuickBar.Slots[i].Items.Clear();
		}*/
		
		//Controller->WorldInventory->Inventory.ReplicatedEntries[0].ItemDefinition.

		FFortAthenaLoadout Loadout = GetLoadout(Controller);

		for (auto& StartingItem : GameMode->StartingItems) {
			if (StartingItem.Count > 0) // i swear bc it's adding blanks
				Inventory::GiveItem(Controller, StartingItem.Item, StartingItem.Count);
		}
		// give pickaxe last?!?!
		Inventory::GiveItem(Controller, Loadout.Pickaxe->WeaponDefinition, 1, -1, true);
		
		// might not the needed
		Controller->ServerExecuteInventoryItem(Inventory::GetItemInSlot(Controller, 0));
		
		EquipSkin(Controller);

		return P;
	}

	inline void (*HandleStartingNewPlayer_OG)(AFortGameModeAthena* GameMode, AFortPlayerControllerAthena* Controller);
	inline void HandleStartingNewPlayer(AFortGameModeAthena* GameMode, AFortPlayerControllerAthena* Controller) {
		HandleStartingNewPlayer_OG(GameMode, Controller);

		UNetConnection* Connection = Controller->NetConnection;

		auto PlayerState = (AFortPlayerStateAthena*)Controller->PlayerState;

		PlayerState->WorldPlayerId = PlayerState->PlayerID;

		uint8_t TeamIndex = (uint8)PlayerState->TeamIndex;

		PlayerState->SquadId = TeamIndex - 3;
		PlayerState->OnRep_SquadId();

		AFortInventory* Inventory = SpawnActor<AFortInventory>(Controller);
		Inventory->InventoryType = EFortInventoryType::World;
		Inventory->Inventory = FFortItemList();
		Inventory->Inventory.ItemInstances = TArray<UFortWorldItem*>();
		Inventory->Inventory.ReplicatedEntries = TArray<FFortItemEntry>();
		Inventory->SetOwner(Controller);

		Controller->WorldInventory = Inventory;

		AFortQuickBars* QuickBars = SpawnActor<AFortQuickBars>(Controller);

		QuickBars->SetOwner(Controller);

		Controller->QuickBars = QuickBars;

		Controller->OverriddenBackpackSize = 5;

		Controller->bHasInitializedWorldInventory = true;
		Controller->HandleWorldInventoryLocalUpdate();
		Controller->WorldInventory->HandleInventoryLocalUpdate();
		Controller->OnRep_QuickBar();

		Controller->WorldInventory->Inventory.MarkArrayDirty();

		Controller->bHasClientFinishedLoading = true;
		Controller->bHasServerFinishedLoading = true;
		Controller->OnRep_bHasServerFinishedLoading();

		if (!Controller->MatchReport)
		{
			Controller->MatchReport = (UAthenaPlayerMatchReport*)UGameplayStatics::SpawnObject(UAthenaPlayerMatchReport::StaticClass(), Controller);
		}
	}
}