#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: SplashScreenWidget

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "FortniteUI_classes.hpp"


namespace SDK
{

// WidgetBlueprintGeneratedClass SplashScreenWidget.SplashScreenWidget_C
// 0x0050 (0x0430 - 0x03E0)
class USplashScreenWidget_C final : public UFortSplashScreenWidget
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x03E0(0x0008)(Transient, DuplicateTransient)
	class UCommonActionWidget*                    GamepadActionWidget;                               // 0x03E8(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UHorizontalBox*                         GamepadInputHbox;                                  // 0x03F0(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UCommonTextBlock*                       GamepadInputText;                                  // 0x03F8(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UWidgetSwitcher*                        InputWidgetSwitcher;                               // 0x0400(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UHorizontalBox*                         MobileInputHbox;                                   // 0x0408(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UCommonTextBlock*                       MobileInputText;                                   // 0x0410(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UHorizontalBox*                         MouseInputHBox;                                    // 0x0418(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UCommonTextBlock*                       MouseInputText;                                    // 0x0420(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UCommonLazyImage*                       TitleImage;                                        // 0x0428(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)

public:
	void ExecuteUbergraph_SplashScreenWidget(int32 EntryPoint);
	void OnActivated();
	void OnGameBootableInviteReceived(int32 UserIndex);
	void OnInputMethodChanged(bool bUsingGamepad);
	struct FEventReply OnFocusReceived(const struct FGeometry& MyGeometry, const struct FFocusEvent& InFocusEvent);
	struct FEventReply OnMouseButtonDown(const struct FGeometry& MyGeometry, struct FPointerEvent& MouseEvent);
	void RelinquishInputFocus();
	void SetInputFocus();

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"SplashScreenWidget_C">();
	}
	static class USplashScreenWidget_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<USplashScreenWidget_C>();
	}
};
static_assert(alignof(USplashScreenWidget_C) == 0x000008, "Wrong alignment on USplashScreenWidget_C");
static_assert(sizeof(USplashScreenWidget_C) == 0x000430, "Wrong size on USplashScreenWidget_C");
static_assert(offsetof(USplashScreenWidget_C, UberGraphFrame) == 0x0003E0, "Member 'USplashScreenWidget_C::UberGraphFrame' has a wrong offset!");
static_assert(offsetof(USplashScreenWidget_C, GamepadActionWidget) == 0x0003E8, "Member 'USplashScreenWidget_C::GamepadActionWidget' has a wrong offset!");
static_assert(offsetof(USplashScreenWidget_C, GamepadInputHbox) == 0x0003F0, "Member 'USplashScreenWidget_C::GamepadInputHbox' has a wrong offset!");
static_assert(offsetof(USplashScreenWidget_C, GamepadInputText) == 0x0003F8, "Member 'USplashScreenWidget_C::GamepadInputText' has a wrong offset!");
static_assert(offsetof(USplashScreenWidget_C, InputWidgetSwitcher) == 0x000400, "Member 'USplashScreenWidget_C::InputWidgetSwitcher' has a wrong offset!");
static_assert(offsetof(USplashScreenWidget_C, MobileInputHbox) == 0x000408, "Member 'USplashScreenWidget_C::MobileInputHbox' has a wrong offset!");
static_assert(offsetof(USplashScreenWidget_C, MobileInputText) == 0x000410, "Member 'USplashScreenWidget_C::MobileInputText' has a wrong offset!");
static_assert(offsetof(USplashScreenWidget_C, MouseInputHBox) == 0x000418, "Member 'USplashScreenWidget_C::MouseInputHBox' has a wrong offset!");
static_assert(offsetof(USplashScreenWidget_C, MouseInputText) == 0x000420, "Member 'USplashScreenWidget_C::MouseInputText' has a wrong offset!");
static_assert(offsetof(USplashScreenWidget_C, TitleImage) == 0x000428, "Member 'USplashScreenWidget_C::TitleImage' has a wrong offset!");

}

