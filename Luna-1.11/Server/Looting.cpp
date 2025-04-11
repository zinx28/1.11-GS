#include "Looting.h"
#include <algorithm> 


FFortLootTierData* Looting::SelectLootTierData(std::vector<FFortLootTierData*> LootTierDatas) {
	float TotalWeight = 0.0f;
	for (const auto& Entry : LootTierDatas) {
		TotalWeight += Entry->Weight;
	}

	float RandomFloat = UKismetMathLibrary::RandomFloat() * TotalWeight;

	float CumulativeProbality = 0.0f;

	for (const auto& Entry : LootTierDatas) {
		CumulativeProbality += Entry->Weight;
		if (RandomFloat <= CumulativeProbality) {
			return Entry;
		}
	}

	return nullptr;
}

FFortLootPackageData* Looting::SelectLootPackage(std::vector<FFortLootPackageData*> LootPackages) {

	float TotalWeight = 0.0f;
	for (const auto& Entry : LootPackages) {
		TotalWeight += Entry->Weight;
	}

	float RandomFloat = UKismetMathLibrary::RandomFloat() * TotalWeight;

	float CumulativeProbality = 0.0f;

	for (const auto& Entry : LootPackages) {
		CumulativeProbality += Entry->Weight;
		if (RandomFloat <= CumulativeProbality) {
			return Entry;
		}
	}

	return nullptr;
}

std::vector<FFortItemEntry> Looting::PickLootDrops(FName LootTierGroup) {

	std::vector<FFortItemEntry> LootDrops;

	UDataTable* LootTierData_Client = StaticLoadObject<UDataTable>("/Game/Items/DataTables/AthenaLootTierData_Client.AthenaLootTierData_Client");

	UDataTable* LootPackages_Client = StaticLoadObject<UDataTable>("/Game/Items/DataTables/AthenaLootPackages_Client.AthenaLootPackages_Client");

	std::vector<FFortLootTierData*> LootTierDatas;
	std::vector<FFortLootPackageData*> LootPackages;

	if (!LootTierData_Client || !LootPackages_Client) return LootDrops;



	std::string LootTierGroupToString = UKismetStringLibrary::Conv_NameToString(LootTierGroup).ToString();

	for (auto& Map : LootTierData_Client->RowMap) {
		FName RowName = Map.First;
		FFortLootTierData* RowData = (FFortLootTierData*)Map.Second;
		std::string TierGroupToString = UKismetStringLibrary::Conv_NameToString(RowData->TierGroup).ToString();
		std::string LootPackageString = UKismetStringLibrary::Conv_NameToString(RowData->LootPackage).ToString();
		if (RowData->TierGroup == LootTierGroup && RowData->Weight != 0) {
			LootTierDatas.push_back(RowData);
		}
	}

	FFortLootTierData* ChosenLootTierData = SelectLootTierData(LootTierDatas);

	if (!ChosenLootTierData) return LootDrops;

	std::string LootPackageString = UKismetStringLibrary::Conv_NameToString(ChosenLootTierData->LootPackage).ToString();

	if (!ChosenLootTierData) return LootDrops;

	for (auto& Map : LootPackages_Client->RowMap) {
		FName RowName = Map.First;
		FFortLootPackageData* RowData = (FFortLootPackageData*)Map.Second;
		string LootPackageIDToString = UKismetStringLibrary::Conv_NameToString(RowData->LootPackageID).ToString();
		if (RowData->LootPackageID == ChosenLootTierData->LootPackage && RowData->Weight != 0.0) {
			LootPackages.push_back(RowData);
		}
	}

	float NumLootPackageDrops = std::floor(ChosenLootTierData->NumLootPackageDrops);

	// i mean if its not in the range it crashes + only supply drops crashes bc of this
	for (size_t I = 0; I < std::min<size_t>(NumLootPackageDrops, (float)LootPackages.size()); I++) {
		auto LootPackage = LootPackages.at(I);

		std::vector<FFortLootPackageData*> LootPackageCalls;

		if (LootPackage->LootPackageCall.ToString().empty()) {
			LootPackageCalls.push_back(LootPackage);
		}
		else {
			for (TPair<FName, uint8*> Map : LootPackages_Client->RowMap) {
				FFortLootPackageData* LootPackageData = (FFortLootPackageData*)Map.Second;
				std::string LootPackageDataString = UKismetStringLibrary::Conv_NameToString(LootPackageData->LootPackageID).ToString();
				if (LootPackageDataString == LootPackage->LootPackageCall.ToString() && LootPackageData->Weight != 0.0) {
					LootPackageCalls.push_back(LootPackageData);
				}
			}
		}

		FFortLootPackageData* LootPackageCall = SelectLootPackage(LootPackageCalls);

		if (!LootPackageCall) continue;

		// saves time bc half of them are just none
		UFortItemDefinition* ItemDef = nullptr;
		FString ConvAsset = UKismetStringLibrary::Conv_NameToString(LootPackageCall->ItemDefinition.ObjectID.AssetPathName);
		if (ConvAsset.ToString() != "None") {
			ItemDef = StaticLoadObject<UFortItemDefinition>(ConvAsset.ToString());
		}

		if (!ItemDef) PickLootDrops(LootTierGroup);

		FFortItemEntry LootDropEntry{};
		LootDropEntry.ItemDefinition = ItemDef;
		LootDropEntry.Count = LootPackageCall->Count;

		LootDrops.push_back(LootDropEntry);
	}

	return LootDrops;
}

