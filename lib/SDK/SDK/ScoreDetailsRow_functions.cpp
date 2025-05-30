#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: ScoreDetailsRow

#include "Basic.hpp"

#include "ScoreDetailsRow_classes.hpp"
#include "ScoreDetailsRow_parameters.hpp"


namespace SDK
{

// Function ScoreDetailsRow.ScoreDetailsRow_C.UpdateRow
// (Public, BlueprintCallable, BlueprintEvent)
// Parameters:
// class FText                             Param_PlayerName                                       (BlueprintVisible, BlueprintReadOnly, Parm)
// int32                                   Param_TotalScore                                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
// int32                                   Param_Combat                                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
// int32                                   Param_Building                                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
// int32                                   Param_Utility                                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void UScoreDetailsRow_C::UpdateRow(const class FText& Param_PlayerName, int32 Param_TotalScore, int32 Param_Combat, int32 Param_Building, int32 Param_Utility)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("ScoreDetailsRow_C", "UpdateRow");

	Params::ScoreDetailsRow_C_UpdateRow Parms{};

	Parms.Param_PlayerName = std::move(Param_PlayerName);
	Parms.Param_TotalScore = Param_TotalScore;
	Parms.Param_Combat = Param_Combat;
	Parms.Param_Building = Param_Building;
	Parms.Param_Utility = Param_Utility;

	UObject::ProcessEvent(Func, &Parms);
}

}

