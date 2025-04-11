#pragma once

#include "./Imgui/imgui.h"
#include "./Imgui/imgui_impl_dx9.h"
#include "./Imgui/imgui_impl_win32.h"
#include <d3d9.h>
#include <wchar.h>
#include <tchar.h>

#pragma comment(lib, "D3d9.lib")

static LPDIRECT3D9              g_pD3D = nullptr;
static LPDIRECT3DDEVICE9        g_pd3dDevice = nullptr;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


void InitImGui() noexcept
{
    ImGui::CreateContext();
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    style.Alpha = 1.0f;
    style.DisabledAlpha = 1.0f;
    style.WindowPadding = ImVec2(20.0f, 20.0f);
    style.WindowRounding = 11.5f;
    style.WindowBorderSize = 0.0f;
    style.WindowMinSize = ImVec2(20.0f, 20.0f);
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_Right;
    style.ChildRounding = 20.0f;
    style.ChildBorderSize = 0.0f;
    style.PopupRounding = 17.39999961853027f;
    style.PopupBorderSize = 1.0f;
    style.FramePadding = ImVec2(20.0f, 3.400000095367432f);
    style.FrameRounding = 11.89999961853027f;
    style.FrameBorderSize = 0.0f;
    style.ItemSpacing = ImVec2(8.899999618530273f, 13.39999961853027f);
    style.ItemInnerSpacing = ImVec2(7.099999904632568f, 1.799999952316284f);
    style.CellPadding = ImVec2(12.10000038146973f, 9.199999809265137f);
    style.IndentSpacing = 0.0f;
    style.ColumnsMinSpacing = 8.699999809265137f;
    style.ScrollbarSize = 11.60000038146973f;
    style.ScrollbarRounding = 15.89999961853027f;
    style.GrabMinSize = 3.700000047683716f;
    style.GrabRounding = 20.0f;
    style.TabRounding = 9.800000190734863f;
    style.TabBorderSize = 0.0f;
    style.TabMinWidthForCloseButton = 0.0f;
    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

    colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.2745098173618317f, 0.3176470696926117f, 0.4509803950786591f, 1.0f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.09411764889955521f, 0.1019607856869698f, 0.1176470592617989f, 1.0f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    colors[ImGuiCol_Border] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.1137254908680916f, 0.125490203499794f, 0.1529411822557449f, 1.0f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.0313725508749485f, 0.9490196108818054f, 0.843137264251709f, 1.0f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.0313725508749485f, 0.9490196108818054f, 0.843137264251709f, 1.0f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.6000000238418579f, 0.9647058844566345f, 0.0313725508749485f, 1.0f);
    colors[ImGuiCol_Button] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.1803921610116959f, 0.1882352977991104f, 0.196078434586525f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.1529411822557449f, 0.1529411822557449f, 0.1529411822557449f, 1.0f);
    colors[ImGuiCol_Header] = ImVec4(0.1411764770746231f, 0.1647058874368668f, 0.2078431397676468f, 1.0f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.105882354080677f, 0.105882354080677f, 0.105882354080677f, 1.0f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    colors[ImGuiCol_Separator] = ImVec4(0.1294117718935013f, 0.1490196138620377f, 0.1921568661928177f, 1.0f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1450980454683304f, 1.0f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.0313725508749485f, 0.9490196108818054f, 0.843137264251709f, 1.0f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    colors[ImGuiCol_Tab] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    colors[ImGuiCol_TabActive] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.125490203499794f, 0.2745098173618317f, 0.572549045085907f, 1.0f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.5215686559677124f, 0.6000000238418579f, 0.7019608020782471f, 1.0f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.03921568766236305f, 0.9803921580314636f, 0.9803921580314636f, 1.0f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.0313725508749485f, 0.9490196108818054f, 0.843137264251709f, 1.0f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    colors[ImGuiCol_TableRowBg] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.9372549057006836f, 0.9372549057006836f, 0.9372549057006836f, 1.0f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.2666666805744171f, 0.2901960909366608f, 1.0f, 1.0f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 0.501960813999176f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 0.501960813999176f);

    style.WindowBorderSize = 3;
    style.ChildBorderSize = 2;
    style.FrameBorderSize = 1;
    style.TabBorderSize = 2;

    style.WindowRounding = 3;
    style.FrameRounding = 3;
    style.TabRounding = 3;
    style.GrabRounding = 3;

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
}

