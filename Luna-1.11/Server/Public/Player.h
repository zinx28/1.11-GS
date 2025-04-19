#pragma once
#include "../framework.h"
#include "Abilities.h"
#include "Looting.h"
#include "Inventory.h"
//7FF765C5D510 - 7FF7657A0000
static ABuildingSMActor* (*ReplaceBuildingActor)(ABuildingSMActor* a1,
	unsigned int a2,
	TSubclassOf<ABuildingSMActor> a3,
	unsigned int a4,
	int a5,
	unsigned __int8 a6,
	AFortPlayerControllerAthena* a7) = decltype(ReplaceBuildingActor)(ImageBase + 0x4BD510);

UAthenaCharacterItemDefinition* GetRandomDefault(int* OutIdx = nullptr) {
	int Num = (rand() % 8);
	const char* Gender = (Num > 4) ? "M" : "F";
	std::string String = std::format("AthenaCharacterItemDefinition CID_00{}_Athena_Commando_{}_Default.CID_00{}_Athena_Commando_{}_Default", Num, Gender, Num, Gender);

	if (OutIdx) *OutIdx = Num;
	return UObject::FindObject< UAthenaCharacterItemDefinition>(String);
}
FRichCurve* (*FindCurve)(UObject* thisPtr, FName a2, FString& a3, char a4) = decltype(FindCurve)(ImageBase + 0x2E21D0);

UFortResourceItemDefinition* GetResourceItemDef(EFortResourceType Type)
{
	static auto WoodItemDef = UObject::FindObject<UFortResourceItemDefinition>("FortResourceItemDefinition WoodItemData.WoodItemData");
	static auto StoneItemDef = UObject::FindObject<UFortResourceItemDefinition>("FortResourceItemDefinition StoneItemData.StoneItemData");
	static auto MetalItemDef = UObject::FindObject<UFortResourceItemDefinition>("FortResourceItemDefinition MetalItemData.MetalItemData");

	UFortResourceItemDefinition* ResourceItem = nullptr;

	switch (Type)
	{
	case EFortResourceType::Wood:
		ResourceItem = WoodItemDef;
		break;
	case EFortResourceType::Stone:
		ResourceItem = StoneItemDef;
		break;
	case EFortResourceType::Metal:
		ResourceItem = MetalItemDef;
		break;
	}

	return ResourceItem;
}

void (*OnDamageServer_OG)(ABuildingContainer* Container, float Damage, const struct FGameplayTagContainer& DamageTags, const struct FVector& Momentum, const struct FHitResult& HitInfo, class AController* InstigatedBy, class AActor* DamageCauser, const struct FGameplayEffectContextHandle& EffectContext);
void OnDamageServer(ABuildingContainer* Container, float Damage, const struct FGameplayTagContainer& DamageTags, const struct FVector& Momentum, const struct FHitResult& HitInfo, class AFortPlayerControllerAthena* InstigatedBy, class AActor* DamageCauser, const struct FGameplayEffectContextHandle& EffectContext)
{
	// some objects crashes gs bc it thinks theres damage?!?!?! it's weird asf
	bool bWeakpoint = Damage == 100.f;

	if (InstigatedBy && InstigatedBy->IsA(AFortPlayerControllerAthena::StaticClass()) && !Container->bPlayerPlaced)
	{
		if(Damage > 0) {
			// let me like uhhhhhh pickaxe with my gun
			
			UFortWeaponMeleeItemDefinition* PickaxeDefinition = InstigatedBy->CustomizationLoadout.Pickaxe->WeaponDefinition;
			if (DamageCauser->IsA(AFortWeapon::StaticClass())) {
				AFortWeapon* Weapon = (AFortWeapon*)DamageCauser;
				if (InstigatedBy->MyFortPawn && InstigatedBy->MyFortPawn->CurrentWeapon && Weapon->WeaponData == PickaxeDefinition)
				{
					UCurveTable* DataTable = Container->BuildingResourceAmountOverride.CurveTable;
					FName RowName = Container->BuildingResourceAmountOverride.RowName;

					FString a3;
					if (DataTable)
					{
						auto Curve = FindCurve(DataTable, RowName, a3, true);
						float Value = Curve->Keys[0].Value;
						float DividedHealth = Container->GetMaxHealth() / Damage;
						float OverallCount = round(Value / DividedHealth);

						auto ResourceItem = GetResourceItemDef(Container->ResourceType);

						if (OverallCount > 0) {
							InstigatedBy->ClientReportDamagedResourceBuilding(Container, Container->ResourceType, OverallCount, Container->bDestroyed, bWeakpoint);
							Inventory::GiveItem(InstigatedBy, ResourceItem, OverallCount, -1, -1);
						}
					}
				}
			}
		}
	}

	if (Container->GetHealth() <= 0) {
		Container->K2_DestroyActor(); // some items doesnt break....
	}


	return OnDamageServer_OG(Container, Damage, DamageTags, Momentum, HitInfo, InstigatedBy, DamageCauser, EffectContext);
}

