#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: BlueprintContext

#include "Basic.hpp"

#include "BlueprintContext_classes.hpp"
#include "BlueprintContext_parameters.hpp"


namespace SDK
{

// Function BlueprintContext.BlueprintContextLibrary.GetContext
// (Final, BlueprintCosmetic, Native, Static, Public, BlueprintCallable, BlueprintPure)
// Parameters:
// class UObject*                          ContextObject                                          (Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
// TSubclassOf<class UBlueprintContextBase>Param_Class                                            (Parm, ZeroConstructor, IsPlainOldData, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
// class UBlueprintContextBase*            ReturnValue                                            (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)

class UBlueprintContextBase* UBlueprintContextLibrary::GetContext(class UObject* ContextObject, TSubclassOf<class UBlueprintContextBase> Param_Class)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = StaticClass()->GetFunction("BlueprintContextLibrary", "GetContext");

	Params::BlueprintContextLibrary_GetContext Parms{};

	Parms.ContextObject = ContextObject;
	Parms.Param_Class = Param_Class;

	auto Flgs = Func->FunctionFlags;
	Func->FunctionFlags |= 0x400;

	GetDefaultObj()->ProcessEvent(Func, &Parms);

	Func->FunctionFlags = Flgs;

	return Parms.ReturnValue;
}

}

