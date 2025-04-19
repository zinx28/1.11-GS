#pragma once

class Player {
private:
	Player() = default;
public:
	static inline ABuildingSMActor* (*ReplaceBuildingActor)(ABuildingSMActor* a1,
		unsigned int a2,
		TSubclassOf<ABuildingSMActor> a3,
		unsigned int a4,
		int a5,
		unsigned __int8 a6,
		AFortPlayerControllerAthena* a7);

	static UAthenaCharacterItemDefinition* GetRandomDefault(int* OutIdx);

	static inline FRichCurve* (*FindCurve)(UObject* thisPtr, FName a2, FString& a3, char a4);

	static UFortResourceItemDefinition* GetResourceItemDef(EFortResourceType Type);

	static inline void (*OnDamageServer_OG)(ABuildingContainer* Container, float Damage, const struct FGameplayTagContainer& DamageTags, const struct FVector& Momentum, const struct FHitResult& HitInfo, class AController* InstigatedBy, class AActor* DamageCauser, const struct FGameplayEffectContextHandle& EffectContext);
	static void OnDamageServer(ABuildingContainer* Container, float Damage, const struct FGameplayTagContainer& DamageTags, const struct FVector& Momentum, const struct FHitResult& HitInfo, class AFortPlayerControllerAthena* InstigatedBy, class AActor* DamageCauser, const struct FGameplayEffectContextHandle& EffectContext);
	static FFortAthenaLoadout GetLoadout(AFortPlayerControllerAthena* Controller);
	static void EquipSkin(AFortPlayerControllerAthena* Controller, UAthenaCharacterItemDefinition* Skin = nullptr);
	static void ServerLoadingScreenDropped_Hook(AFortPlayerControllerAthena* Controller);

	static inline void (*OGServerAttemptInteract)(AFortPlayerController* PlayerController, AActor* ReceivingActor, UPrimitiveComponent* InteractComponent, ETInteractionType InteractType);
	static void ServerAttemptInteract(AFortPlayerController* PlayerController, AActor* ReceivingActor, UPrimitiveComponent* InteractComponent, ETInteractionType InteractType);


	static void ServerReturnToMainMenu(AFortPlayerController* PlayerController);
	static void ServerExecuteInventoryItem(AFortPlayerController* PlayerController, FGuid& ItemGuid);
	static void ServerSpawnInventoryDrop(AFortPlayerControllerAthena* PC, const struct FGuid& ItemGuid, int32 Count);

	static inline __int64 (*AFortPlayerController_GetAthenaLoadoutWithOverrides_OG)(AFortPlayerControllerAthena* Controller, __int64 a2, __int64 a3);
	static __int64 AFortPlayerController_GetAthenaLoadoutWithOverrides(AFortPlayerControllerAthena* Controller, __int64 a2, __int64 a3);


	static inline void (*ApplyHomeBaseEffectsOnPlayerSetup_OG)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, char a6, unsigned __int8 a7);
	static void ApplyHomeBaseEffectsOnPlayerSetup(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, char a6, unsigned __int8 a7);

	static inline void (*ClientOnPawnDied_OG)(AFortPlayerControllerAthena* Controller, const struct FFortPlayerDeathReport& DeathReport);
	static void ClientOnPawnDied(AFortPlayerControllerAthena* DeadController, const struct FFortPlayerDeathReport& DeathReport);
	
	static void ServerHandlePickup(AFortPlayerPawnAthena* Pawn, class AFortPickup* Pickup, float InFlyTime, const struct FVector& InStartDirection, bool bPlayPickupSound);

	static inline void (*OriginalServerSwapItemsInternal)(AFortQuickBars* AmICooked, EFortQuickBars QuickBarA, int32 SlotIndexA, EFortQuickBars QuickBarB, int32 SlotIndexB);
	static void ServerSwapItemsInternal(AFortQuickBars* AmICooked, EFortQuickBars QuickBarA, int32 SlotIndexA, EFortQuickBars QuickBarB, int32 SlotIndexB);
	
	static inline __int64 (*OnPickupComplete_OG)(AFortPickup* a1);
	static __int64 OnPickupComplete(AFortPickup* a1);

	static inline void (*OrginalAirCraftStartPhase)(AFortGameModeAthena* GameMode);
	static void AirCraftStartPhase(AFortGameModeAthena* GameMode);

	static void ServerEditBuildingActor(AFortPlayerControllerAthena* PC, ABuildingSMActor* BuildingActorToEdit, TSubclassOf<ABuildingSMActor> NewBuildingClass, int32 RotationIterations, bool bMirrored);
	static void ServerRepairBuildingActor(AFortPlayerControllerAthena* PC, ABuildingSMActor* BuildingActorToRepair);
	static void ServerCreateBuildingActor(AFortPlayerControllerAthena* Controller, FBuildingClassData BuildingClassData, FVector_NetQuantize10 BuildLoc, FRotator Rotator, bool bMirrored);
	static void ServerBeginEditingBuildingActor(AFortPlayerController* Player, ABuildingSMActor* Building);
	static void ServerEndEditingBuildingActor(AFortPlayerControllerAthena* PC, ABuildingSMActor* BuildingActorToStopEditing);

	// function doesnt work without orginal hooked
	static inline void (*OrginalServerSpawnDeco)(AFortTrapTool* DecoTool, const FVector& Location, const FRotator& Rotation, ABuildingSMActor* AttachedActor);
	static void ServerSpawnDeco(AFortTrapTool* DecoTool, const FVector& Location, const FRotator& Rotation, ABuildingSMActor* AttachedActor);

	static void ServerPlayEmoteItem(AFortPlayerControllerAthena* PC, UFortMontageItemDefinitionBase* EmoteAsset);
};

//7FF765C5D510 - 7FF7657A0000
