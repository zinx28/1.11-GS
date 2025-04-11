#pragma once
#include "framework.h"

static UFortResourceItemDefinition* Wood;
static UFortResourceItemDefinition* Stone;
static UFortResourceItemDefinition* Metal;

namespace Inventory {
	int GetMaxAmmo(UFortWeaponItemDefinition* ItemDef) {

		return 0;
	}

	void Update(AFortPlayerControllerAthena* PC, FFortItemEntry* Entry = nullptr) {
		auto WorldInventory = PC->WorldInventory;
		auto QuickBars = PC->QuickBars;
		WorldInventory->HandleInventoryLocalUpdate();
		PC->HandleWorldInventoryLocalUpdate();
		
		PC->OnRep_QuickBar();
		QuickBars->OnRep_PrimaryQuickBar();
		QuickBars->OnRep_SecondaryQuickBar();
		//WorldInventory->Inventory.MarkArrayDirty(); hoping this isnt needed even for certain items
		// 
		PC->ForceNetUpdate();
		PC->WorldInventory->ForceNetUpdate();

		
		if (Entry)
			PC->WorldInventory->Inventory.MarkItemDirty(*Entry);
		else
			PC->WorldInventory->Inventory.MarkArrayDirty();
	}

	int GetOpenSlot(AFortPlayerControllerAthena* PC) {
		auto Quickbars = PC->QuickBars;
		if (Quickbars != nullptr) {
			for (int i = 0; i < Quickbars->PrimaryQuickBar.Slots.Num(); i++) {
				if (Quickbars->PrimaryQuickBar.Slots[i].Items.Num() == 0) {
					return i;
				}
			}
		}
		return -1;
	}

	int GetWeaponSlot(AFortPlayerControllerAthena* PC, FGuid Item) {
		auto Quickbars = PC->QuickBars;
		if (Quickbars != nullptr) {
			for (int i = 0; i < Quickbars->PrimaryQuickBar.Slots.Num(); i++) {
				if (Quickbars->PrimaryQuickBar.Slots[i].Items.Num() > 0) {
					if(Quickbars->PrimaryQuickBar.Slots[i].Items[0] == Item)
						return i;
				}
			}
		}
		return -1;
	}

	UFortWorldItem* GetItemInInv(AFortPlayerControllerAthena* PC, UFortItemDefinition* Def) {
		for (int i = 0; i < PC->WorldInventory->Inventory.ItemInstances.Num(); i++) {
			if (PC->WorldInventory->Inventory.ItemInstances[i]->ItemEntry.ItemDefinition == Def) {
				return PC->WorldInventory->Inventory.ItemInstances[i];
			}
		}
		return nullptr;
	}

	FFortItemEntry GetEntryInInv(AFortPlayerControllerAthena* PC, FGuid GUID) {
		for (int i = 0; i < PC->WorldInventory->Inventory.ReplicatedEntries.Num(); i++) {
			if (PC->WorldInventory->Inventory.ReplicatedEntries[i].ItemGuid == GUID) {
				return PC->WorldInventory->Inventory.ReplicatedEntries[i];
			}
		}
		return {};
	}

	FGuid GetItemInSlot(AFortPlayerControllerAthena* PC, int Slot, EFortQuickBars QB = EFortQuickBars::Primary) {
		auto Quickbars = PC->QuickBars;
		if (Quickbars) 
			return ((QB == EFortQuickBars::Primary) ? (Quickbars->PrimaryQuickBar.Slots[Slot].Items[0]) : (Quickbars->SecondaryQuickBar.Slots[Slot].Items[0]));

		return {};
	}

