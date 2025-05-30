#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: PBWA_S1_Solid

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "FortniteGame_classes.hpp"


namespace SDK
{

// BlueprintGeneratedClass PBWA_S1_Solid.PBWA_S1_Solid_C
// 0x0028 (0x0E78 - 0x0E50)
class APBWA_S1_Solid_C final : public ABuildingWall
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x0E50(0x0008)(Transient, DuplicateTransient)
	int32                                         GnomeWallChance;                                   // 0x0E58(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         GnomeWallMax;                                      // 0x0E5C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          Gnomed;                                            // 0x0E60(0x0001)(Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor)
	uint8                                         Pad_E61[0x7];                                      // 0x0E61(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	class UMaterialInstanceConstant*              GnomeMaterial;                                     // 0x0E68(0x0008)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UStaticMesh*                            GnomeWall;                                         // 0x0E70(0x0008)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

public:
	void ExecuteUbergraph_PBWA_S1_Solid(int32 EntryPoint);
	void ReceiveBeginPlay();
	void UserConstructionScript();

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"PBWA_S1_Solid_C">();
	}
	static class APBWA_S1_Solid_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<APBWA_S1_Solid_C>();
	}
};
static_assert(alignof(APBWA_S1_Solid_C) == 0x000008, "Wrong alignment on APBWA_S1_Solid_C");
static_assert(sizeof(APBWA_S1_Solid_C) == 0x000E78, "Wrong size on APBWA_S1_Solid_C");
static_assert(offsetof(APBWA_S1_Solid_C, UberGraphFrame) == 0x000E50, "Member 'APBWA_S1_Solid_C::UberGraphFrame' has a wrong offset!");
static_assert(offsetof(APBWA_S1_Solid_C, GnomeWallChance) == 0x000E58, "Member 'APBWA_S1_Solid_C::GnomeWallChance' has a wrong offset!");
static_assert(offsetof(APBWA_S1_Solid_C, GnomeWallMax) == 0x000E5C, "Member 'APBWA_S1_Solid_C::GnomeWallMax' has a wrong offset!");
static_assert(offsetof(APBWA_S1_Solid_C, Gnomed) == 0x000E60, "Member 'APBWA_S1_Solid_C::Gnomed' has a wrong offset!");
static_assert(offsetof(APBWA_S1_Solid_C, GnomeMaterial) == 0x000E68, "Member 'APBWA_S1_Solid_C::GnomeMaterial' has a wrong offset!");
static_assert(offsetof(APBWA_S1_Solid_C, GnomeWall) == 0x000E70, "Member 'APBWA_S1_Solid_C::GnomeWall' has a wrong offset!");

}

