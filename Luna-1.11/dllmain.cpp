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
    MH_CreateHook(LPVOID(ImageBase + 0x9D0C50), OnDamageServer, (void**)&OnDamageServer_OG);
    MH_CreateHook(LPVOID(ImageBase + 0x5DF2A0), ApplyHomeBaseEffectsOnPlayerSetup, (void**)&ApplyHomeBaseEffectsOnPlayerSetup_OG);
    MH_CreateHook(LPVOID(ImageBase + 0xAE0A20), ClientOnPawnDied, (void**)&ClientOnPawnDied_OG);
    MH_CreateHook(LPVOID(ImageBase + 0x6D6BE0), OnPickupComplete, (void**)&OnPickupComplete_OG);

  

    VirtualHook(AFortPlayerPawnAthena::GetDefaultObj()->VTable, 0x182, ServerHandlePickup, nullptr);
    VirtualHook(AFortQuickBars::GetDefaultObj()->VTable, 0xBF, ServerSwapItemsInternal, (void**)&OriginalServerSwapItemsInternal);
    VirtualHook(AFortPlayerControllerAthena::GetDefaultObj()->VTable, 0x1ED, ServerSpawnInventoryDrop, nullptr);
    VirtualHook(AFortPlayerControllerAthena::GetDefaultObj()->VTable, 0x228, ServerAttemptInteract, (void**)&OGServerAttemptInteract);
    VirtualHook(AFortPlayerControllerAthena::GetDefaultObj()->VTable, 0x232, ServerReturnToMainMenu, nullptr);
    VirtualHook(AFortPlayerControllerAthena::GetDefaultObj()->VTable, 0x1F9, ServerEditBuildingActor, nullptr);
    VirtualHook(AFortPlayerControllerAthena::GetDefaultObj()->VTable, 0x1FD, ServerBeginEditingBuildingActor, nullptr);
    VirtualHook(AFortPlayerControllerAthena::GetDefaultObj()->VTable, 0x1FB, ServerEndEditingBuildingActor, nullptr);
    VirtualHook(AFortPlayerControllerAthena::GetDefaultObj()->VTable, 0x1F7, ServerCreateBuildingActor, nullptr);
    VirtualHook(AFortPlayerControllerAthena::GetDefaultObj()->VTable, 0x1F3, ServerRepairBuildingActor, nullptr);
    VirtualHook(AFortPlayerControllerAthena::GetDefaultObj()->VTable, 0x1AD, ServerPlayEmoteItem, nullptr);
    VirtualHook(AFortTrapTool::GetDefaultObj()->VTable, 0x126, ServerSpawnDeco, (void**)&OrginalServerSpawnDeco); // TRap tool stop joknking it
    // ^^ it isnt decotool but fortraptool

    
    //ServerRepairBuildingActor
    // this instead jumping?!?! pretty sure thats where fortnite normally clears or smth
    //7FF7 65BE 8DA0 ~ 448DA0
    //44CD90 - startaircraftphase
    MH_CreateHook(LPVOID(ImageBase + 0x448DA0), AirCraftStartPhase, (void**)&OrginalAirCraftStartPhase);

    //7FF766167B40 ~ 9C7B40
    MH_CreateHook(LPVOID(ImageBase + 0x9C7B40), ReloadCost, (void**)&OGReloadCost);

    //7FF76628D2A0 ~ AED2A0
    MH_CreateHook(LPVOID(ImageBase + 0xAED2A0), NetMulticast_Athena_BatchedDamageCues, (void**)&OGNetMulticast_Athena_BatchedDamageCues);

    HookFunction(AFortPlayerControllerAthena::StaticClass(), UObject::FindObjectInclude<UFunction>("ServerExecuteInventoryItem"), ServerExecuteInventoryItem, nullptr);
    HookFunction(AFortPlayerControllerAthena::StaticClass(), UObject::FindObjectInclude<UFunction>("ServerLoadingScreenDropped"), ServerLoadingScreenDropped_Hook, nullptr);

    HookFunction(AFortPlayerPawnAthena::StaticClass(), UObject::FindObjectInclude<UFunction>("ServerChoosePart"), rettrue, nullptr);

    HookFunction(UAbilitySystemComponent::StaticClass(), UObject::FindObject<UFunction>("Function GameplayAbilities.AbilitySystemComponent.ServerTryActivateAbility"), ServerTryActivateAbilityHook, nullptr);
    HookFunction(UFortAbilitySystemComponent::StaticClass(), UObject::FindObject<UFunction>("Function GameplayAbilities.AbilitySystemComponent.ServerTryActivateAbility"), ServerTryActivateAbilityHook, nullptr);
    HookFunction(UFortAbilitySystemComponentAthena::StaticClass(), UObject::FindObject<UFunction>("Function GameplayAbilities.AbilitySystemComponent.ServerTryActivateAbility"), ServerTryActivateAbilityHook, nullptr);

    HookFunction(AFortGameModeAthena::StaticClass(), UObject::FindObjectInclude<UFunction>("HandleStartingNewPlayer"), GameMode::HandleStartingNewPlayer, (void**)&GameMode::HandleStartingNewPlayer_OG);

    HookFunction(AFortGameModeAthena::StaticClass(), UObject::FindObjectInclude<UFunction>("SpawnDefaultPawnFor"), GameMode::SpawnDefaultPawnFor, nullptr);

    HookFunction(AFortGameModeAthena::StaticClass(), UObject::FindObject<UFunction>("Function Engine.GameMode.ReadyToStartMatch"), GameMode::ReadyToStartMatch, (void**)&GameMode::ReadyToStartMatch_OG);

    // this is such a troll moment ~ we just need to load it once
    GetResourceItemDef(EFortResourceType::None);

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

