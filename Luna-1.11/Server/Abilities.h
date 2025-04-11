#pragma once
#include "../framework.h"

inline FGameplayAbilitySpecHandle(*GiveAbility)(UAbilitySystemComponent*, FGameplayAbilitySpecHandle* Handle, const FGameplayAbilitySpec&) = decltype(GiveAbility)(ImageBase + 0x2C7BDC0);
inline bool (*InternalTryActivateAbility)(UAbilitySystemComponent*, FGameplayAbilitySpecHandle Handle, FPredictionKey, UGameplayAbility** OutAbility, void* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData) = decltype(InternalTryActivateAbility)(ImageBase + 0x2C7D040);

void GiveAbilitySet(AFortPawn* Pawn, UFortAbilitySet* Set) {
	for (auto& Ability : Set->GameplayAbilities) {
		if (Ability && Ability->DefaultObject);
		FGameplayAbilitySpec Spec{ -1,-1,-1 };
		Spec.Ability = (UFortGameplayAbility*)Ability->DefaultObject;
		Spec.Level = 1;
		Spec.InputID = -1;
		Spec.SourceObject = nullptr;
		Spec.Handle.Handle = rand();
		GiveAbility(Pawn->AbilitySystemComponent, &Spec.Handle, Spec);
	}
}

void ServerTryActivateAbilityHook(UAbilitySystemComponent* Comp, FGameplayAbilitySpecHandle Handle, bool InputPressed, const struct FPredictionKey& PredictionKey) {
	FGameplayAbilitySpec* SpecToUse = nullptr;

	for (const FGameplayAbilitySpec& Spec : Comp->ActivatableAbilities.Items) {
		if (Spec.Handle.Handle == Handle.Handle) {
			if (!Spec.PendingRemove) {
				SpecToUse = const_cast<FGameplayAbilitySpec*>(&Spec);
			}
		}
	}

	if (!SpecToUse) {
		Comp->ClientActivateAbilityFailed(Handle, PredictionKey.Current);
		return;
	}

	const UGameplayAbility* AbilityToActivate = SpecToUse->Ability;

	if (!AbilityToActivate || AbilityToActivate->NetExecutionPolicy == EGameplayAbilityNetExecutionPolicy::ServerOnly) {
		Comp->ClientActivateAbilityFailed(Handle, PredictionKey.Current);
		return;
	}

	SpecToUse->InputPressed = true;

	UGameplayAbility* InstancedAbility = nullptr;
	FGameplayEventData* TriggerEventData = nullptr;

	if (!InternalTryActivateAbility(Comp, Handle, PredictionKey, &InstancedAbility, nullptr, TriggerEventData)) {
		Comp->ClientActivateAbilityFailed(Handle, PredictionKey.Current);
		SpecToUse->InputPressed = false;
	}
	Comp->ActivatableAbilities.MarkItemDirty(*SpecToUse);
}