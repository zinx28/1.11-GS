#include "./Server/framework.h"

#include "Server/Public/Driver.h"
#include "Server/Public/GameMode.h"
#include "Server/Public/Abilities.h"
#include "Server/Public/Player.h"
#include "Server/Public/Object.h"
#include "Server/Public/Miscs.h"

#include "Server/Public/Gui.h"

static __int64 (*DispatchRequestOG)(UMcpProfileGroup* a1, void*);

__int64 DispatchRequestHook(UMcpProfileGroup* ProfileGroup, void* RequestContext) {

    *(int*)(__int64(RequestContext) + 0x18) = 3;

    return DispatchRequestOG(ProfileGroup, RequestContext);
}

DWORD WINAPI Main(LPVOID) {
    AllocConsole();
    FILE* File;
    freopen_s(&File, "CONOUT$", "w+", stdout);

    bUseGuiLowTaperFade ? CreateThread(0, 0, ImGuiThread, 0, 0, 0) : nullptr; //idk you just have to put nullptr here

    MH_Initialize();
    Sleep(5000);

    Abilities::GiveAbility = decltype(Abilities::GiveAbility)(ImageBase + 0x2C7BDC0);
    Abilities::InternalTryActivateAbility = decltype(Abilities::InternalTryActivateAbility)(ImageBase + 0x2C7D040);

    Driver::CallPreReplication = decltype(Driver::CallPreReplication)(ImageBase + 0x1761700);
    Driver::CreateChannel = decltype(Driver::CreateChannel)(ImageBase + 0x1AD6A60);
    Driver::SetChannelActor = decltype(Driver::SetChannelActor)(ImageBase + 0x1970310);
    Driver::IsNetRelevantFor = decltype(Driver::IsNetRelevantFor)(ImageBase + 0x1775200);
    Driver::CloseActorChannel = decltype(Driver::CloseActorChannel)(ImageBase + 0x1953080);
    Driver::SendClientAdjustment = decltype(Driver::SendClientAdjustment)(ImageBase + 0x1BE16B0);
    Driver::ReplicateActor = decltype(Driver::ReplicateActor)(ImageBase + 0x196B970);

    GameMode::CreateNetDriver = decltype(GameMode::CreateNetDriver)(ImageBase + 0x1D0CB60);
    GameMode::InitListen = decltype(GameMode::InitListen)(ImageBase + 0x2A72B50);
    GameMode::SetWorld = decltype(GameMode::SetWorld)(ImageBase + 0x1AEFA50);

    Player::ReplaceBuildingActor = decltype(Player::ReplaceBuildingActor)(ImageBase + 0x4BD510);
    Player::FindCurve = decltype(Player::FindCurve)(ImageBase + 0x2E21D0);

    if (bLogVerbose) {
        UKismetSystemLibrary::ExecuteConsoleCommand(UWorld::GetWorld(), L"log LogAbilitySystemComponent VeryVerbose", nullptr);
        UKismetSystemLibrary::ExecuteConsoleCommand(UWorld::GetWorld(), L"log LogAIModule VeryVerbose", nullptr);
        UKismetSystemLibrary::ExecuteConsoleCommand(UWorld::GetWorld(), L"log LogAINavigation VeryVerbose", nullptr);
        UKismetSystemLibrary::ExecuteConsoleCommand(UWorld::GetWorld(), L"log LogAIPerception VeryVerbose", nullptr);
        UKismetSystemLibrary::ExecuteConsoleCommand(UWorld::GetWorld(), L"log LogBuilding VeryVerbose", nullptr);
        UKismetSystemLibrary::ExecuteConsoleCommand(UWorld::GetWorld(), L"log LogFort VeryVerbose", nullptr);
        UKismetSystemLibrary::ExecuteConsoleCommand(UWorld::GetWorld(), L"log LogFortAI VeryVerbose", nullptr);
        UKismetSystemLibrary::ExecuteConsoleCommand(UWorld::GetWorld(), L"log LogFortInventory VeryVerbose", nullptr);
        UKismetSystemLibrary::ExecuteConsoleCommand(UWorld::GetWorld(), L"log LogFortLoot VeryVerbose", nullptr);
        UKismetSystemLibrary::ExecuteConsoleCommand(UWorld::GetWorld(), L"log LogFortQuest VeryVerbose", nullptr);
        UKismetSystemLibrary::ExecuteConsoleCommand(UWorld::GetWorld(), L"log LogFortPlayerPawnAthena VeryVerbose", nullptr);
        UKismetSystemLibrary::ExecuteConsoleCommand(UWorld::GetWorld(), L"log LogFortTeams VeryVerbose", nullptr);
    }

    

    MH_CreateHook(LPVOID(ImageBase + 0x1D58B40), rettrue, nullptr); //UWorld::GetNetMode
    MH_CreateHook(LPVOID(ImageBase + 0x74C0B0), rettrue, nullptr); //Reservation
    MH_CreateHook(LPVOID(ImageBase + 0x19D6900), rettrue, nullptr);
    MH_CreateHook(LPVOID(ImageBase + 0x1D13F30), GetMaxTickRateHook, nullptr);
    MH_CreateHook(LPVOID(ImageBase + 0x1AF10F0), Driver::TickFlush, (void**)&Driver::TickFlush_OG);
    MH_CreateHook(LPVOID(ImageBase + 0x2e72550), DispatchRequestHook, (void**)&DispatchRequestOG);
    MH_CreateHook(LPVOID(ImageBase + 0x1779C60), ActorProcEvent_Hk, (void**)&ActorProcEvent);
    MH_CreateHook(LPVOID(ImageBase + Offsets::ProcessEvent), ProcEvent_Hk, (void**)&ProcEvent);
    MH_CreateHook(LPVOID(ImageBase + 0x9D0C50), Player::OnDamageServer, (void**)&Player::OnDamageServer_OG);
    MH_CreateHook(LPVOID(ImageBase + 0x5DF2A0), Player::ApplyHomeBaseEffectsOnPlayerSetup, (void**)&Player::ApplyHomeBaseEffectsOnPlayerSetup_OG);
    MH_CreateHook(LPVOID(ImageBase + 0xAE0A20), Player::ClientOnPawnDied, (void**)&Player::ClientOnPawnDied_OG);
    MH_CreateHook(LPVOID(ImageBase + 0x6D6BE0), Player::OnPickupComplete, (void**)&Player::OnPickupComplete_OG);

  

    VirtualHook(AFortPlayerPawnAthena::GetDefaultObj()->VTable, 0x182, Player::ServerHandlePickup, nullptr);
    VirtualHook(AFortQuickBars::GetDefaultObj()->VTable, 0xBF, Player::ServerSwapItemsInternal, (void**)&Player::OriginalServerSwapItemsInternal);
    VirtualHook(AFortPlayerControllerAthena::GetDefaultObj()->VTable, 0x1ED, Player::ServerSpawnInventoryDrop, nullptr);
    VirtualHook(AFortPlayerControllerAthena::GetDefaultObj()->VTable, 0x228, Player::ServerAttemptInteract, (void**)&Player::OGServerAttemptInteract);
    VirtualHook(AFortPlayerControllerAthena::GetDefaultObj()->VTable, 0x232, Player::ServerReturnToMainMenu, nullptr);
    VirtualHook(AFortPlayerControllerAthena::GetDefaultObj()->VTable, 0x1F9, Player::ServerEditBuildingActor, nullptr);
    VirtualHook(AFortPlayerControllerAthena::GetDefaultObj()->VTable, 0x1FD, Player::ServerBeginEditingBuildingActor, nullptr);
    VirtualHook(AFortPlayerControllerAthena::GetDefaultObj()->VTable, 0x1FB, Player::ServerEndEditingBuildingActor, nullptr);
    VirtualHook(AFortPlayerControllerAthena::GetDefaultObj()->VTable, 0x1F7, Player::ServerCreateBuildingActor, nullptr);
    VirtualHook(AFortPlayerControllerAthena::GetDefaultObj()->VTable, 0x1F3, Player::ServerRepairBuildingActor, nullptr);
    VirtualHook(AFortPlayerControllerAthena::GetDefaultObj()->VTable, 0x1AD, Player::ServerPlayEmoteItem, nullptr);
    VirtualHook(AFortTrapTool::GetDefaultObj()->VTable, 0x126, Player::ServerSpawnDeco, (void**)&Player::OrginalServerSpawnDeco); // TRap tool stop joknking it
    // ^^ it isnt decotool but fortraptool

    
    //ServerRepairBuildingActor
    // this instead jumping?!?! pretty sure thats where fortnite normally clears or smth
    //7FF7 65BE 8DA0 ~ 448DA0
    //44CD90 - startaircraftphase
    MH_CreateHook(LPVOID(ImageBase + 0x448DA0), Player::AirCraftStartPhase, (void**)&Player::OrginalAirCraftStartPhase);

    //7FF766167B40 ~ 9C7B40
    MH_CreateHook(LPVOID(ImageBase + 0x9C7B40), ReloadCost, (void**)&OGReloadCost);

    //7FF76628D2A0 ~ AED2A0
    MH_CreateHook(LPVOID(ImageBase + 0xAED2A0), NetMulticast_Athena_BatchedDamageCues, (void**)&OGNetMulticast_Athena_BatchedDamageCues);

    HookFunction(AFortPlayerControllerAthena::StaticClass(), UObject::FindObjectInclude<UFunction>("ServerExecuteInventoryItem"), Player::ServerExecuteInventoryItem, nullptr);
    HookFunction(AFortPlayerControllerAthena::StaticClass(), UObject::FindObjectInclude<UFunction>("ServerLoadingScreenDropped"), Player::ServerLoadingScreenDropped_Hook, nullptr);

    HookFunction(AFortPlayerPawnAthena::StaticClass(), UObject::FindObjectInclude<UFunction>("ServerChoosePart"), rettrue, nullptr);

    HookFunction(UAbilitySystemComponent::StaticClass(), UObject::FindObject<UFunction>("Function GameplayAbilities.AbilitySystemComponent.ServerTryActivateAbility"), Abilities::ServerTryActivateAbilityHook, nullptr);
    HookFunction(UFortAbilitySystemComponent::StaticClass(), UObject::FindObject<UFunction>("Function GameplayAbilities.AbilitySystemComponent.ServerTryActivateAbility"), Abilities::ServerTryActivateAbilityHook, nullptr);
    HookFunction(UFortAbilitySystemComponentAthena::StaticClass(), UObject::FindObject<UFunction>("Function GameplayAbilities.AbilitySystemComponent.ServerTryActivateAbility"), Abilities::ServerTryActivateAbilityHook, nullptr);

    HookFunction(AFortGameModeAthena::StaticClass(), UObject::FindObjectInclude<UFunction>("HandleStartingNewPlayer"), GameMode::HandleStartingNewPlayer, (void**)&GameMode::HandleStartingNewPlayer_OG);

    HookFunction(AFortGameModeAthena::StaticClass(), UObject::FindObjectInclude<UFunction>("SpawnDefaultPawnFor"), GameMode::SpawnDefaultPawnFor, nullptr);

    HookFunction(AFortGameModeAthena::StaticClass(), UObject::FindObject<UFunction>("Function Engine.GameMode.ReadyToStartMatch"), GameMode::ReadyToStartMatch, (void**)&GameMode::ReadyToStartMatch_OG);

    Player::GetResourceItemDef(EFortResourceType::None);

    uintptr_t GIsClientAddr = (ImageBase + 0x5BAA38F);
    *(bool*)GIsClientAddr = false;

    uintptr_t GIsServerAddr = ImageBase + 0x5BAA390;
    *(bool*)GIsServerAddr = true;

    MH_EnableHook(MH_ALL_HOOKS);

    UKismetSystemLibrary::ExecuteConsoleCommand(UWorld::GetWorld(), L"open Athena_Terrain", nullptr);
    UWorld::GetWorld()->OwningGameInstance->LocalPlayers.Remove(0);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,DWORD reason,LPVOID lpReserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, Main, 0, 0, 0);
        break;
    }
    return TRUE;
}

