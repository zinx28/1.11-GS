#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: B_Fragment_Container

#include "Basic.hpp"

#include "GameplayAbilities_structs.hpp"
#include "E_OutlanderFragmentTypes_structs.hpp"
#include "GameplayTags_structs.hpp"
#include "Engine_structs.hpp"
#include "CoreUObject_structs.hpp"
#include "FortniteGame_structs.hpp"
#include "FortniteGame_classes.hpp"


namespace SDK
{

// BlueprintGeneratedClass B_Fragment_Container.B_Fragment_Container_C
// 0x0370 (0x10D0 - 0x0D60)
class AB_Fragment_Container_C final : public ABuildingSMActor
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x0D60(0x0008)(Transient, DuplicateTransient)
	class UParticleSystemComponent*               P_LightOn;                                         // 0x0D68(0x0008)(BlueprintVisible, ZeroConstructor, IsPlainOldData, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class UStaticMeshComponent*                   Orb_Mesh;                                          // 0x0D70(0x0008)(BlueprintVisible, ZeroConstructor, IsPlainOldData, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class UParticleSystemComponent*               P_ResOut;                                          // 0x0D78(0x0008)(BlueprintVisible, ZeroConstructor, IsPlainOldData, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class UParticleSystemComponent*               P_Orb_PickupEffect;                                // 0x0D80(0x0008)(BlueprintVisible, ZeroConstructor, IsPlainOldData, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class UCapsuleComponent*                      BlockingCollision;                                 // 0x0D88(0x0008)(BlueprintVisible, ZeroConstructor, IsPlainOldData, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USkeletalMeshComponent*                 Container_SK;                                      // 0x0D90(0x0008)(BlueprintVisible, ZeroConstructor, IsPlainOldData, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USceneComponent*                        RotationRoot;                                      // 0x0D98(0x0008)(BlueprintVisible, ZeroConstructor, IsPlainOldData, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USceneComponent*                        VerticalMovement;                                  // 0x0DA0(0x0008)(BlueprintVisible, ZeroConstructor, IsPlainOldData, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class UBoxComponent*                          Awaken_Collision;                                  // 0x0DA8(0x0008)(BlueprintVisible, ZeroConstructor, IsPlainOldData, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USphereComponent*                       MiniMapCollision;                                  // 0x0DB0(0x0008)(BlueprintVisible, ZeroConstructor, IsPlainOldData, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class UFortMiniMapComponent*                  MiniMapLoc;                                        // 0x0DB8(0x0008)(BlueprintVisible, ZeroConstructor, IsPlainOldData, NonTransactional, NoDestructor, HasGetValueTypeHash)
	float                                         VerticalMovementTimeline_Z_Offset_E77B23F44312E9BD5DA6EF9ACE127DE4; // 0x0DC0(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	ETimelineDirection                            VerticalMovementTimeline__Direction_E77B23F44312E9BD5DA6EF9ACE127DE4; // 0x0DC4(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_DC5[0x3];                                      // 0x0DC5(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	class UTimelineComponent*                     VerticalMovementTimeline;                          // 0x0DC8(0x0008)(BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FGameplayTagContainer                  TC_HasFragmentAbility;                             // 0x0DD0(0x0020)(Edit, BlueprintVisible, DisableEditOnInstance)
	struct FGameplayTagContainer                  TC_LlamaFragment;                                  // 0x0DF0(0x0020)(Edit, BlueprintVisible, DisableEditOnInstance, SaveGame)
	struct FGameplayTagContainer                  TC_ChargeFragmentTag;                              // 0x0E10(0x0020)(Edit, BlueprintVisible, DisableEditOnInstance)
	struct FGameplayTagContainer                  TC_LlamaFragmentTag;                               // 0x0E30(0x0020)(Edit, BlueprintVisible, DisableEditOnInstance)
	struct FGameplayTag                           Event_FragmentCollected;                           // 0x0E50(0x0008)(Edit, BlueprintVisible, DisableEditOnInstance, NoDestructor, HasGetValueTypeHash)
	struct FGameplayEventData                     SentFragment;                                      // 0x0E58(0x00A8)(Edit, BlueprintVisible, DisableEditOnInstance)
	E_OutlanderFragmentTypes                      FragmentType;                                      // 0x0F00(0x0001)(Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnInstance, SaveGame, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_F01[0x3];                                      // 0x0F01(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	struct FLinearColor                           ChargeFragmentColor;                               // 0x0F04(0x0010)(Edit, BlueprintVisible, DisableEditOnInstance, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FLinearColor                           LlamaFragmentColor;                                // 0x0F14(0x0010)(Edit, BlueprintVisible, DisableEditOnInstance, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_F24[0x4];                                      // 0x0F24(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class UFortAmmoItemDefinition*                FragmentAmmoData;                                  // 0x0F28(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class AActor*                                 Current_Outlander;                                 // 0x0F30(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class AFortPlayerPawn*                        InteractingPlayerPawn;                             // 0x0F38(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UClass*                                 GE_Outlander_LlamaFragment;                        // 0x0F40(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UClass*                                 GE_ClearFragmentCooldown;                          // 0x0F48(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UClass*                                 GE_Outlander_FragmentTeamSpeedBost;                // 0x0F50(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UClass*                                 FortPawnFilter;                                    // 0x0F58(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         LlamaFragmentPercent;                              // 0x0F60(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         RotateToPlayerSpeed;                               // 0x0F64(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         LastInteractStartTime;                             // 0x0F68(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         DelayedDestroyTime;                                // 0x0F6C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         NumberOfTimeToPingMap;                             // 0x0F70(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         NumberOfMapPings;                                  // 0x0F74(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          IsAnyOutlanderStillAround;                         // 0x0F78(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor)
	bool                                          CanInteract;                                       // 0x0F79(0x0001)(Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnInstance, SaveGame, IsPlainOldData, NoDestructor)
	bool                                          IsAwake;                                           // 0x0F7A(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor)
	bool                                          HasLoot;                                           // 0x0F7B(0x0001)(Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor)
	bool                                          IsOpen;                                            // 0x0F7C(0x0001)(Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, RepNotify, NoDestructor)
	bool                                          bIsUP;                                             // 0x0F7D(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor)
	bool                                          IsOn;                                              // 0x0F7E(0x0001)(Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, RepNotify, NoDestructor)
	uint8                                         Pad_F7F[0x1];                                      // 0x0F7F(0x0001)(Fixing Size After Last Property [ Dumper-7 ])
	class UMaterialInstanceDynamic*               Container_Base_Mat;                                // 0x0F80(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UMaterialInstanceDynamic*               Container_Screen_mat;                              // 0x0F88(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UMaterialInstanceDynamic*               Container_Light_mat;                               // 0x0F90(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UMaterialInstanceDynamic*               Orb_Mat;                                           // 0x0F98(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class USoundBase*                             Orb_Turn_On_Sound;                                 // 0x0FA0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class USoundBase*                             Orb_Hello_Sound;                                   // 0x0FA8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class USoundBase*                             Orb_Hover_Sound;                                   // 0x0FB0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class USoundBase*                             Orb_Goodbye_Sound;                                 // 0x0FB8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class USoundBase*                             Orb_Thanks_Sound;                                  // 0x0FC0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class FText                                   InteractLlamaFragment;                             // 0x0FC8(0x0018)(Edit, BlueprintVisible, DisableEditOnInstance)
	class FText                                   InteractChargeFragment;                            // 0x0FE0(0x0018)(Edit, BlueprintVisible, DisableEditOnInstance)
	class FText                                   InteractNonOutlander;                              // 0x0FF8(0x0018)(Edit, BlueprintVisible, DisableEditOnInstance)
	class FText                                   PickupLlamaFragment;                               // 0x1010(0x0018)(Edit, BlueprintVisible, DisableEditOnInstance)
	class FText                                   PickupChargeFragment;                              // 0x1028(0x0018)(Edit, BlueprintVisible, DisableEditOnInstance)
	class UAudioComponent*                        OrbAudioComponent;                                 // 0x1040(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          IsOrbTaken;                                        // 0x1048(0x0001)(Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, RepNotify, NoDestructor)
	uint8                                         Pad_1049[0x7];                                     // 0x1049(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	class FText                                   FailedOutlanderOnlyOneLlama;                       // 0x1050(0x0018)(Edit, BlueprintVisible, DisableEditOnInstance)
	class FText                                   FailedOutlanderMaxFragHeldDefault;                 // 0x1068(0x0018)(Edit, BlueprintVisible, DisableEditOnInstance)
	class FText                                   FailedOutlanderActivatedButDoesNotYetPossessFragmentAbility; // 0x1080(0x0018)(Edit, BlueprintVisible, DisableEditOnInstance)
	class FText                                   FailedNonOutlanderActivated;                       // 0x1098(0x0018)(Edit, BlueprintVisible, DisableEditOnInstance)
	class UForceFeedbackEffect*                   FF_Interact;                                       // 0x10B0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UForceFeedbackEffect*                   FFInteractSoft;                                    // 0x10B8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UAnimSequence*                          DeployAnim;                                        // 0x10C0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UAnimSequence*                          UndeployAnim;                                      // 0x10C8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

public:
	void ExecuteUbergraph_B_Fragment_Container(int32 EntryPoint);
	void AnimationComplete();
	void PlayAnimation(class UAnimSequence* AnimToPlay);
	void SoftFeedback();
	void MultiFeedback();
	void BlueprintOnBeginInteract();
	void Reset_Activation();
	void StartHide();
	void ShowOnMiniMap();
	void MoveDown();
	void PowerDown();
	void MoveUp();
	void ReceiveTick(float DeltaSeconds);
	void BndEvt__Awaken_Collision_K2Node_ComponentBoundEvent_111_ComponentEndOverlapSignature__DelegateSignature(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	void BndEvt__Awaken_Collision_K2Node_ComponentBoundEvent_108_ComponentBeginOverlapSignature__DelegateSignature(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const struct FHitResult& SweepResult);
	void ActivateFX();
	void BlueprintOnInteract(const class AFortPawn* InteractingPawn);
	void OnDeathServer(float Damage, const struct FGameplayTagContainer& DamageTags, const struct FVector& Momentum, const struct FHitResult& HitInfo, class AController* InstigatedBy, class AActor* DamageCauser, const struct FGameplayEffectContextHandle& EffectContext);
	void ReceiveBeginPlay();
	void VerticalMovementTimeline__down__EventFunc();
	void VerticalMovementTimeline__Up__EventFunc();
	void VerticalMovementTimeline__UpdateFunc();
	void VerticalMovementTimeline__FinishedFunc();
	void UserConstructionScript();
	class FText BlueprintGetInteractionString(class AFortPawn* InteractingPawn);
	void OnRep_BuffType();
	void DelayedDestroy();
	void OnRep_IsOpen();
	void UpdateShouldTick();
	void SetAwake(bool NewAwake);
	void SetOutlander(class AActor* NewOutlander);
	void OnRep_IsOn();
	void OnRep_IsOrbTaken();
	void ForceFeedbackInteract(bool Soft);

	bool BlueprintCanInteract(class AFortPawn* InteractingPawn) const;
	class FText BlueprintGetFailedInteractionString(class AFortPawn* InteractingPawn) const;
	void IsOutlander(class AFortPawn* Pawn, bool* Param_IsOutlander) const;

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"B_Fragment_Container_C">();
	}
	static class AB_Fragment_Container_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<AB_Fragment_Container_C>();
	}
};
static_assert(alignof(AB_Fragment_Container_C) == 0x000008, "Wrong alignment on AB_Fragment_Container_C");
static_assert(sizeof(AB_Fragment_Container_C) == 0x0010D0, "Wrong size on AB_Fragment_Container_C");
static_assert(offsetof(AB_Fragment_Container_C, UberGraphFrame) == 0x000D60, "Member 'AB_Fragment_Container_C::UberGraphFrame' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, P_LightOn) == 0x000D68, "Member 'AB_Fragment_Container_C::P_LightOn' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, Orb_Mesh) == 0x000D70, "Member 'AB_Fragment_Container_C::Orb_Mesh' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, P_ResOut) == 0x000D78, "Member 'AB_Fragment_Container_C::P_ResOut' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, P_Orb_PickupEffect) == 0x000D80, "Member 'AB_Fragment_Container_C::P_Orb_PickupEffect' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, BlockingCollision) == 0x000D88, "Member 'AB_Fragment_Container_C::BlockingCollision' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, Container_SK) == 0x000D90, "Member 'AB_Fragment_Container_C::Container_SK' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, RotationRoot) == 0x000D98, "Member 'AB_Fragment_Container_C::RotationRoot' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, VerticalMovement) == 0x000DA0, "Member 'AB_Fragment_Container_C::VerticalMovement' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, Awaken_Collision) == 0x000DA8, "Member 'AB_Fragment_Container_C::Awaken_Collision' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, MiniMapCollision) == 0x000DB0, "Member 'AB_Fragment_Container_C::MiniMapCollision' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, MiniMapLoc) == 0x000DB8, "Member 'AB_Fragment_Container_C::MiniMapLoc' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, VerticalMovementTimeline_Z_Offset_E77B23F44312E9BD5DA6EF9ACE127DE4) == 0x000DC0, "Member 'AB_Fragment_Container_C::VerticalMovementTimeline_Z_Offset_E77B23F44312E9BD5DA6EF9ACE127DE4' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, VerticalMovementTimeline__Direction_E77B23F44312E9BD5DA6EF9ACE127DE4) == 0x000DC4, "Member 'AB_Fragment_Container_C::VerticalMovementTimeline__Direction_E77B23F44312E9BD5DA6EF9ACE127DE4' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, VerticalMovementTimeline) == 0x000DC8, "Member 'AB_Fragment_Container_C::VerticalMovementTimeline' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, TC_HasFragmentAbility) == 0x000DD0, "Member 'AB_Fragment_Container_C::TC_HasFragmentAbility' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, TC_LlamaFragment) == 0x000DF0, "Member 'AB_Fragment_Container_C::TC_LlamaFragment' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, TC_ChargeFragmentTag) == 0x000E10, "Member 'AB_Fragment_Container_C::TC_ChargeFragmentTag' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, TC_LlamaFragmentTag) == 0x000E30, "Member 'AB_Fragment_Container_C::TC_LlamaFragmentTag' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, Event_FragmentCollected) == 0x000E50, "Member 'AB_Fragment_Container_C::Event_FragmentCollected' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, SentFragment) == 0x000E58, "Member 'AB_Fragment_Container_C::SentFragment' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, FragmentType) == 0x000F00, "Member 'AB_Fragment_Container_C::FragmentType' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, ChargeFragmentColor) == 0x000F04, "Member 'AB_Fragment_Container_C::ChargeFragmentColor' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, LlamaFragmentColor) == 0x000F14, "Member 'AB_Fragment_Container_C::LlamaFragmentColor' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, FragmentAmmoData) == 0x000F28, "Member 'AB_Fragment_Container_C::FragmentAmmoData' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, Current_Outlander) == 0x000F30, "Member 'AB_Fragment_Container_C::Current_Outlander' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, InteractingPlayerPawn) == 0x000F38, "Member 'AB_Fragment_Container_C::InteractingPlayerPawn' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, GE_Outlander_LlamaFragment) == 0x000F40, "Member 'AB_Fragment_Container_C::GE_Outlander_LlamaFragment' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, GE_ClearFragmentCooldown) == 0x000F48, "Member 'AB_Fragment_Container_C::GE_ClearFragmentCooldown' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, GE_Outlander_FragmentTeamSpeedBost) == 0x000F50, "Member 'AB_Fragment_Container_C::GE_Outlander_FragmentTeamSpeedBost' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, FortPawnFilter) == 0x000F58, "Member 'AB_Fragment_Container_C::FortPawnFilter' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, LlamaFragmentPercent) == 0x000F60, "Member 'AB_Fragment_Container_C::LlamaFragmentPercent' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, RotateToPlayerSpeed) == 0x000F64, "Member 'AB_Fragment_Container_C::RotateToPlayerSpeed' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, LastInteractStartTime) == 0x000F68, "Member 'AB_Fragment_Container_C::LastInteractStartTime' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, DelayedDestroyTime) == 0x000F6C, "Member 'AB_Fragment_Container_C::DelayedDestroyTime' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, NumberOfTimeToPingMap) == 0x000F70, "Member 'AB_Fragment_Container_C::NumberOfTimeToPingMap' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, NumberOfMapPings) == 0x000F74, "Member 'AB_Fragment_Container_C::NumberOfMapPings' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, IsAnyOutlanderStillAround) == 0x000F78, "Member 'AB_Fragment_Container_C::IsAnyOutlanderStillAround' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, CanInteract) == 0x000F79, "Member 'AB_Fragment_Container_C::CanInteract' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, IsAwake) == 0x000F7A, "Member 'AB_Fragment_Container_C::IsAwake' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, HasLoot) == 0x000F7B, "Member 'AB_Fragment_Container_C::HasLoot' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, IsOpen) == 0x000F7C, "Member 'AB_Fragment_Container_C::IsOpen' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, bIsUP) == 0x000F7D, "Member 'AB_Fragment_Container_C::bIsUP' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, IsOn) == 0x000F7E, "Member 'AB_Fragment_Container_C::IsOn' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, Container_Base_Mat) == 0x000F80, "Member 'AB_Fragment_Container_C::Container_Base_Mat' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, Container_Screen_mat) == 0x000F88, "Member 'AB_Fragment_Container_C::Container_Screen_mat' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, Container_Light_mat) == 0x000F90, "Member 'AB_Fragment_Container_C::Container_Light_mat' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, Orb_Mat) == 0x000F98, "Member 'AB_Fragment_Container_C::Orb_Mat' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, Orb_Turn_On_Sound) == 0x000FA0, "Member 'AB_Fragment_Container_C::Orb_Turn_On_Sound' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, Orb_Hello_Sound) == 0x000FA8, "Member 'AB_Fragment_Container_C::Orb_Hello_Sound' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, Orb_Hover_Sound) == 0x000FB0, "Member 'AB_Fragment_Container_C::Orb_Hover_Sound' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, Orb_Goodbye_Sound) == 0x000FB8, "Member 'AB_Fragment_Container_C::Orb_Goodbye_Sound' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, Orb_Thanks_Sound) == 0x000FC0, "Member 'AB_Fragment_Container_C::Orb_Thanks_Sound' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, InteractLlamaFragment) == 0x000FC8, "Member 'AB_Fragment_Container_C::InteractLlamaFragment' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, InteractChargeFragment) == 0x000FE0, "Member 'AB_Fragment_Container_C::InteractChargeFragment' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, InteractNonOutlander) == 0x000FF8, "Member 'AB_Fragment_Container_C::InteractNonOutlander' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, PickupLlamaFragment) == 0x001010, "Member 'AB_Fragment_Container_C::PickupLlamaFragment' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, PickupChargeFragment) == 0x001028, "Member 'AB_Fragment_Container_C::PickupChargeFragment' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, OrbAudioComponent) == 0x001040, "Member 'AB_Fragment_Container_C::OrbAudioComponent' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, IsOrbTaken) == 0x001048, "Member 'AB_Fragment_Container_C::IsOrbTaken' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, FailedOutlanderOnlyOneLlama) == 0x001050, "Member 'AB_Fragment_Container_C::FailedOutlanderOnlyOneLlama' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, FailedOutlanderMaxFragHeldDefault) == 0x001068, "Member 'AB_Fragment_Container_C::FailedOutlanderMaxFragHeldDefault' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, FailedOutlanderActivatedButDoesNotYetPossessFragmentAbility) == 0x001080, "Member 'AB_Fragment_Container_C::FailedOutlanderActivatedButDoesNotYetPossessFragmentAbility' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, FailedNonOutlanderActivated) == 0x001098, "Member 'AB_Fragment_Container_C::FailedNonOutlanderActivated' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, FF_Interact) == 0x0010B0, "Member 'AB_Fragment_Container_C::FF_Interact' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, FFInteractSoft) == 0x0010B8, "Member 'AB_Fragment_Container_C::FFInteractSoft' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, DeployAnim) == 0x0010C0, "Member 'AB_Fragment_Container_C::DeployAnim' has a wrong offset!");
static_assert(offsetof(AB_Fragment_Container_C, UndeployAnim) == 0x0010C8, "Member 'AB_Fragment_Container_C::UndeployAnim' has a wrong offset!");

}