FFortAthenaLoadout GetLoadout(AFortPlayerControllerAthena* Controller) {
	if (Controller) {
		AFortPlayerPawnAthena* Pawn = (AFortPlayerPawnAthena*)Controller->Pawn;
		if (Controller->CustomizationLoadout.Pickaxe && Controller->CustomizationLoadout.Character) {
			return Controller->CustomizationLoadout;
		}
		else if (Pawn && Pawn->CustomizationLoadout.Pickaxe && Pawn->CustomizationLoadout.Character) {
			return Pawn->CustomizationLoadout;
		}
	}
	static FFortAthenaLoadout Ret;
	if (!Ret.Glider) Ret.Glider = UObject::FindObject<UAthenaGliderItemDefinition>("AthenaGliderItemDefinition DefaultGlider.DefaultGlider");
	if (!Ret.Pickaxe) Ret.Pickaxe = UObject::FindObject<UAthenaPickaxeItemDefinition>("AthenaPickaxeItemDefinition DefaultPickaxe.DefaultPickaxe");
	return Ret;
}

void EquipSkin(AFortPlayerControllerAthena* Controller, UAthenaCharacterItemDefinition* Skin = nullptr) {
	if (!Controller || !Controller->PlayerState) return;
	AFortPlayerStateAthena* PS = (AFortPlayerStateAthena*)Controller->PlayerState;
	if (!Skin) Skin = Controller->CustomizationLoadout.Character ? (Controller->CustomizationLoadout.Character) : GetRandomDefault(&Controller->RandomCharacterIndex);

	if (!Skin->HeroDefinition) return;

	for (auto& SpecRef : Skin->HeroDefinition->Specializations) {
		UFortHeroSpecialization* Spec = StaticLoadObject<UFortHeroSpecialization>(SpecRef.ObjectID.AssetPathName.GetRawString());
		if (Spec) {
			for (auto& PartRef : Spec->CharacterParts) {
				UCustomCharacterPart* Part = StaticLoadObject<UCustomCharacterPart>(PartRef.ObjectID.AssetPathName.GetRawString());
				if (Part) PS->CharacterParts[(int)Part->CharacterPartType] = Part;
			}
		}
	}

	PS->OnRep_CharacterParts();
}


void ServerLoadingScreenDropped_Hook(AFortPlayerControllerAthena* Controller) {
	static UFortAbilitySet* Set;
	if (!Set) Set = StaticLoadObject<UFortAbilitySet>("/Game/Abilities/Player/Generic/Traits/DefaultPlayer/GAS_DefaultPlayer.GAS_DefaultPlayer");
	if (Controller->IsInAircraft()) {
		Controller->ClientReturnToMainMenu(L"YOU JOINED TOO LATE!");
		return;
	}
	GiveAbilitySet(Controller->MyFortPawn, Set);
}

void (*OGServerAttemptInteract)(AFortPlayerController* PlayerController, AActor* ReceivingActor, UPrimitiveComponent* InteractComponent, ETInteractionType InteractType);
void ServerAttemptInteract(AFortPlayerController* PlayerController, AActor* ReceivingActor, UPrimitiveComponent* InteractComponent, ETInteractionType InteractType)
{
	if (!PlayerController || !ReceivingActor) {
		return;
	}
	OGServerAttemptInteract(PlayerController, ReceivingActor, InteractComponent, InteractType); // this fixes doors chat AHHHHh

	if (ReceivingActor->IsA(ABuildingContainer::StaticClass())) {
		ABuildingContainer* BuildingContainer = (ABuildingContainer*)ReceivingActor;
		if (BuildingContainer->bAlreadySearched) return;

		std::string ContainerName = BuildingContainer->Class->GetName();
		FVector LootLocation = BuildingContainer->K2_GetActorLocation() + BuildingContainer->GetActorRightVector() * 70.0f + FVector{ 0, 0, 50 };
		if (ContainerName.contains("Tiered_Chest")) {
			std::vector<FFortItemEntry> Entrys = Looting::PickLootDrops(UKismetStringLibrary::Conv_StringToName(L"Loot_AthenaTreasure"));
			for (auto& RandomEntry : Entrys) {
				Inventory::SpawnPickup(RandomEntry.ItemDefinition, LootLocation, RandomEntry.Count);
			}

			Entrys.clear();
		}
		else if (ContainerName.contains("Tiered_Short_Ammo")) {
			std::vector<FFortItemEntry> Entrys = Looting::PickLootDrops(UKismetStringLibrary::Conv_StringToName(L"Loot_AthenaAmmoSmall"));
			for (auto& RandomEntry : Entrys) {
				Inventory::SpawnPickup(RandomEntry.ItemDefinition, LootLocation, RandomEntry.Count);
			}

			Entrys.clear();
		}

		BuildingContainer->bAlreadySearched = true;
		BuildingContainer->OnRep_bAlreadySearched();
	}
	else if (ReceivingActor->IsA(AFortAthenaSupplyDrop::StaticClass())) {
		AFortAthenaSupplyDrop* SupplyContainer = (AFortAthenaSupplyDrop*)ReceivingActor;
		FVector GGS = SupplyContainer->K2_GetActorLocation();
		GGS.Z += 50;
		std::vector<FFortItemEntry> Entrys = Looting::PickLootDrops(UKismetStringLibrary::Conv_StringToName(L"Loot_AthenaSupplyDrop"));
		for (auto& RandomEntry : Entrys) {
			Inventory::SpawnPickup(RandomEntry.ItemDefinition, GGS, RandomEntry.Count);
		}

		Entrys.clear();
	}
}