DWORD WINAPI ImGuiThread(LPVOID)
{

    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"Luna", nullptr };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Luna-1.11", WS_OVERLAPPEDWINDOW, 100, 100, 700, 700, nullptr, nullptr, wc.hInstance, nullptr);

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    InitImGui();

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    bool done = false;
    while (!done)
    {
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            g_d3dpp.BackBufferWidth = g_ResizeWidth;
            g_d3dpp.BackBufferHeight = g_ResizeHeight;
            g_ResizeWidth = g_ResizeHeight = 0;
            ResetDevice();
        }

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();


        static float f = 0.0f;

        static int counter = 0;

        // shrug
        RECT rect;
        GetClientRect(hwnd, &rect);

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(rect.right, rect.bottom));

        ImGui::Begin("Server Menu", nullptr, 
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoBringToFrontOnFocus
        );

        static int tab = 0;
        static char NewWeapon[256] = "";
        static int AmountNumber = 1;

        static bool ShowPlayerDetails = false;
        if (ImGui::BeginTabBar("Tabs"))
        {
            if (GameMode::bWorldisReady) {

                if (ImGui::BeginTabItem("Server"))
                {
                    if (ImGui::Button("Start Aircraft")) {
                        UKismetSystemLibrary::ExecuteConsoleCommand(UWorld::GetWorld(), L"startaircraft", nullptr);
                    }
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Players"))
                {
                    auto GameState = reinterpret_cast<AFortGameStateAthena*>(UWorld::GetWorld()->GameState);
                    if (GameState) {
                        
                        static int selectedPlayerIndex = -1;
                  
                        TArray<AFortPlayerState*> PlayerArray = *reinterpret_cast<TArray<AFortPlayerState*>*>(((void*)&(UWorld::GetWorld()->GameState->PlayerArray))); //What the Fuck is wrong with VS? error C2440: 'reinterpret_cast': cannot convert from 'UC::TArray<SDK::APlayerState *>' to 'UC::TArray<SDK::AFortPlayerState *>'
                        ImGui::Text("Players = %d", PlayerArray.Num());
                        ImGui::Text("Max Players = %d", UWorld::GetWorld()->AuthorityGameMode->GameSession->MaxPlayers);

                        ImGui::BeginListBox("", ImVec2(ImGui::GetContentRegionAvail().x, 300));
                        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
                        ImGui::BeginChild("ScrollingRegion", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar);

                        for (int i = 0; i < PlayerArray.Num(); ++i) {
                            if (PlayerArray[i]->bIsABot) continue; // not real player

                            bool isSelected = selectedPlayerIndex == i;
                        
                            std::string UserName = "Test";//reinterpret_cast<AFortPlayerControllerAthena*>(PlayerArray[selectedPlayerIndex]->Owner)->McpProfileGroup->PlayerName.ToString();

                            if (ImGui::Selectable(UserName.c_str(), isSelected)) {
                                selectedPlayerIndex = i;
                            }
                        }
                        ImGui::EndChild();
                        ImGui::PopStyleVar();
                        ImGui::EndListBox();

                        if (selectedPlayerIndex != -1) {
                            if (ImGui::Button("View Details")) {
                                ShowPlayerDetails = true;
                            }
                        }

                        if (ShowPlayerDetails) {
                            std::string UserName = "Test";//reinterpret_cast<AFortPlayerControllerAthena*>(PlayerArray[selectedPlayerIndex]->Owner)->McpProfileGroup->PlayerName.ToString();

                            auto PlayerInfo = PlayerArray[selectedPlayerIndex];
                            ImGui::Begin("Player Details");
                            ImGui::Text("Username: %s", UserName);
                            ImGui::Text("Ping: %s", PlayerInfo->Ping);
                            ImGui::Text("ID: %d", PlayerInfo->PlayerID);
                            if ((AFortPlayerControllerAthena*)PlayerInfo->Owner) {
                                AFortPlayerControllerAthena* PlayerController = (AFortPlayerControllerAthena*)PlayerInfo->Owner;
                                if (PlayerController->Pawn) {
                                    ImGui::InputText("Weapon ID", NewWeapon, IM_ARRAYSIZE(NewWeapon));
                                 
                                    ImGui::InputInt("Amount", &AmountNumber);

                                    if (ImGui::Button("Fly")) {
                                        PlayerController->Pawn->LaunchPawn({ 0,0,10000 }, false, false);
                                    }

                                    if (ImGui::Button("Give Item")) {
                                        std::string WeaponIDStr(NewWeapon);
                                        std::cout << WeaponIDStr << std::endl;
                                        std::cout << AmountNumber << std::endl;
                                        // findinclude wasnt working and giving the package version?!!?!
                                        std::string CombinedIDss = "FortWeaponRangedItemDefinition " + WeaponIDStr + "." + WeaponIDStr;
                                        UFortWeaponRangedItemDefinition* Weapon = UObject::FindObject<UFortWeaponRangedItemDefinition>(CombinedIDss);//UObject::FindObjectFast<UFortWorldItemDefinition>(WeaponIDStr);
                                        if (Weapon) {
                                            std::cout << Weapon->GetFullName() << std::endl;
                                            Inventory::GiveItem(PlayerController, Weapon, AmountNumber);
                                        }
                                    }
                                }
                            }
                            ImGui::Spacing();

                            ImGui::End();
                        }


                    }

                    ImGui::EndTabItem();
                }


            }
            else {
                if (ImGui::BeginTabItem("Settings"))
                {
                    ImGui::EndTabItem();
                }
                ImGui::Text("Server is still loading <3");
            }
            ImGui::EndTabBar();
        }
        ImGui::End();

        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * clear_color.w * 255.0f), (int)(clear_color.y * clear_color.w * 255.0f), (int)(clear_color.z * clear_color.w * 255.0f), (int)(clear_color.w * 255.0f));
        g_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);

        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}



bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr)
        return false;

    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = nullptr; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam);
        g_ResizeHeight = (UINT)HIWORD(lParam);

        if (g_pd3dDevice != nullptr && g_ResizeWidth > 0 && g_ResizeHeight > 0)
        {
            ResetDevice();
        }

        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}