	std::pair<EFortQuickBars, int> GetItemSlot(AFortPlayerControllerAthena* PC, FGuid GUID) {
		auto Quickbars = PC->QuickBars;
		if (Quickbars) {
			for (int i = 0; i < Quickbars->PrimaryQuickBar.Slots.Num(); i++) {
				// yes this is stupid
				if (Quickbars->PrimaryQuickBar.Slots.IsValidIndex(i) &&
					Quickbars->PrimaryQuickBar.Slots[i].Items.Data && 
					Quickbars->PrimaryQuickBar.Slots[i].Items.IsValidIndex(0) &&
					Quickbars->PrimaryQuickBar.Slots[i].Items[0] == GUID) {
					return std::make_pair(EFortQuickBars::Primary, i);
				}
			}
			for (int i = 0; i < Quickbars->SecondaryQuickBar.Slots.Num(); i++) {
				if (Quickbars->SecondaryQuickBar.Slots.IsValidIndex(i) &&
					Quickbars->SecondaryQuickBar.Slots[i].Items.Data && 
					Quickbars->SecondaryQuickBar.Slots[i].Items.IsValidIndex(0) &&
					Quickbars->SecondaryQuickBar.Slots[i].Items[0] == GUID) {
					return std::make_pair(EFortQuickBars::Secondary, i);
				}
			}
		}
		return std::make_pair(EFortQuickBars::Max_None, -1);
	}

	void SpawnPickup(UFortItemDefinition* Item, FVector Loc, int Count, int32 LoadedAmmo = -1) {
		FRotator Rotator = {};

		FTransform Transform{};
		Transform.Translation = Loc;
		Transform.Rotation = ConvertRotToQuat(Rotator);
		Transform.Scale3D = FVector{ 1,1,1 };
		AFortPickupAthena* NewPickup = SpawnActor<AFortPickupAthena>(Transform, nullptr);
		NewPickup->PrimaryPickupItemEntry.ItemDefinition = Item;
		NewPickup->PrimaryPickupItemEntry.Count = Count;
		// we only want max ammo for new items
		if (LoadedAmmo == -1) {
	/*		FFortRangedWeaponStats* Stats = nullptr;*/
			if (Item->IsA(UFortWeaponItemDefinition::StaticClass())) {

				for (auto& Map : ((UFortWeaponItemDefinition*)Item)->WeaponStatHandle.DataTable->RowMap) {
					//std::cout << Map.Key().ToString() << std::endl;
					if (((UFortWeaponItemDefinition*)Item)->WeaponStatHandle.RowName.ComparisonIndex == Map.Key().ComparisonIndex && Map.Value()) {
						LoadedAmmo = ((FFortBaseWeaponStats*)Map.Value())->ClipSize;
					
						break;
					}
				}
			}

			if (LoadedAmmo == -1) {
				LoadedAmmo = 0;
			}
		}
		NewPickup->PrimaryPickupItemEntry.LoadedAmmo = LoadedAmmo;
		
		NewPickup->OnRep_PrimaryPickupItemEntry();

		NewPickup->TossPickup(Loc, nullptr, -1, true);
	}

