#pragma once
// Windows Header Files
#include <windows.h>
#include <fstream>
#include <iostream>
#include "./Public/Log.h"
#include <vector>
#include <memory>
#include <codecvt>

static bool bLogVerbose = true;
static bool bMCP = false;

//Program Specific Files
#include "../SDK/SDK.hpp"
#include "../SDK/SDK/FortniteGame_parameters.hpp"
#include "../SDK/SDK/Engine_parameters.hpp"
#include "../SDK/SDK/CoreUObject_parameters.hpp"
using namespace SDK;
using namespace Params;
using namespace std;

inline std::ofstream GameLog("Luna.log");

#include "memcury.h"
#include "MinHook.h"

inline bool bUseGuiLowTaperFade = true;

template<typename T>
inline T* SpawnActor(FTransform Transform, AActor* Owner) {
	AActor* Actor = UGameplayStatics::BeginDeferredActorSpawnFromClass(UWorld::GetWorld(), T::StaticClass(), Transform, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn, Owner);

	return (T*)UGameplayStatics::FinishSpawningActor(Actor, Transform);
}

inline uintptr_t ImageBase = uintptr_t(GetModuleHandle(0));

static UObject* (*StaticFindObjectOG)(UClass*, UObject* Package, const wchar_t* OrigInName, bool ExactClass) = decltype(StaticFindObjectOG)(ImageBase + 0xe07e60);

static UObject* (*StaticLoadObjectOG)(UClass* Class, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename, uint32_t LoadFlags, UObject* Sandbox, bool bAllowObjectReconciliation, void*) = decltype(StaticLoadObjectOG)(ImageBase + 0xe090a0);

inline float GetMaxTickRateHook(UEngine*, float DeltaTime) {
	return 30.f;
}

template <typename T>
static T* StaticFindObject(std::string ObjectName)
{
	auto NameWStr = std::wstring(ObjectName.begin(), ObjectName.end()).c_str();

	return (T*)StaticFindObjectOG(T::StaticClass(), nullptr, NameWStr, false);
}

template<typename T>
inline T* StaticLoadObject(std::string name) {
	T* Object = StaticFindObject<T>(name);

	if (!Object) {
		auto Name = std::wstring(name.begin(), name.end()).c_str();
		Object = (T*)StaticLoadObjectOG(T::StaticClass(), nullptr, Name, nullptr, 0, nullptr, false, nullptr);
	}

	return Object;
}

inline void VirtualHook(void** VFT, int Index, PVOID Hook, void** OG) {
	if (OG)
		*OG = VFT[Index];

	DWORD OldProtect;
	VirtualProtect(VFT[Index], 8, PAGE_EXECUTE_READWRITE, &OldProtect);
	VFT[Index] = Hook;
	VirtualProtect(VFT[Index], 8, OldProtect, &OldProtect);
}

inline int rettrue() {
	return 1;
}

template<typename T>
inline T* SpawnActor(AActor* Owner = nullptr,UClass* OverrideClass = T::StaticClass(),FTransform Transform = {}) {
	AActor* Actor = UGameplayStatics::BeginDeferredActorSpawnFromClass(UWorld::GetWorld(), OverrideClass, Transform, ESpawnActorCollisionHandlingMethod::AlwaysSpawn, Owner);
	return (T*)UGameplayStatics::FinishSpawningActor(Actor, Transform);
}

inline void sinCos(float* ScalarSin, float* ScalarCos, float Value)
{
	float quotient = (0.31830988618f * 0.5f) * Value;
	if (Value >= 0.0f)
	{
		quotient = (float)((int)(quotient + 0.5f));
	}
	else
	{
		quotient = (float)((int)(quotient - 0.5f));
	}
	float y = Value - (2.0f * 3.1415926535897932f) * quotient;

	float sign;
	if (y > 1.57079632679f)
	{
		y = 3.1415926535897932f - y;
		sign = -1.0f;
	}
	else if (y < -1.57079632679f)
	{
		y = -3.1415926535897932f - y;
		sign = -1.0f;
	}
	else
	{
		sign = +1.0f;
	}

	float y2 = y * y;

	*ScalarSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

	float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
	*ScalarCos = sign * p;
}

