#pragma once

// idk what to put this under without player.h being over loaded
#include "Inventory.h"

void (*OGReloadCost)(AFortWeapon* a1, int a2);
void ReloadCost(AFortWeapon* a1, int a2) {
	if (!a1) return OGReloadCost(a1, a2);
	AFortPlayerPawnAthena* Pawn = (AFortPlayerPawnAthena*)a1->Owner;
	if(!Pawn) return OGReloadCost(a1, a2);
	AFortPlayerControllerAthena* PC = (AFortPlayerControllerAthena*)Pawn->GetController();
	if(!PC) return OGReloadCost(a1, a2);
	if(PC->IsInAircraft()) return OGReloadCost(a1, a2);

	FFortItemEntry ItemEntry = Inventory::GetEntryInInv(PC, a1->ItemEntryGuid);
	if (!ItemEntry.ItemDefinition) return OGReloadCost(a1, a2);

	auto WeaponData = a1->WeaponData;
	auto WorldInventory = PC->WorldInventory;

	OGReloadCost(a1, a2); // isnt needed

	auto AmmoDef = WeaponData->GetAmmoWorldItemDefinition_BP(); // ?!?!

	for (int i = 0; i < WorldInventory->Inventory.ItemInstances.Num(); i++) {
		auto Item = WorldInventory->Inventory.ItemInstances[i];

		if (Item->ItemEntry.ItemDefinition == ItemEntry.ItemDefinition) {
			if (Item->ItemEntry.ItemDefinition->MaxStackSize > 1)
			{
				std::cout << "REMOVING ITEM" << std::endl;
				Inventory::RemoveItem(PC, Item->ItemEntry.ItemGuid, false, a2);
			}
		}
		// else just incase of big pots
		else if (AmmoDef) {
			if (Item->ItemEntry.ItemDefinition == AmmoDef) {
				std::cout << "REMOVING AMMO" << std::endl;
				Inventory::RemoveItem(PC, Item->ItemEntry.ItemGuid, false, a2);
			}
		}
	}

	Inventory::UpdateLoadedAmmo(PC, Pawn->CurrentWeapon); // auto till you drop it
}

void (*OGNetMulticast_Athena_BatchedDamageCues)(AFortPlayerPawnAthena* Pawn, const struct FAthenaBatchedDamageGameplayCues& BatchData);
void NetMulticast_Athena_BatchedDamageCues(AFortPlayerPawnAthena* Pawn, const struct FAthenaBatchedDamageGameplayCues& BatchData) {
	if (!Pawn) {
		return OGNetMulticast_Athena_BatchedDamageCues(Pawn, BatchData);
	}
	//std::cout << "USER IS SHOOTING THE GUN" << std::endl;

	AFortPlayerControllerAthena* PC = (AFortPlayerControllerAthena*)Pawn->GetController();
	if (!PC) return OGNetMulticast_Athena_BatchedDamageCues(Pawn, BatchData);

	auto WorldInventory = PC->WorldInventory;
	if (WorldInventory && Pawn->CurrentWeapon) {
		// soooo pickaxes arent supposed to have ammo
		if (Pawn->CurrentWeapon->WeaponData->bCanBeDropped) {
			Inventory::UpdateLoadedAmmo(PC, Pawn->CurrentWeapon);
		}
	}
	
	// check if the users gun damage is higher then normal? 

	return OGNetMulticast_Athena_BatchedDamageCues(Pawn, BatchData);
}