void ServerReturnToMainMenu(AFortPlayerController* PlayerController) { //WHAT THE FUCK IS THE POINT OF THIS
	PlayerController->ClientReturnToMainMenu(L"");
	PlayerController->MyFortPawn->K2_DestroyActor(); // extra protection cause sigma
}

void ServerExecuteInventoryItem(AFortPlayerController* PlayerController, FGuid& ItemGuid) {

	if (!PlayerController || !PlayerController->WorldInventory)
		return;

	UFortWeaponItemDefinition* ItemDefinition = nullptr;

	auto& InventoryEntries = PlayerController->WorldInventory->Inventory.ReplicatedEntries;
	if (InventoryEntries.Num() == 0)
		return;

	for (size_t i = 0; i < InventoryEntries.Num(); i++)
	{
		auto ItemEntry = InventoryEntries[i];
		if (ItemEntry.ItemGuid == ItemGuid)
		{
			if (!ItemEntry.ItemDefinition)
				continue;

			if (ItemEntry.ItemDefinition->IsA(UFortDecoItemDefinition::StaticClass()))
			{
				if (!PlayerController->MyFortPawn)
					return;

				UFortDecoItemDefinition* DecoItemDefinition = (UFortDecoItemDefinition*)ItemEntry.ItemDefinition;
				if (!DecoItemDefinition)
					return;

				PlayerController->MyFortPawn->PickUpActor(nullptr, DecoItemDefinition);

				if (!PlayerController->MyFortPawn->CurrentWeapon)
					return;

				PlayerController->MyFortPawn->CurrentWeapon->ItemEntryGuid = ItemGuid;

				if (PlayerController->MyFortPawn->CurrentWeapon->IsA(AFortDecoTool_ContextTrap::StaticClass()))
				{
					AFortDecoTool_ContextTrap* ContextTrap = (AFortDecoTool_ContextTrap*)PlayerController->MyFortPawn->CurrentWeapon;
					if (ContextTrap)
					{
						ContextTrap->ContextTrapItemDefinition = (UFortContextTrapItemDefinition*)ItemEntry.ItemDefinition;
					}
				}

				break;
			}

			ItemDefinition = (UFortWeaponItemDefinition*)ItemEntry.ItemDefinition;
			if (!ItemDefinition)
				return;

			break;
		}
	}

	if (ItemDefinition && PlayerController->MyFortPawn)
	{
		AFortWeapon* Weap = PlayerController->MyFortPawn->EquipWeaponDefinition(ItemDefinition, ItemGuid);
		if (Weap && Weap->IsA(AFortWeap_BuildingTool::StaticClass())) {
			((AFortWeap_BuildingTool*)Weap)->DefaultMetadata = ((UFortBuildingItemDefinition*)ItemDefinition)->BuildingMetaData.Get();
			((AFortWeap_BuildingTool*)Weap)->OnRep_DefaultMetadata();
		}
	}
}

void ServerSpawnInventoryDrop(AFortPlayerControllerAthena* PC, const struct FGuid& ItemGuid, int32 Count)
{
	if(PC && !PC->IsInAircraft())
		Inventory::RemoveItem(PC, ItemGuid, true, Count);
}