std::vector<FFortItemEntry> Looting::PickLootDrops2(FName LootTierGroup) {

	std::vector<FFortItemEntry> LootDrops;

	UDataTable* LootTierData_Client = StaticLoadObject<UDataTable>("/Game/Items/DataTables/LootTierData_Client.LootTierData_Client");

	UDataTable* LootPackages_Client = StaticLoadObject<UDataTable>("/Game/Items/DataTables/LootPackages_Client.LootPackages_Client");

	std::vector<FFortLootTierData*> LootTierDatas;
	std::vector<FFortLootPackageData*> LootPackages;

	if (!LootTierData_Client || !LootPackages_Client) return LootDrops;



	std::string LootTierGroupToString = UKismetStringLibrary::Conv_NameToString(LootTierGroup).ToString();

	for (auto& Map : LootTierData_Client->RowMap) {
		FName RowName = Map.First;
		FFortLootTierData* RowData = (FFortLootTierData*)Map.Second;
		std::string TierGroupToString = UKismetStringLibrary::Conv_NameToString(RowData->TierGroup).ToString();
		std::string LootPackageString = UKismetStringLibrary::Conv_NameToString(RowData->LootPackage).ToString();
		if (RowData->TierGroup == LootTierGroup && RowData->Weight != 0) {
			LootTierDatas.push_back(RowData);
		}
	}

	FFortLootTierData* ChosenLootTierData = SelectLootTierData(LootTierDatas);

	if (!ChosenLootTierData) return LootDrops;

	std::string LootPackageString = UKismetStringLibrary::Conv_NameToString(ChosenLootTierData->LootPackage).ToString();

	if (!ChosenLootTierData) return LootDrops;

	for (auto& Map : LootPackages_Client->RowMap) {
		FName RowName = Map.First;
		FFortLootPackageData* RowData = (FFortLootPackageData*)Map.Second;
		string LootPackageIDToString = UKismetStringLibrary::Conv_NameToString(RowData->LootPackageID).ToString();
		if (RowData->LootPackageID == ChosenLootTierData->LootPackage && RowData->Weight != 0.0) {
			LootPackages.push_back(RowData);
		}
	}

	float NumLootPackageDrops = std::floor(ChosenLootTierData->NumLootPackageDrops);

	for (float I = 0; I < NumLootPackageDrops; I++) {
		auto LootPackage = LootPackages.at(I);

		std::vector<FFortLootPackageData*> LootPackageCalls;

		if (LootPackage->LootPackageCall.ToString().empty()) {
			LootPackageCalls.push_back(LootPackage);
		}
		else {
			for (TPair<FName, uint8*> Map : LootPackages_Client->RowMap) {
				FFortLootPackageData* LootPackageData = (FFortLootPackageData*)Map.Second;
				std::string LootPackageDataString = UKismetStringLibrary::Conv_NameToString(LootPackageData->LootPackageID).ToString();
				if (LootPackageDataString == LootPackage->LootPackageCall.ToString() && LootPackageData->Weight != 0.0) {
					LootPackageCalls.push_back(LootPackageData);
				}
			}
		}

		FFortLootPackageData* LootPackageCall = SelectLootPackage(LootPackageCalls);

		if (!LootPackageCall) continue;

		// saves time bc half of them are just none
		UFortItemDefinition* ItemDef = nullptr;
		FString ConvAsset = UKismetStringLibrary::Conv_NameToString(LootPackageCall->ItemDefinition.ObjectID.AssetPathName);
		if (ConvAsset.ToString() != "None") {
			ItemDef = StaticLoadObject<UFortItemDefinition>(ConvAsset.ToString());
		}
		
		if (!ItemDef) PickLootDrops2(LootTierGroup);

		FFortItemEntry LootDropEntry{};
		LootDropEntry.ItemDefinition = ItemDef;
		LootDropEntry.Count = LootPackageCall->Count;

		LootDrops.push_back(LootDropEntry);
	}

	return LootDrops;
}