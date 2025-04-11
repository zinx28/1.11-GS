#pragma once
#include "..\framework.h"

namespace Looting {
	FFortLootPackageData* SelectLootPackage(std::vector<FFortLootPackageData*> LootPackages);
	FFortLootTierData* SelectLootTierData(std::vector<FFortLootTierData*> LootTierDatas);
	std::vector<FFortItemEntry> PickLootDrops(FName LootTierGroup);
	std::vector<FFortItemEntry> PickLootDrops2(FName LootTierGroup);
}