__int64 (*AFortPlayerController_GetAthenaLoadoutWithOverrides_OG)(AFortPlayerControllerAthena* Controller, __int64 a2, __int64 a3);
__int64 AFortPlayerController_GetAthenaLoadoutWithOverrides(AFortPlayerControllerAthena* Controller, __int64 a2, __int64 a3)
{
	std::cout << "Controller: " << Controller->GetFullName() << std::endl;

	return AFortPlayerController_GetAthenaLoadoutWithOverrides_OG(Controller, a2, a3);
}

void (*ApplyHomeBaseEffectsOnPlayerSetup_OG)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, char a6, unsigned __int8 a7);
void ApplyHomeBaseEffectsOnPlayerSetup(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, char a6, unsigned __int8 a7)
{
	AAthena_GameState_C* GameState = reinterpret_cast<AAthena_GameState_C*>(a1);

	auto Hero = reinterpret_cast<UFortHero*>(a5);

	std::cout << Hero->CosmeticItem->GetName() << std::endl;

	std::cout << Hero->ItemDefinition->GetName() << std::endl;

	static UFortHeroType* HeroType = UObject::FindObject<UFortHeroType>("FortHeroType HID_001_Athena_Commando_F.HID_001_Athena_Commando_F");

	if (!HeroType)
		HeroType = StaticLoadObject<UFortHeroType>("/Game/Athena/Heroes/HID_001_Athena_Commando_F.HID_001_Athena_Commando_F");

	Hero->ItemDefinition = HeroType;

	return ApplyHomeBaseEffectsOnPlayerSetup_OG(a1, a2, a3, a4, a5, a6, a7);
}

void (*ClientOnPawnDied_OG)(AFortPlayerControllerAthena* Controller, const struct FFortPlayerDeathReport& DeathReport);
void ClientOnPawnDied(AFortPlayerControllerAthena* DeadController, const struct FFortPlayerDeathReport& DeathReport)
{
	std::cout << "ClientOnPawnDied" << std::endl;
	std::cout << "Controller: " << DeadController->GetName() << std::endl;

	bool bDiedToPlayer = DeathReport.KillerPawn && DeathReport.KillerPawn->Controller != DeadController;

	if (!DeadController) return ClientOnPawnDied_OG(DeadController, DeathReport);

	if (DeadController->WorldInventory) {
		for (int i = 0; i < DeadController->WorldInventory->Inventory.ItemInstances.Num(); i++) {
			auto& ItemInstance = DeadController->WorldInventory->Inventory.ItemInstances[i];

			if (!ItemInstance->CanBeDropped()) continue;

			Inventory::RemoveItem(DeadController, ItemInstance->ItemEntry.ItemGuid);
		}
	}

	DeadController->PlayerState->DeathInfo.FinisherOrDowner = DeathReport.KillerPlayerState;
	DeadController->PlayerState->OnRep_DeathInfo();

	void (*RemoveFromAlivePlayers)(AFortGameModeAthena * GameMode, AFortPlayerControllerAthena * DeadController, AFortPlayerStateAthena * KillerState) = decltype(RemoveFromAlivePlayers)(ImageBase + 0x447020);

	RemoveFromAlivePlayers(UWorld::GetWorld()->AuthorityGameMode, DeadController, DeathReport.KillerPlayerState);

	if (DeathReport.DamageCauser)
	{
		std::cout << "DamageCauser: " << DeathReport.DamageCauser->GetName() << std::endl;
	}
	
	if (DeathReport.KillerPawn && bDiedToPlayer)
	{
		auto Controller = DeathReport.KillerPawn->Controller;
		Controller->ClientReceiveKillNotification(DeathReport.KillerPlayerState, DeadController->PlayerState);
		Controller->PlayerState->TeamKillScore++;
		Controller->PlayerState->KillScore++;
		Controller->PlayerState->OnRep_Kills();
		Controller->PlayerState->ClientReportKill(DeadController->PlayerState);

		Controller->MatchReport->Stats.Kills++;
	}

	if (DeadController && DeathReport.KillerPawn && DeathReport.KillerPawn->Controller)
	{
		DeadController->PlayerToSpectateOnDeath = DeathReport.KillerPawn;
		UKismetSystemLibrary::K2_SetTimer(DeadController, L"SpectateOnDeath", 5.f, false);

		DeadController->MatchReport->TeamStats.Place = UWorld::GetWorld()->GameState->PlayersLeft + 1;
		DeadController->MatchReport->TeamStats.TotalPlayers = UWorld::GetWorld()->GameState->TotalPlayers;

		DeadController->ClientSendMatchStatsForPlayer(DeadController->MatchReport->Stats);
		DeadController->ClientSendTeamStatsForPlayer(DeadController->MatchReport->TeamStats);
		bool bSuccess = true;
		FAthenaRewardResult Result = DeadController->MatchReport->EndOfMatchResults;
		DeadController->ClientSendEndBattleRoyaleMatchForPlayer(bSuccess, Result);

		if (UWorld::GetWorld()->GameState->PlayersLeft == 1 && bDiedToPlayer)
		{
			DeathReport.KillerPawn->Controller->PlayWinEffects();

			DeathReport.KillerPawn->Controller->MatchReport->TeamStats.Place = 1;
			DeathReport.KillerPawn->Controller->MatchReport->TeamStats.TotalPlayers = UWorld::GetWorld()->GameState->TotalPlayers;

			DeathReport.KillerPawn->Controller->ClientSendMatchStatsForPlayer(DeathReport.KillerPawn->Controller->MatchReport->Stats);
			DeathReport.KillerPawn->Controller->ClientSendTeamStatsForPlayer(DeathReport.KillerPawn->Controller->MatchReport->TeamStats);
			bool bSuccess = true;
			FAthenaRewardResult Result{};
			DeathReport.KillerPawn->Controller->ClientSendEndBattleRoyaleMatchForPlayer(bSuccess, Result);

			UWorld::GetWorld()->GameState->WinningTeam = int(DeathReport.KillerPlayerState->TeamIndex);
			UWorld::GetWorld()->GameState->OnRep_WinningTeam();
			UWorld::GetWorld()->GameState->WinningPlayerName = DeathReport.KillerPlayerState->GetPlayerName();
			UWorld::GetWorld()->GameState->OnRep_WinningPlayerName();
		}
	}

	return ClientOnPawnDied_OG(DeadController, DeathReport);
}

