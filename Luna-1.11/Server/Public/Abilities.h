#pragma once

class Abilities {
private:
	Abilities() = default;
public:
	static inline FGameplayAbilitySpecHandle(*GiveAbility)(UAbilitySystemComponent*, FGameplayAbilitySpecHandle* Handle, const FGameplayAbilitySpec&);
	static inline bool (*InternalTryActivateAbility)(UAbilitySystemComponent*, FGameplayAbilitySpecHandle Handle, FPredictionKey, UGameplayAbility** OutAbility, void* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData);

	static void GiveAbilitySet(AFortPawn* Pawn, UFortAbilitySet* Set);
	static void ServerTryActivateAbilityHook(UAbilitySystemComponent* Comp, FGameplayAbilitySpecHandle Handle, bool InputPressed, const struct FPredictionKey& PredictionKey);
};