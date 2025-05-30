#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: PlayerPawn_Athena

#include "Basic.hpp"

#include "GameplayAbilities_structs.hpp"
#include "GameplayTags_structs.hpp"
#include "Engine_structs.hpp"
#include "CoreUObject_structs.hpp"
#include "PlayerPawn_Athena_Generic_classes.hpp"


namespace SDK
{

// BlueprintGeneratedClass PlayerPawn_Athena.PlayerPawn_Athena_C
// 0x0280 (0x24F0 - 0x2270)
class APlayerPawn_Athena_C final : public APlayerPawn_Athena_Generic_C
{
public:
	uint8                                         Pad_2265[0x3];                                     // 0x2265(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	struct FPointerToUberGraphFrame               UberGraphFrame_PlayerPawn_Athena_C;                // 0x2268(0x0008)(Transient, DuplicateTransient)
	float                                         Storm_Audio_Fader_Volume_8F54E8DB44CB132992E4EBA6F5FAF86B; // 0x2270(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	ETimelineDirection                            Storm_Audio_Fader__Direction_8F54E8DB44CB132992E4EBA6F5FAF86B; // 0x2274(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_2275[0x3];                                     // 0x2275(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	class UTimelineComponent*                     Storm_Audio_Fader;                                 // 0x2278(0x0008)(BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         LightningFlashTL_LERP_C86EEA494C7B742DC045759B630397B7; // 0x2280(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	ETimelineDirection                            LightningFlashTL__Direction_C86EEA494C7B742DC045759B630397B7; // 0x2284(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_2285[0x3];                                     // 0x2285(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	class UTimelineComponent*                     LightningFlashTL;                                  // 0x2288(0x0008)(BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class USkeletalMeshComponent*                 TargetHead;                                        // 0x2290(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class USkeletalMeshComponent*                 TargetBody;                                        // 0x2298(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	TArray<class UMaterialInterface*>             PawnHeadMaterials_0;                               // 0x22A0(0x0010)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	TArray<class UMaterialInterface*>             PawnBodyMaterials_0;                               // 0x22B0(0x0010)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	class UParticleSystem*                        P_IncendiaryRound;                                 // 0x22C0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UParticleSystem*                        P_MakeItRain;                                      // 0x22C8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FGameplayTagContainer                  TC_FlakVest;                                       // 0x22D0(0x0020)(Edit, BlueprintVisible, DisableEditOnInstance)
	struct FGameplayEventData                     Event_Data;                                        // 0x22F0(0x00A8)(Edit, BlueprintVisible, DisableEditOnInstance)
	struct FGameplayTag                           EventSpawnEffect;                                  // 0x2398(0x0008)(Edit, BlueprintVisible, DisableEditOnInstance, NoDestructor, HasGetValueTypeHash)
	float                                         ShockwaveRefractionRingHeight;                     // 0x23A0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_23A4[0x4];                                     // 0x23A4(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class UParticleSystem*                        P_Shockwave;                                       // 0x23A8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UForceFeedbackEffect*                   ShockwaveForceFeedback;                            // 0x23B0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UClass*                                 ShockwaveCameraShake;                              // 0x23B8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          IsMale;                                            // 0x23C0(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor)
	uint8                                         Pad_23C1[0x7];                                     // 0x23C1(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	class AFortWeapon*                            MenuGoingCommandowWeapon;                          // 0x23C8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class USoundBase*                             SafeZonePassThroughSound;                          // 0x23D0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          bHasBeenOutsideSafeZone;                           // 0x23D8(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor)
	uint8                                         Pad_23D9[0x3];                                     // 0x23D9(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	struct FLinearColor                           ThreatColor;                                       // 0x23DC(0x0010)(Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_23EC[0x4];                                     // 0x23EC(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class USoundBase*                             PlayerKilledSound;                                 // 0x23F0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UParticleSystemComponent*               Contrail_A;                                        // 0x23F8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UParticleSystemComponent*               Contrail_B;                                        // 0x2400(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UParticleSystemComponent*               Contrail_C;                                        // 0x2408(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UParticleSystemComponent*               Contrail_D;                                        // 0x2410(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          bContrailReady;                                    // 0x2418(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor)
	uint8                                         Pad_2419[0x7];                                     // 0x2419(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	TArray<class UParticleSystem*>                Contrails;                                         // 0x2420(0x0010)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	class UParticleSystem*                        ActiveContrail;                                    // 0x2430(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          bLiveContrail;                                     // 0x2438(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor)
	uint8                                         Pad_2439[0x7];                                     // 0x2439(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	class UParticleSystemComponent*               Vapor_Effect;                                      // 0x2440(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UParticleSystemComponent*               WindDebrisParticles;                               // 0x2448(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UParticleSystemComponent*               FallingRainParticles;                              // 0x2450(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                LightningSpawnLocation;                            // 0x2458(0x000C)(Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         LightningIntensityMin;                             // 0x2464(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         LightningIntensityMax;                             // 0x2468(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_246C[0x4];                                     // 0x246C(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class AActor*                                 SafeZoneActor;                                     // 0x2470(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         LightningIntensity;                                // 0x2478(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_247C[0x4];                                     // 0x247C(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class UPointLightComponent*                   RandomLightningLight;                              // 0x2480(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         LightningTimelinePlaySpeedMin;                     // 0x2488(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         LightningTimelinePlaySpeedMax;                     // 0x248C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         LightningFlashDiameter;                            // 0x2490(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         LightningFlashHeight;                              // 0x2494(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         LightningFlashRepeatDelayMin;                      // 0x2498(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         LightningFlashRepeatDelayMax;                      // 0x249C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class AEmitterCameraLensEffectBase*           RainCameraLensParticles;                           // 0x24A0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         _ChanceOfLightningMesh;                            // 0x24A8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          ShowInvulnerableVisuals;                           // 0x24AC(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor)
	uint8                                         Pad_24AD[0x3];                                     // 0x24AD(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	class UAudioComponent*                        StormAudioLoop_Inst;                               // 0x24B0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         StormAudioVolume;                                  // 0x24B8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkydiveAudioGroundVolumeScale;                     // 0x24BC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkydiveMovementVolumeScale;                        // 0x24C0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_24C4[0x4];                                     // 0x24C4(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class UAudioComponent*                        FallingAudioLoop_Inst;                             // 0x24C8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          bIsPlayingFallingSound;                            // 0x24D0(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor)
	uint8                                         Pad_24D1[0x3];                                     // 0x24D1(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         PlayerAttributes_Speed_Walk;                       // 0x24D4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         PlayerAttributes_Speed_Run;                        // 0x24D8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         PlayerAttributes_Speed_Sprint;                     // 0x24DC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         MaxTrailsLOD;                                      // 0x24E0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

public:
	void ExecuteUbergraph_PlayerPawn_Athena(int32 EntryPoint);
	void OnExitedWaterVolume();
	void OnEnteredWaterVolume();
	void Update_Parachute_and_Falling_Audio();
	void Start_Storm_Audio_Fader();
	void Play_Lightning_Flash_Audio(const struct FVector& Location);
	void Remove_Storm_Audio();
	void Add_Storm_Audio();
	void UpdateInvulnerableVisuals();
	void ZapFX(int32 ZapCount);
	void RandomLightningFlashesRepeat();
	void StartRandomLightningFlashes();
	void RemoveStormFX();
	void AddStormFX();
	void GameplayCue_Athena_Player_BeingRevivedFromDBNO(EGameplayCueEvent EventType, const struct FGameplayCueParameters& Parameters);
	void ContrailCheck();
	void GameplayCue_Athena_Equipping(EGameplayCueEvent EventType, const struct FGameplayCueParameters& Parameters);
	void GameplayCue_Abilities_Activation_DBNOResurrect(EGameplayCueEvent EventType, const struct FGameplayCueParameters& Parameters);
	void ReceiveTick(float DeltaSeconds);
	void OnDeathPlayEffects(float Damage, const struct FGameplayTagContainer& DamageTags, const struct FVector& Momentum, const struct FHitResult& HitInfo, class AFortPawn* InstigatedBy, class AActor* DamageCauser, const struct FGameplayEffectContextHandle& EffectContext);
	void SafeZoneStatusChanged();
	void GameplayCue_Athena_OutsideSafeZone(EGameplayCueEvent EventType, const struct FGameplayCueParameters& Parameters);
	void ReceiveDestroyed();
	void SelectPawn(class UAnimInstance* AnimInst);
	void ReceiveBeginPlay();
	void SetMenuScreenClassName();
	void GameplayCue_Abilities_Activation_Commando_Shockwave(EGameplayCueEvent EventType, const struct FGameplayCueParameters& Parameters);
	void ReceivePossessed(class AController* NewController);
	void GameplayCue_Abilities_Activation_Generic_HarvestBuff_Tier2(EGameplayCueEvent EventType, const struct FGameplayCueParameters& Parameters);
	void GameplayCue_Abilities_Activation_Generic_HarvestBuff_Tier1(EGameplayCueEvent EventType, const struct FGameplayCueParameters& Parameters);
	void Storm_Audio_Fader__UpdateFunc();
	void Storm_Audio_Fader__FinishedFunc();
	void LightningFlashTL__UpdateFunc();
	void LightningFlashTL__FinishedFunc();
	void UserConstructionScript();
	void InitAthenaFoleyAudio();
	void GetLocationInCircle_XY(struct FVector* LocationLocalSpace);
	void GetParachuteMovementVolumeScale(float* Scale);
	void ApplyParachuteMovementVolumeScale();
	void HandleWaterFX();
	void EnableWaterAudio(bool Is_Entering_Water);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"PlayerPawn_Athena_C">();
	}
	static class APlayerPawn_Athena_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<APlayerPawn_Athena_C>();
	}
};
static_assert(alignof(APlayerPawn_Athena_C) == 0x000010, "Wrong alignment on APlayerPawn_Athena_C");
static_assert(sizeof(APlayerPawn_Athena_C) == 0x0024F0, "Wrong size on APlayerPawn_Athena_C");
static_assert(offsetof(APlayerPawn_Athena_C, UberGraphFrame_PlayerPawn_Athena_C) == 0x002268, "Member 'APlayerPawn_Athena_C::UberGraphFrame_PlayerPawn_Athena_C' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, Storm_Audio_Fader_Volume_8F54E8DB44CB132992E4EBA6F5FAF86B) == 0x002270, "Member 'APlayerPawn_Athena_C::Storm_Audio_Fader_Volume_8F54E8DB44CB132992E4EBA6F5FAF86B' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, Storm_Audio_Fader__Direction_8F54E8DB44CB132992E4EBA6F5FAF86B) == 0x002274, "Member 'APlayerPawn_Athena_C::Storm_Audio_Fader__Direction_8F54E8DB44CB132992E4EBA6F5FAF86B' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, Storm_Audio_Fader) == 0x002278, "Member 'APlayerPawn_Athena_C::Storm_Audio_Fader' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, LightningFlashTL_LERP_C86EEA494C7B742DC045759B630397B7) == 0x002280, "Member 'APlayerPawn_Athena_C::LightningFlashTL_LERP_C86EEA494C7B742DC045759B630397B7' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, LightningFlashTL__Direction_C86EEA494C7B742DC045759B630397B7) == 0x002284, "Member 'APlayerPawn_Athena_C::LightningFlashTL__Direction_C86EEA494C7B742DC045759B630397B7' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, LightningFlashTL) == 0x002288, "Member 'APlayerPawn_Athena_C::LightningFlashTL' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, TargetHead) == 0x002290, "Member 'APlayerPawn_Athena_C::TargetHead' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, TargetBody) == 0x002298, "Member 'APlayerPawn_Athena_C::TargetBody' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, PawnHeadMaterials_0) == 0x0022A0, "Member 'APlayerPawn_Athena_C::PawnHeadMaterials_0' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, PawnBodyMaterials_0) == 0x0022B0, "Member 'APlayerPawn_Athena_C::PawnBodyMaterials_0' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, P_IncendiaryRound) == 0x0022C0, "Member 'APlayerPawn_Athena_C::P_IncendiaryRound' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, P_MakeItRain) == 0x0022C8, "Member 'APlayerPawn_Athena_C::P_MakeItRain' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, TC_FlakVest) == 0x0022D0, "Member 'APlayerPawn_Athena_C::TC_FlakVest' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, Event_Data) == 0x0022F0, "Member 'APlayerPawn_Athena_C::Event_Data' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, EventSpawnEffect) == 0x002398, "Member 'APlayerPawn_Athena_C::EventSpawnEffect' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, ShockwaveRefractionRingHeight) == 0x0023A0, "Member 'APlayerPawn_Athena_C::ShockwaveRefractionRingHeight' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, P_Shockwave) == 0x0023A8, "Member 'APlayerPawn_Athena_C::P_Shockwave' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, ShockwaveForceFeedback) == 0x0023B0, "Member 'APlayerPawn_Athena_C::ShockwaveForceFeedback' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, ShockwaveCameraShake) == 0x0023B8, "Member 'APlayerPawn_Athena_C::ShockwaveCameraShake' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, IsMale) == 0x0023C0, "Member 'APlayerPawn_Athena_C::IsMale' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, MenuGoingCommandowWeapon) == 0x0023C8, "Member 'APlayerPawn_Athena_C::MenuGoingCommandowWeapon' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, SafeZonePassThroughSound) == 0x0023D0, "Member 'APlayerPawn_Athena_C::SafeZonePassThroughSound' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, bHasBeenOutsideSafeZone) == 0x0023D8, "Member 'APlayerPawn_Athena_C::bHasBeenOutsideSafeZone' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, ThreatColor) == 0x0023DC, "Member 'APlayerPawn_Athena_C::ThreatColor' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, PlayerKilledSound) == 0x0023F0, "Member 'APlayerPawn_Athena_C::PlayerKilledSound' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, Contrail_A) == 0x0023F8, "Member 'APlayerPawn_Athena_C::Contrail_A' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, Contrail_B) == 0x002400, "Member 'APlayerPawn_Athena_C::Contrail_B' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, Contrail_C) == 0x002408, "Member 'APlayerPawn_Athena_C::Contrail_C' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, Contrail_D) == 0x002410, "Member 'APlayerPawn_Athena_C::Contrail_D' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, bContrailReady) == 0x002418, "Member 'APlayerPawn_Athena_C::bContrailReady' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, Contrails) == 0x002420, "Member 'APlayerPawn_Athena_C::Contrails' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, ActiveContrail) == 0x002430, "Member 'APlayerPawn_Athena_C::ActiveContrail' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, bLiveContrail) == 0x002438, "Member 'APlayerPawn_Athena_C::bLiveContrail' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, Vapor_Effect) == 0x002440, "Member 'APlayerPawn_Athena_C::Vapor_Effect' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, WindDebrisParticles) == 0x002448, "Member 'APlayerPawn_Athena_C::WindDebrisParticles' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, FallingRainParticles) == 0x002450, "Member 'APlayerPawn_Athena_C::FallingRainParticles' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, LightningSpawnLocation) == 0x002458, "Member 'APlayerPawn_Athena_C::LightningSpawnLocation' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, LightningIntensityMin) == 0x002464, "Member 'APlayerPawn_Athena_C::LightningIntensityMin' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, LightningIntensityMax) == 0x002468, "Member 'APlayerPawn_Athena_C::LightningIntensityMax' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, SafeZoneActor) == 0x002470, "Member 'APlayerPawn_Athena_C::SafeZoneActor' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, LightningIntensity) == 0x002478, "Member 'APlayerPawn_Athena_C::LightningIntensity' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, RandomLightningLight) == 0x002480, "Member 'APlayerPawn_Athena_C::RandomLightningLight' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, LightningTimelinePlaySpeedMin) == 0x002488, "Member 'APlayerPawn_Athena_C::LightningTimelinePlaySpeedMin' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, LightningTimelinePlaySpeedMax) == 0x00248C, "Member 'APlayerPawn_Athena_C::LightningTimelinePlaySpeedMax' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, LightningFlashDiameter) == 0x002490, "Member 'APlayerPawn_Athena_C::LightningFlashDiameter' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, LightningFlashHeight) == 0x002494, "Member 'APlayerPawn_Athena_C::LightningFlashHeight' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, LightningFlashRepeatDelayMin) == 0x002498, "Member 'APlayerPawn_Athena_C::LightningFlashRepeatDelayMin' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, LightningFlashRepeatDelayMax) == 0x00249C, "Member 'APlayerPawn_Athena_C::LightningFlashRepeatDelayMax' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, RainCameraLensParticles) == 0x0024A0, "Member 'APlayerPawn_Athena_C::RainCameraLensParticles' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, _ChanceOfLightningMesh) == 0x0024A8, "Member 'APlayerPawn_Athena_C::_ChanceOfLightningMesh' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, ShowInvulnerableVisuals) == 0x0024AC, "Member 'APlayerPawn_Athena_C::ShowInvulnerableVisuals' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, StormAudioLoop_Inst) == 0x0024B0, "Member 'APlayerPawn_Athena_C::StormAudioLoop_Inst' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, StormAudioVolume) == 0x0024B8, "Member 'APlayerPawn_Athena_C::StormAudioVolume' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, SkydiveAudioGroundVolumeScale) == 0x0024BC, "Member 'APlayerPawn_Athena_C::SkydiveAudioGroundVolumeScale' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, SkydiveMovementVolumeScale) == 0x0024C0, "Member 'APlayerPawn_Athena_C::SkydiveMovementVolumeScale' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, FallingAudioLoop_Inst) == 0x0024C8, "Member 'APlayerPawn_Athena_C::FallingAudioLoop_Inst' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, bIsPlayingFallingSound) == 0x0024D0, "Member 'APlayerPawn_Athena_C::bIsPlayingFallingSound' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, PlayerAttributes_Speed_Walk) == 0x0024D4, "Member 'APlayerPawn_Athena_C::PlayerAttributes_Speed_Walk' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, PlayerAttributes_Speed_Run) == 0x0024D8, "Member 'APlayerPawn_Athena_C::PlayerAttributes_Speed_Run' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, PlayerAttributes_Speed_Sprint) == 0x0024DC, "Member 'APlayerPawn_Athena_C::PlayerAttributes_Speed_Sprint' has a wrong offset!");
static_assert(offsetof(APlayerPawn_Athena_C, MaxTrailsLOD) == 0x0024E0, "Member 'APlayerPawn_Athena_C::MaxTrailsLOD' has a wrong offset!");

}