	void RemoveItem(AFortPlayerControllerAthena* PC, FGuid GUID, bool ShouldSpawnItem = true, int Amount = -1, int ShouldINotSwap = false) {
		auto Slot = GetItemSlot(PC, GUID);
		auto WorldInventory = PC->WorldInventory;
		bool IsDroppingCertain = false;
		bool ShouldGoToPickaxe = PC->GetPlayerPawn()->CurrentWeapon->ItemEntryGuid == GUID;
		for (int i = 0; i < WorldInventory->Inventory.ItemInstances.Num(); i++) {
			UFortWorldItem*& Item = WorldInventory->Inventory.ItemInstances[i];
			if (Item->ItemEntry.ItemGuid == GUID) {
				if (Amount != -1) {
					Item->ItemEntry.Count -= Amount;
					if (Item->ItemEntry.Count > 0) {
						IsDroppingCertain = true;
					}
					else {
						// full count
						int DroppedAmount = Amount + Item->ItemEntry.Count;
						Amount = UKismetMathLibrary::Max(0, DroppedAmount);
						Item->ItemEntry.Count = 0;
					}
				}
				else Amount = Item->ItemEntry.Count;
				
				if (ShouldSpawnItem)
					SpawnPickup(Item->ItemEntry.ItemDefinition, PC->Pawn->K2_GetActorLocation(), Amount, WorldInventory->Inventory.ItemInstances[i]->GetLoadedAmmo());

				if(!IsDroppingCertain)
					WorldInventory->Inventory.ItemInstances.Remove(i);
				
			
				break;
			}
		}

		for (int i = 0; i < WorldInventory->Inventory.ReplicatedEntries.Num(); i++) {
			FFortItemEntry& Item = WorldInventory->Inventory.ReplicatedEntries[i];
			if (Item.ItemGuid == GUID) {
				if (IsDroppingCertain) {
					Item.Count -= Amount;
					Update(PC, &Item);
				}
				else {
					WorldInventory->Inventory.ReplicatedEntries.Remove(i);
					PC->QuickBars->ServerRemoveItemInternal(GUID, false, true);
				}
				
				break;
			}
		}

		if (IsDroppingCertain)
			return;

		if (Slot.first == EFortQuickBars::Primary) {
			PC->QuickBars->EmptySlot(Slot.first, Slot.second);
			PC->QuickBars->PrimaryQuickBar.Slots[Slot.second].Items.Data = nullptr;
			PC->QuickBars->PrimaryQuickBar.Slots[Slot.second].Items.Clear();
			PC->QuickBars->ServerActivateSlotInternal(Slot.first, Slot.second, 0, true);

			// only needed for primary
			if (ShouldGoToPickaxe && !ShouldINotSwap) {
				// fix pickaxe bug after dropping
				// this is proper and yes epic did this back then
				// code could have improvements
				FGuid GuildToUse = PC->QuickBars->PrimaryQuickBar.Slots[0].Items[0];
				int32 SlotToUse = 0;
				int32 LastSlot = PC->QuickBars->PrimaryQuickBar.PreviousFocusedSlot;
				int32 SecondSlot = PC->QuickBars->PrimaryQuickBar.SecondaryFocusedSlot;
				if (PC->QuickBars->PrimaryQuickBar.Slots.IsValidIndex(LastSlot))
				{
					if (PC->QuickBars->PrimaryQuickBar.Slots[LastSlot].Items.IsValidIndex(0)) {
						GuildToUse = PC->QuickBars->PrimaryQuickBar.Slots[LastSlot].Items[0];
						SlotToUse = LastSlot;
					}
				}
				else if (PC->QuickBars->PrimaryQuickBar.Slots.IsValidIndex(SecondSlot)) {
					if (PC->QuickBars->PrimaryQuickBar.Slots[SecondSlot].Items.IsValidIndex(0)) {
						GuildToUse = PC->QuickBars->PrimaryQuickBar.Slots[SecondSlot].Items[0];
						SlotToUse = SecondSlot;
					}
				}
					
				PC->QuickBars->ServerActivateSlotInternal(Slot.first, SlotToUse, 0, true);
				PC->ServerExecuteInventoryItem(GuildToUse);
				/*PC->GetPlayerPawn()->EquipWeaponDefinition(
					PC->CustomizationLoadout.Pickaxe->WeaponDefinition,
					PC->QuickBars->PrimaryQuickBar.Slots[0].Items[0]
				);*/
			}
		}
		else if (Slot.first == EFortQuickBars::Secondary) {
			PC->QuickBars->EmptySlot(Slot.first, Slot.second);
			PC->QuickBars->SecondaryQuickBar.Slots[Slot.second].Items.Data = nullptr;
			PC->QuickBars->SecondaryQuickBar.Slots[Slot.second].Items.Clear();
			PC->QuickBars->ServerActivateSlotInternal(Slot.first, Slot.second, 0, true);
		}
		Update(PC);
	}

	// just copiewd befre you removed
	inline EFortQuickBars GetQuickBars(UFortItemDefinition* Def) {
		if (Def->IsA(UFortBuildingItemDefinition::StaticClass()) || 
			Def->IsA(UFortResourceItemDefinition::StaticClass()) || 
			Def->IsA(UFortEditToolItemDefinition::StaticClass()) ||
			//Def->IsA(UFortTrapItemDefinition::StaticClass()) || ~ this would fix the auto equip with traps
			Def->IsA(UFortWeaponMeleeItemDefinition::StaticClass()) ||
			Def->IsA(UFortAmmoItemDefinition::StaticClass())) return EFortQuickBars::Secondary;

		return EFortQuickBars::Primary;
	}

