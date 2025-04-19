#pragma once
#include "..\framework.h"

class Looting {
private:
	Looting() = default;
public:
	static FFortLootPackageData* SelectLootPackage(std::vector<FFortLootPackageData*> LootPackages);
	static FFortLootTierData* SelectLootTierData(std::vector<FFortLootTierData*> LootTierDatas);
	static std::vector<FFortItemEntry> PickLootDrops(FName LootTierGroup);
};