void ServerHandlePickup(AFortPlayerPawnAthena* Pawn, class AFortPickup* Pickup, float InFlyTime, const struct FVector& InStartDirection, bool bPlayPickupSound)
{
	*(bool*)(__int64(&Pickup->PickupLocationData) + 0x4D) = bPlayPickupSound;
	Pickup->PickupLocationData.FlyTime = 0.5f;
	Pickup->PickupLocationData.PickupTarget = Pawn;
	Pickup->PickupLocationData.StartDirection = (FVector_NetQuantizeNormal)InStartDirection;
	Pickup->OnRep_PickupLocationData();
	Pickup->bPickedUp = true;
	Pickup->OnRep_bPickedUp();
}

inline void (*OriginalServerSwapItemsInternal)(AFortQuickBars* AmICooked, EFortQuickBars QuickBarA, int32 SlotIndexA, EFortQuickBars QuickBarB, int32 SlotIndexB);
void ServerSwapItemsInternal(AFortQuickBars* AmICooked, EFortQuickBars QuickBarA, int32 SlotIndexA, EFortQuickBars QuickBarB, int32 SlotIndexB)
{
	std::cout << "QuickBarA: " << (int)QuickBarA << std::endl;
	std::cout << "QuickBarB: " << (int)QuickBarB << std::endl;
	std::cout << "SlotIndexA: " << SlotIndexA << std::endl;
	std::cout << "SlotIndexB: " << SlotIndexB << std::endl;
	std::cout << "USER WANMTS TO SWAP ITEM" << std::endl;
	//tell me these please please please
	if (AmICooked->Owner->IsA(AFortPlayerControllerAthena::StaticClass())) {
		std::cout << "PlayerController Sigma" << std::endl;
		auto PC = (AFortPlayerControllerAthena*)(AmICooked->Owner);
		UFortItemDefinition* ItemA = nullptr;
		if (QuickBarA == EFortQuickBars::Primary) // this should never be like not primary but is ok
		{
			auto& Guid = PC->QuickBars->PrimaryQuickBar.Slots[SlotIndexA].Items[0]; //should only be one item if im using all braincells
			ItemA = Inventory::GetEntryInInv(PC, Guid).ItemDefinition;
		}

		if (ItemA)
		{
			std::cout << "ItemA: " << ItemA->GetFullName() << std::endl;
		}
	}
	std::cout << AmICooked->Owner->GetFullName() << std::endl;
	OriginalServerSwapItemsInternal(AmICooked, QuickBarA, SlotIndexA, QuickBarB, SlotIndexB);
}

inline __int64 (*OnPickupComplete_OG)(AFortPickup* a1);