	inline bool IsPrimaryQuickBar(UFortItemDefinition* Def)
	{
		return GetQuickBars(Def) == EFortQuickBars::Primary && Def->IsA(UFortWeaponMeleeItemDefinition::StaticClass());
	}

	int32 GetPrimaryQuickBarItems(AFortPlayerControllerAthena* PC)
	{
		int Items = 0;
		for (auto& ItemInstance : PC->WorldInventory->Inventory.ItemInstances)
		{
			auto Pair = GetItemSlot(PC, ItemInstance->ItemEntry.ItemGuid);

			if (Pair.first == EFortQuickBars::Primary)
			{
				if (ItemInstance->ItemEntry.ItemDefinition->IsA(UFortWeaponMeleeItemDefinition::StaticClass()) && ItemInstance->ItemEntry.ItemDefinition->IsA(UFortEditToolItemDefinition::StaticClass())) continue;

				Items++;
			}
		}
	}

	UFortWorldItem* GiveItem(AFortPlayerControllerAthena* PC, UFortItemDefinition* ItemDef, int Count = 1, int Slot = -1, int LoadedAmmo = -1, bool AutoEquip = false) {
		
		EFortQuickBars Quickbar = GetQuickBars(ItemDef);
		if (Quickbar == EFortQuickBars::Primary && Slot == -1) {
			Slot = GetOpenSlot(PC);
			std::cout << "SLOT " << std::to_string(Slot) << std::endl;
		}

		if (Count == 0) return nullptr; // you cant have 0 items

		auto WorldInventory = PC->WorldInventory;
		auto Quickbars = PC->QuickBars;
		bool Stack = false;
		int idkhowtodothis = 0;

		// todo make this a function
		for (int i = 0; i < WorldInventory->Inventory.ItemInstances.Num(); i++) {
			auto Item = WorldInventory->Inventory.ItemInstances[i];
			//AFortTrapTool
			
			if (GetQuickBars(Item->ItemEntry.ItemDefinition) == EFortQuickBars::Primary) {
				//std::cout << "ITEMS " << Item->ItemEntry.ItemDefinition->GetFullName() << std::endl;
				if(!Item->ItemEntry.ItemDefinition->IsA(UFortTrapItemDefinition::StaticClass()))
					idkhowtodothis++;
			}
		}

		for (int i = 0; i < WorldInventory->Inventory.ItemInstances.Num(); i++) {
			auto& Item = WorldInventory->Inventory.ItemInstances[i];
			if (Item->ItemEntry.ItemDefinition == ItemDef && Item->ItemEntry.ItemDefinition->MaxStackSize > 1) {
				std::cout << "STACK SIZE  " << std::to_string(Item->ItemEntry.ItemDefinition->MaxStackSize) << std::endl;
				std::cout << std::to_string(Count) << std::endl;
				// possible but ahhhhh
				// allow the same item again?!?!
			
				Count = (Item->ItemEntry.Count += Count);
				
				if (Count > Item->ItemEntry.ItemDefinition->MaxStackSize) {
					std::cout << "TODO !!" << std::endl;
					int Num = Count - Item->ItemEntry.ItemDefinition->MaxStackSize;
					Count = (Item->ItemEntry.Count = Item->ItemEntry.ItemDefinition->MaxStackSize);
					std::cout << std::to_string(Num) << std::endl;
					if (Num > 0) {
						SpawnPickup(Item->ItemEntry.ItemDefinition, PC->Pawn->K2_GetActorLocation(), Num, LoadedAmmo);
					}
					// attempt to add the remaining items or just drop it
				}

			
				Stack = true;
				break;

			}
		}
	
		
	
	

		if (Stack) {
			/*Slot = GetWeaponSlot(PC, Item->ItemEntry.ItemGuid);*/
			for (int i = 0; i < WorldInventory->Inventory.ReplicatedEntries.Num(); i++) {
				auto& Item = WorldInventory->Inventory.ReplicatedEntries[i];
				if (Item.ItemDefinition == ItemDef /*&& !Item.ItemDefinition->IsA(UFortWeaponItemDefinition::StaticClass())*/) {
				
					WorldInventory->Inventory.ReplicatedEntries[i].Count = Count;
					Update(PC, &Item);
					break;
				}
			}
			return nullptr;
		}


		std::cout << "AMOUNT OF ITEMS " << idkhowtodothis << std::endl;
		// full inventory
		if (Quickbar == EFortQuickBars::Primary && !ItemDef->IsA(UFortTrapItemDefinition::StaticClass())) { // this check fixes mats not stacking
			if (idkhowtodothis >= 5) {
				if (((AFortPlayerPawnAthena*)PC->Pawn)->CurrentWeapon->WeaponData->bCanBeDropped) {
					Slot = GetWeaponSlot(PC, ((AFortPlayerPawnAthena*)PC->Pawn)->CurrentWeapon->ItemEntryGuid);
					RemoveItem(PC, ((AFortPlayerPawnAthena*)PC->Pawn)->CurrentWeapon->ItemEntryGuid, true, -1, true);
				}
				else {
					FVector ggsagain = PC->Pawn->K2_GetActorLocation();
					ggsagain.Z += 50; // maybe from eyes?
					SpawnPickup(ItemDef, ggsagain, Count, LoadedAmmo);
					return nullptr;
				}
				//std::cout << "spawn?!?!" << std::endl;
				
				// remove current item....
				
				//SpawnPickup(ItemDef, ggsagain, Count, LoadedAmmo);
				//return nullptr;
			}
		}



		UFortWorldItem* Item = (UFortWorldItem*)ItemDef->CreateTemporaryItemInstanceBP(Count, 1);
		Item->ItemEntry.Count = Count;
		Item->ItemEntry.LoadedAmmo = LoadedAmmo;
		Item->SetOwningControllerForTemporaryItem(PC);
		FFortItemEntryStateValue Value{};
		Value.IntValue = 1;
		Value.StateType = EFortItemEntryState::ShouldShowItemToast;
		Item->ItemEntry.StateValues.Add(Value);
		WorldInventory->Inventory.ReplicatedEntries.Add(Item->ItemEntry);
		WorldInventory->Inventory.ItemInstances.Add(Item);
		std::cout << std::to_string(Quickbar == EFortQuickBars::Primary) << std::endl;
		std::cout << std::to_string(Count) << std::endl;
		std::cout << std::to_string(LoadedAmmo) << std::endl;

		Quickbars->ServerAddItemInternal(
			Item->GetItemGuid(), 
			Quickbar, 
			Slot
		);

		if (AutoEquip) {
			PC->GetPlayerPawn()->EquipWeaponDefinition(
				(UFortWeaponItemDefinition*)Item->ItemEntry.ItemDefinition,
				Item->GetItemGuid()
			);
		}
		
		Update(PC);
		return Item;
	}



	void UpdateLoadedAmmo(AFortPlayerControllerAthena* PC, AFortWeapon* Weapon/*, int Ammo*/) {
		auto WorldInventory = PC->WorldInventory;
		if (WorldInventory && Weapon) {
			//FFortItemEntry* ItemEntry2 = nullptr;
			for (int i = 0; i < WorldInventory->Inventory.ItemInstances.Num(); i++) {
				auto& Item = WorldInventory->Inventory.ItemInstances[i];
				// we dont use def bc other items can be named the same
				if (Item->ItemEntry.ItemGuid == Weapon->ItemEntryGuid) {
					Item->ItemEntry.LoadedAmmo = Weapon->AmmoCount;
					//ItemEntry2 = &Item->ItemEntry;
				}
			}
			for (int i = 0; i < WorldInventory->Inventory.ReplicatedEntries.Num(); i++) {
				auto& Item = WorldInventory->Inventory.ReplicatedEntries[i];

				if (Item.ItemGuid == Weapon->ItemEntryGuid) {
					Item.LoadedAmmo = Weapon->AmmoCount;
					Inventory::Update(PC, &Item);
				}
			}
		}
	}
}