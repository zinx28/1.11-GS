#pragma once

class Inventory {
private: 
	Inventory() = default;
public:
	static inline UFortResourceItemDefinition* Wood;
	static inline UFortResourceItemDefinition* Stone;
	static inline UFortResourceItemDefinition* Metal;

	static int GetMaxAmmo(UFortWeaponItemDefinition* ItemDef);
	static void Update(AFortPlayerControllerAthena* PC, FFortItemEntry* Entry = nullptr);

	static int GetOpenSlot(AFortPlayerControllerAthena* PC);
	static int GetWeaponSlot(AFortPlayerControllerAthena* PC, FGuid Item);

	static UFortWorldItem* GetItemInInv(AFortPlayerControllerAthena* PC, UFortItemDefinition* Def);
	static FFortItemEntry GetEntryInInv(AFortPlayerControllerAthena* PC, FGuid GUID);
	static FGuid GetItemInSlot(AFortPlayerControllerAthena* PC, int Slot, EFortQuickBars QB = EFortQuickBars::Primary);
	static std::pair<EFortQuickBars, int> GetItemSlot(AFortPlayerControllerAthena* PC, FGuid GUID);
	static void SpawnPickup(UFortItemDefinition* Item, FVector Loc, int Count, int32 LoadedAmmo = -1);

	static void RemoveItem(AFortPlayerControllerAthena* PC, FGuid GUID, bool ShouldSpawnItem = true, int Amount = -1, int ShouldINotSwap = false);

	// just copiewd befre you removed
	static EFortQuickBars GetQuickBars(UFortItemDefinition* Def);
	static bool IsPrimaryQuickBar(UFortItemDefinition* Def);
	static int32 GetPrimaryQuickBarItems(AFortPlayerControllerAthena* PC);
	static UFortWorldItem* GiveItem(AFortPlayerControllerAthena* PC, UFortItemDefinition* ItemDef, int Count = 1, int Slot = -1, int LoadedAmmo = -1, bool AutoEquip = false);

	static void UpdateLoadedAmmo(AFortPlayerControllerAthena* PC, AFortWeapon* Weapon/*, int Ammo*/);
};