__int64 OnPickupComplete(AFortPickup* a1)
{
	__int64 Test = OnPickupComplete_OG(a1);
	auto& PickupLocationData = a1->PickupLocationData;
	AFortPlayerPawnAthena* Pawn = reinterpret_cast<AFortPlayerPawnAthena*>(PickupLocationData.PickupTarget);
	if (!Pawn) return Test;
	AFortPlayerControllerAthena* Controller = (AFortPlayerControllerAthena*)Pawn->GetController();
	if (!Controller) return Test;
	if (Controller->IsInAircraft()) return Test; // ?!?!?!?
	UFortItemDefinition* CurrentWeaponDefinition = Pawn->CurrentWeapon ? Pawn->CurrentWeapon->WeaponData : nullptr;
	if (!CurrentWeaponDefinition) return Test;
	bool bSwapping = false;

	Inventory::GiveItem(Controller, a1->PrimaryPickupItemEntry.ItemDefinition, a1->PrimaryPickupItemEntry.Count, -1, a1->PrimaryPickupItemEntry.LoadedAmmo);

	std::cout << "_ReturnAddress: " << __int64(_ReturnAddress()) - ImageBase << std::endl;

	return Test;
}


inline void (*OrginalAirCraftStartPhase)(AFortGameModeAthena* GameMode);
void AirCraftStartPhase(AFortGameModeAthena* GameMode)
{
	OrginalAirCraftStartPhase(GameMode);
	std::cout << "AIRCRAFT " << std::endl;

	TArray<ABuildingContainer*> Containers;
	UGameplayStatics::GetAllActorsOfClass(UWorld::GetWorld(), ABuildingContainer::StaticClass(), reinterpret_cast<TArray<AActor*>*>(&Containers));

	for (auto& Container : Containers) {
		if (!Container->GetName().contains("Tiered_") && !Container->IsA(AFortAthenaSupplyDrop::StaticClass())) {
			Container->bAlreadySearched = true;
			Container->OnRep_bAlreadySearched();
		}
	}

	for (int i = 0; i < UWorld::GetWorld()->NetDriver->ClientConnections.Num(); i++) {
		UNetConnection* NetConn = UWorld::GetWorld()->NetDriver->ClientConnections[i];
		
		if (NetConn && NetConn->PlayerController && NetConn->PlayerController->Pawn)
		{
			AFortPlayerControllerAthena* PC = reinterpret_cast<AFortPlayerControllerAthena*>(NetConn->PlayerController);
			if (PC) {
				//Spectating Bug Fix
				if (PC->PlayerCameraManager) PC->PlayerCameraManager->ViewRollMin = PC->PlayerCameraManager->ViewRollMax = 0;

				//Equip Pickaxe
				PC->ServerExecuteInventoryItem(Inventory::GetItemInSlot(PC, 0));

				//Clear Inv
			}
		}
	}
}

void ServerEditBuildingActor(AFortPlayerControllerAthena* PC, ABuildingSMActor* BuildingActorToEdit, TSubclassOf<ABuildingSMActor> NewBuildingClass, int32 RotationIterations, bool bMirrored)
{
	if (!PC || !BuildingActorToEdit || PC->PlayerState != BuildingActorToEdit->EditingPlayer || BuildingActorToEdit->bDestroyed == 1) return;

	BuildingActorToEdit->SetNetDormancy(ENetDormancy::DORM_DormantAll);
	BuildingActorToEdit->EditingPlayer = nullptr;

	ABuildingSMActor* Build = ReplaceBuildingActor(BuildingActorToEdit, 1, NewBuildingClass, BuildingActorToEdit->CurrentBuildingLevel, RotationIterations, bMirrored, PC);

	if (Build) {
		Build->bPlayerPlaced = true;
	}
}

void ServerRepairBuildingActor(AFortPlayerControllerAthena* PC, ABuildingSMActor* BuildingActorToRepair)
{
	if (!PC || BuildingActorToRepair->bDestroyed == 1)
		return;


	AFortPlayerStateAthena* PlayerState = (AFortPlayerStateAthena*)PC->PlayerState;
	if (!PlayerState)
		return;
	auto BuildDef = GetResourceItemDef(BuildingActorToRepair->ResourceType);
	// what the floppers
	auto ItemEntry = PC->WorldInventory->Inventory.ReplicatedEntries.Search([&](FFortItemEntry& entry)
		{ return entry.ItemDefinition == BuildDef; });

	if (!ItemEntry)
		return;

	//int TEST = *(int*)(__int64(BuildingActorToRepair) + 0x51);

	// there has to be a proper way of doing this
	//std::cout << std::to_string(((UFortConstructionSet*)BuildingActorToRepair->BuildingAttributeSet)->RepairCost.CurrentValue) << std::endl;
	//UFortConstructionSet
	//FortGameplayAttributeData
	std::cout << std::to_string(BuildingActorToRepair->BuildingAttributeSet->HealingSource.Maximum) << std::endl;
	std::cout << std::to_string(BuildingActorToRepair->BuildingAttributeSet->HealingSource.BaseValue) << std::endl;
	std::cout << std::to_string(BuildingActorToRepair->BuildingAttributeSet->HealingSource.CurrentValue) << std::endl;
	//std::cout << std::to_string(TEST) << std::endl;
	//2C8
	// 
	// 
	//std::cout << std::to_string(BuildingActorToRepair->GetHealth()) << std::endl;
	//std::cout << std::to_string(BuildingActorToRepair->GetMaxHealth()) << std::endl;
	//std::cout << std::to_string(1.f - BuildingActorToRepair->GetHealthPercent()) << std::endl;
	// main issue is like maths but its going to not be proper all the time unless you have a list of things what isnt proper so probally try to get the real cost
	int32 BuildCost = (int32)std::floor(7.5f * (1.f - BuildingActorToRepair->GetHealthPercent()));
	if (BuildingActorToRepair->ResourceType == EFortResourceType::Stone)
	if (BuildCost == 0)
	BuildCost += 1;

	std::cout << std::to_string(BuildCost) << std::endl;
	std::cout << std::to_string(ItemEntry->Count) << std::endl;
	std::cout << std::to_string(ItemEntry->LoadedAmmo) << std::endl;
	if (BuildCost > ItemEntry->Count) return; // user doesnt have enough mats

	Inventory::RemoveItem(PC, ItemEntry->ItemGuid, false, BuildCost);

	BuildingActorToRepair->RepairBuilding(PC, BuildCost); // 10
}