inline FQuat ConvertRotToQuat(const FRotator& Rot)
{
	const float DEG_TO_RAD = 3.1415926535897932f / (180.f);
	const float DIVIDE_BY_2 = DEG_TO_RAD / 2.f;
	float SP, SY, SR;
	float CP, CY, CR;

	sinCos(&SP, &CP, Rot.Pitch * DIVIDE_BY_2);
	sinCos(&SY, &CY, Rot.Yaw * DIVIDE_BY_2);
	sinCos(&SR, &CR, Rot.Roll * DIVIDE_BY_2);

	FQuat RotationQuat;
	RotationQuat.X = CR * SP * SY - SR * CP * CY;
	RotationQuat.Y = -CR * SP * CY - SR * CP * SY;
	RotationQuat.Z = CR * CP * SY - SR * SP * CY;
	RotationQuat.W = CR * CP * CY + SR * SP * SY;

	return RotationQuat;
}

inline void HookFunction(UClass* Class, UFunction* Func, void* Hook, void** OG, bool bDebugAddresses = true) {

	if (!Func) {
		GameLog << "[HookFunction] NoFunc" << std::endl;
		return;
	}
	GameLog << "[HookFunction] " << Func->GetFullName() << std::endl;

	int VFTIndex = 0;
	std::wstring FuncName = UKismetStringLibrary::Conv_NameToString(Func->Name).ToWString();
	uintptr_t AddressOfString = Memcury::Scanner::FindStringRef(FuncName + L"_Validate").Get();
	bool bHasValidate = false;
	bool bIsVFT = true;

	if (AddressOfString > uintptr_t(Func->ExecFunction)) {
		if (bDebugAddresses) {
			GameLog << "[HookFunction] HasValidate" << std::endl;
		}
		bHasValidate = true;
	}

	/*
	* @TJ
	Technical Explanation
	Some Virtuals with Validation use a JMP instead of a CALL which messes up Finding.
	This checks the distance between the Validate Func and the Implementation Func and if it's over 70 bytes we check for a CALL
	I've never seen a distance more than 70 so this should work for all of these scenarios
	*/
	if (bHasValidate && ((*Memcury::Scanner(uintptr_t(Func->ExecFunction)).ScanFor({ 0xFF, 0x90 }, true, 1).AbsoluteOffset(2).GetAs<uint32_t*>()) - (*Memcury::Scanner(uintptr_t(Func->ExecFunction)).ScanFor({ 0xFF, 0x90 }).AbsoluteOffset(2).GetAs<uint32_t*>()) > 70)) VFTIndex = *Memcury::Scanner(uintptr_t(Func->ExecFunction)).ScanFor({ 0x48,0xFF, 0xA0 }).AbsoluteOffset(3).GetAs<uint32_t*>();
	else VFTIndex = bHasValidate ? *Memcury::Scanner(uintptr_t(Func->ExecFunction)).ScanFor({ 0xFF, 0x90 }, true, 1).AbsoluteOffset(2).GetAs<uint32_t*>() : *Memcury::Scanner(uintptr_t(Func->ExecFunction)).ScanFor({ 0xFF, 0x90 }).AbsoluteOffset(2).GetAs<uint32_t*>();

	if (bDebugAddresses) {
		GameLog << "[HookFunction] ExecFunctionAddr: " << std::hex << uintptr_t(Func->ExecFunction) - ImageBase << std::dec << std::endl;

		GameLog << "[HookFunction] VTableIndex: " << std::hex << VFTIndex / 8 << std::dec << std::endl;
	}

	if (VFTIndex == 0) {
		bIsVFT = false;
	}

	if (!bIsVFT) {
		uintptr_t Address = Memcury::Scanner(uintptr_t(Func->ExecFunction)).ScanFor({ 0xE8 }).RelativeOffset(1).Get();

		GameLog << "[HookFunction] NativeFunctionAddr: " << Address - ImageBase << std::endl;

		MH_CreateHook(LPVOID(Address), Hook, OG);
	}
	else {
		GameLog << "[HookFunction] VTableAddr: " << std::hex << (uintptr_t(Class->DefaultObject->VTable) - ImageBase) << std::endl;
		VirtualHook(Class->DefaultObject->VTable, (VFTIndex / 8), Hook, OG);
	}
}