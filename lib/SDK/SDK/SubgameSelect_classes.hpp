#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: SubgameSelect

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "UMG_structs.hpp"
#include "FortniteUI_structs.hpp"
#include "FortniteUI_classes.hpp"


namespace SDK
{

// WidgetBlueprintGeneratedClass SubgameSelect.SubgameSelect_C
// 0x0028 (0x0408 - 0x03E0)
class USubgameSelect_C final : public UFortUIStateWidget_NUI
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x03E0(0x0008)(Transient, DuplicateTransient)
	class UBottomBarWidget_C*                     BottomBar;                                         // 0x03E8(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UBuildWatermark_C*                      BuildWatermark;                                    // 0x03F0(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UCommonWidgetStack*                     MainContentStack;                                  // 0x03F8(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class USafeZone*                              TopBar;                                            // 0x0400(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)

public:
	void ExecuteUbergraph_SubgameSelect(int32 EntryPoint);
	void PushContentWidgetInternal(class UWidget* Widget, const struct FContentPushState& State);
	void OnEnterState(EFortUIState PreviousUIState);
	void Construct();
	void Initialize();
	class UWidget* PopContentWidgetInternal(const struct FContentPushState& State);
	void UpdateHeaderAndFooter(bool HideHeader, bool HideFooter);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"SubgameSelect_C">();
	}
	static class USubgameSelect_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<USubgameSelect_C>();
	}
};
static_assert(alignof(USubgameSelect_C) == 0x000008, "Wrong alignment on USubgameSelect_C");
static_assert(sizeof(USubgameSelect_C) == 0x000408, "Wrong size on USubgameSelect_C");
static_assert(offsetof(USubgameSelect_C, UberGraphFrame) == 0x0003E0, "Member 'USubgameSelect_C::UberGraphFrame' has a wrong offset!");
static_assert(offsetof(USubgameSelect_C, BottomBar) == 0x0003E8, "Member 'USubgameSelect_C::BottomBar' has a wrong offset!");
static_assert(offsetof(USubgameSelect_C, BuildWatermark) == 0x0003F0, "Member 'USubgameSelect_C::BuildWatermark' has a wrong offset!");
static_assert(offsetof(USubgameSelect_C, MainContentStack) == 0x0003F8, "Member 'USubgameSelect_C::MainContentStack' has a wrong offset!");
static_assert(offsetof(USubgameSelect_C, TopBar) == 0x000400, "Member 'USubgameSelect_C::TopBar' has a wrong offset!");

}