void ServerCreateBuildingActor(AFortPlayerControllerAthena* Controller, FBuildingClassData BuildingClassData, FVector_NetQuantize10 BuildLoc, FRotator Rotator, bool bMirrored)
{
	if (!Controller)
		return;

	UClass* ClassToUse = nullptr;

	if (BuildingClassData.BuildingClass)
	{
		ClassToUse = BuildingClassData.BuildingClass.Get();
	}

	if (!ClassToUse)
		return;

	std::cout << "ClassToUse: " << ClassToUse->GetFullName() << std::endl;

	TArray<ABuildingSMActor*> RemoveBuildings;
	char _Unknown;
	static auto CantBuild = (__int64 (*)(UWorld*, UObject*, FVector, FRotator, bool, TArray<ABuildingSMActor*> *, char*))(ImageBase + 0x61d490);
	if (CantBuild(UWorld::GetWorld(), ClassToUse, BuildLoc, Rotator, bMirrored, &RemoveBuildings, &_Unknown))
		return;

	auto BuildDef = GetResourceItemDef(((ABuildingSMActor*)ClassToUse->DefaultObject)->ResourceType);
	auto ItemEntry = Controller->WorldInventory->Inventory.ReplicatedEntries.Search([BuildDef](FFortItemEntry& entry)
		{ return entry.ItemDefinition == BuildDef; });

	if (!ItemEntry)
		return;

	Inventory::RemoveItem(Controller, ItemEntry->ItemGuid, false, 10);

	FTransform Transform{};
	Transform.Translation = BuildLoc;
	Transform.Rotation = ConvertRotToQuat(Rotator);
	Transform.Scale3D = FVector(1, 1, 1);
	ABuildingSMActor* Building = SpawnActor<ABuildingSMActor>(Controller, ClassToUse, Transform);
	Building->bPlayerPlaced = true;
	Building->SetMirrored(bMirrored);
	Building->InitializeKismetSpawnedBuildingActor(Building, Controller);
	Building->Team = Controller->PlayerState->TeamIndex;

	for (int i = 0; i < RemoveBuildings.Num(); i++) {
		RemoveBuildings[i]->K2_DestroyActor();
	}
	RemoveBuildings.Clear();
}

void ServerBeginEditingBuildingActor(AFortPlayerController* Player, ABuildingSMActor* Building)
{
	if (!Player || !Player->MyFortPawn || !Building || Building->Team != static_cast<AFortPlayerStateAthena*>(Player->PlayerState)->TeamIndex)
		return;

	AFortPlayerStateAthena* PlayerState = (AFortPlayerStateAthena*)Player->PlayerState;
	if (!PlayerState)
		return;

	auto ItemEntry = Player->WorldInventory->Inventory.ReplicatedEntries.Search([](FFortItemEntry& entry)
		{ return entry.ItemDefinition->IsA<UFortEditToolItemDefinition>(); });
	if (!ItemEntry)
		return;

	Player->ServerExecuteInventoryItem(ItemEntry->ItemGuid);

	auto EditTool = Player->MyFortPawn->CurrentWeapon->Cast<AFortWeap_EditingTool>();
	EditTool->EditActor = Building;
	Building->EditingPlayer = Player->PlayerState;
	Building->OnRep_EditingPlayer();
	EditTool->OnRep_EditActor();
}

void ServerEndEditingBuildingActor(AFortPlayerControllerAthena* PC, ABuildingSMActor* BuildingActorToStopEditing)
{
	std::cout << "CALLED " << std::endl;
	if (!PC || PC->PlayerState != BuildingActorToStopEditing->EditingPlayer || BuildingActorToStopEditing->bDestroyed == 1) return;

	auto ItemEntry = PC->WorldInventory->Inventory.ReplicatedEntries.Search([](FFortItemEntry& entry)
		{ return entry.ItemDefinition->IsA<UFortEditToolItemDefinition>(); });

	if (!ItemEntry)
		return;

	auto EditTool = PC->MyFortPawn->CurrentWeapon->Cast<AFortWeap_EditingTool>();
	BuildingActorToStopEditing->SetNetDormancy(ENetDormancy::DORM_DormantAll);
	BuildingActorToStopEditing->EditingPlayer = nullptr;
	BuildingActorToStopEditing->OnRep_EditingPlayer();
	if (EditTool) {
		EditTool->EditActor = nullptr;
		EditTool->OnRep_EditActor();
	}
}

// function doesnt work without orginal hooked
inline void (*OrginalServerSpawnDeco)(AFortTrapTool* DecoTool, const FVector& Location, const FRotator& Rotation, ABuildingSMActor* AttachedActor);
void ServerSpawnDeco(AFortTrapTool* DecoTool, const FVector& Location, const FRotator& Rotation, ABuildingSMActor* AttachedActor)
{
	std::cout << "TRAP TEST" << std::endl;
	if (!DecoTool) return;
	AFortPlayerPawnAthena* Pawn = (AFortPlayerPawnAthena*)DecoTool->GetOwner();
	AFortPlayerControllerAthena* PC = (AFortPlayerControllerAthena*)Pawn->Controller;
	if (!PC || PC->IsInAircraft()) return; 

	auto ItemEntry = PC->WorldInventory->Inventory.ReplicatedEntries.Search([&](FFortItemEntry& entry)
		{ return entry.ItemDefinition == DecoTool->ItemDefinition; });
	if (!ItemEntry) return;

	OrginalServerSpawnDeco(DecoTool, Location, Rotation, AttachedActor); // user has the trap so we can call og
	std::cout << "TRAP?" << std::endl;
	Inventory::RemoveItem(PC, ItemEntry->ItemGuid, false, 1);
	if (ItemEntry->Count - 1 <= 0) {
		// this was only on very old versions and later versions it wouldnt do this ;(
		PC->QuickBars->ServerActivateSlotInternal(EFortQuickBars::Secondary, PC->QuickBars->SecondaryQuickBar.PreviousFocusedSlot, 0, true);
	}

	FTransform Transform{};
	Transform.Translation = Location;
	Transform.Rotation = ConvertRotToQuat(Rotation);
	Transform.Scale3D = FVector(1, 1, 1);

	//UBlueprintFunctionLibrary::
	// i'm like special
	UFortDecoItemDefinition* ItemDef = (UFortDecoItemDefinition*)DecoTool->ItemDefinition;
	ABuildingTrap* Trap = SpawnActor<ABuildingTrap>(PC, ItemDef->GetBlueprintClass().Get(), Transform);
	Trap->InitializeKismetSpawnedBuildingActor(Trap, PC);
	Trap->AttachedTo = AttachedActor;
	Trap->Team = PC->PlayerState->TeamIndex;
	Trap->OnRep_AttachedTo();
}

void ServerPlayEmoteItem(AFortPlayerControllerAthena* PC, UFortMontageItemDefinitionBase* EmoteAsset)
{
	if (!PC || !PC->MyFortPawn || !EmoteAsset || !PC->MyFortPawn->AbilitySystemComponent) return;
	if (PC->IsInAircraft()) return;

	UClass* AbilityToUse = UGAB_Emote_Generic_C::StaticClass();
	UAthenaDanceItemDefinition* DanceItemDef = (UAthenaDanceItemDefinition*)EmoteAsset;

	if (DanceItemDef && AbilityToUse) {
		FGameplayAbilitySpec Spec{ -1,-1,-1 };
		Spec.Ability = (UFortGameplayAbility*)AbilityToUse->DefaultObject;
		Spec.Level = 1;
		Spec.InputID = -1;
		Spec.SourceObject = DanceItemDef;
		Spec.Handle.Handle = rand();
		GiveAbility(PC->MyFortPawn->AbilitySystemComponent, &Spec.Handle, Spec);

		((AFortPlayerStateAthena*)PC->PlayerState)->AbilitySystemComponent->ServerTryActivateAbility(Spec.Handle, Spec.InputPressed, Spec.ActivationInfo.PredictionKeyWhenActivated);
	}
}