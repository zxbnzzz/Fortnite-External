#include <D3D11.h>
#include <D3DX11core.h>
#include <D3DX11.h>
#include <D3DX11tex.h>

#include "../game/cache/actorloop.h"
#include "../framework/ImGui/imgui_impl_dx11.h"
#include "../framework/ImGui/imgui_internal.h"
#include "menu/drawing.h"
#include "menu/menu.h"
#include "other/fonts/font.h"

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.f);
float menu_color[4] = { 1.00f, 0.00f, 0.20f, 0.80f };

int menu_tab = menu.tab;

ImFont* ico = nullptr;
ImFont* ico_combo = nullptr;
ImFont* ico_button = nullptr;
ImFont* ico_grande = nullptr;
ImFont* segu = nullptr;
ImFont* default_segu = nullptr;
ImFont* bold_segu = nullptr;

ID3D11Device* d3d_device;
ID3D11DeviceContext* d3d_device_ctx;
IDXGISwapChain* d3d_swap_chain;
ID3D11RenderTargetView* d3d_render_target;
D3DPRESENT_PARAMETERS d3d_present_params;

#pragma comment(lib, "d3d11.lib")

namespace overlay
{
    bool InitImgui()
    {
        DXGI_SWAP_CHAIN_DESC swap_chain_description;
        ZeroMemory(&swap_chain_description, sizeof(swap_chain_description));
        swap_chain_description.BufferCount = 2;
        swap_chain_description.BufferDesc.Width = 0;
        swap_chain_description.BufferDesc.Height = 0;
        swap_chain_description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swap_chain_description.BufferDesc.RefreshRate.Numerator = 60;
        swap_chain_description.BufferDesc.RefreshRate.Denominator = 1;
        swap_chain_description.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        swap_chain_description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_description.OutputWindow = globals.window_handle;
        swap_chain_description.SampleDesc.Count = 1;
        swap_chain_description.SampleDesc.Quality = 0;
        swap_chain_description.Windowed = 1;
        swap_chain_description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        D3D_FEATURE_LEVEL d3d_feature_lvl;

        const D3D_FEATURE_LEVEL d3d_feature_array[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };

        D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, d3d_feature_array, 2, D3D11_SDK_VERSION, &swap_chain_description, &d3d_swap_chain, &d3d_device, &d3d_feature_lvl, &d3d_device_ctx);

        ID3D11Texture2D* pBackBuffer;
        D3DX11_IMAGE_LOAD_INFO info;
        ID3DX11ThreadPump* pump{ nullptr };

        d3d_swap_chain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

        d3d_device->CreateRenderTargetView(pBackBuffer, NULL, &d3d_render_target);

        pBackBuffer->Release();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
        ImFontConfig icons_config;

        ImFontConfig CustomFont;
        CustomFont.FontDataOwnedByAtlas = false;

        icons_config.MergeMode = true;
        icons_config.PixelSnapH = true;
        icons_config.OversampleH = 2.5;
        icons_config.OversampleV = 2.5;

        ImGui_ImplWin32_Init(globals.window_handle);
        ImGui_ImplDX11_Init(d3d_device, d3d_device_ctx);


        ImFontConfig font_config;
        font_config.OversampleH = 1;
        font_config.OversampleV = 1;
        font_config.PixelSnapH = 1;


        static const ImWchar ranges[] =
        {
            0x0020, 0x00FF,
            0x0400, 0x044F,
            0,
        };

        menu.MenuFont = io.Fonts->AddFontFromFileTTF(("c:\\fortnite.otf"), 18.f);

        io.Fonts->AddFontFromMemoryTTF(&seguoe, sizeof seguoe, 18, NULL, io.Fonts->GetGlyphRangesCyrillic());

        default_segu = io.Fonts->AddFontFromMemoryTTF(&seguoe, sizeof seguoe, 18, NULL, io.Fonts->GetGlyphRangesCyrillic());

        segu = io.Fonts->AddFontFromMemoryTTF(&seguoe, sizeof seguoe, 40, NULL, io.Fonts->GetGlyphRangesCyrillic());

        bold_segu = io.Fonts->AddFontFromMemoryTTF(&bold_segue, sizeof bold_segue, 40, NULL, io.Fonts->GetGlyphRangesCyrillic());

        ico = io.Fonts->AddFontFromMemoryTTF(&icon_fag, sizeof icon_fag, 24, NULL, io.Fonts->GetGlyphRangesCyrillic());

        ico_combo = io.Fonts->AddFontFromMemoryTTF(&icon_fag, sizeof icon_fag, 19, NULL, io.Fonts->GetGlyphRangesCyrillic());

        ico_button = io.Fonts->AddFontFromMemoryTTF(&icon_fag, sizeof icon_fag, 25, NULL, io.Fonts->GetGlyphRangesCyrillic());

        ico_grande = io.Fonts->AddFontFromMemoryTTF(&icon_fag, sizeof icon_fag, 40, NULL, io.Fonts->GetGlyphRangesCyrillic());

        d3d_device->Release();

        return true;
    }

    bool HijackWindow()
    {
        globals.window_handle = FindWindowA(("Chrome_WidgetWin_1"), ("CrosshairX")); // CrosshairX
        //globals.window_handle = FindWindowA(("GameOverlay"), ("GameOverlay)); // Steelseries
      //  globals.window_handle = FindWindowA(("MedalOverlayClass"), ("MedalOverlay")); // Medal

        if (!globals.window_handle)
        {
            MessageBoxA(0, ("(Overlay Failed) Please Make Sure You Have CrosshairX Open"), (""), MB_ICONINFORMATION);
            return false;
        }

        SetWindowPos(globals.window_handle, HWND_TOPMOST, 0, 0, globals.ScreenWidth, globals.ScreenHeight, SWP_SHOWWINDOW);
        SetLayeredWindowAttributes(globals.window_handle, RGB(0, 0, 0), 255, LWA_ALPHA);
        SetWindowLongA(globals.window_handle, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT);

        MARGINS margin = { -1 };
        DwmExtendFrameIntoClientArea(globals.window_handle, &margin);

        ShowWindow(globals.window_handle, SW_SHOW);
        UpdateWindow(globals.window_handle);

        ShowWindow(globals.window_handle, SW_HIDE);

        return true;
    }

    void menu_loop()
    {
        if (GetAsyncKeyState(menu.menu_key) & 1)
            menu.ShowMenu = !menu.ShowMenu;

        if (GetAsyncKeyState(VK_END) & 1)
        {
            console.kill_cheat();
        }

        if (menu.ShowMenu)
        {
            menu_class();
        }
    }

    void draw()
    {
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        actorloop();
        //leveldrawing();
        ModuleArrayList();
        menu_loop();

        if (menu.ShowMenu)
        {
            if (menu.menu_cursor)
            {
                ImGuiIO& io = ImGui::GetIO();
                ImVec2 Cursor_Pos = ImGui::GetMousePos();
                float radius = 5.0f;
                ImDrawList* draw_list = ImGui::GetForegroundDrawList();
                ImU32 color = IM_COL32(255, 0, 0, 255);

                draw_list->AddCircleFilled(Cursor_Pos, radius, ImColor(255,0,0), 32);
            }
        }

        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        d3d_device_ctx->OMSetRenderTargets(1, &d3d_render_target, nullptr);
        d3d_device_ctx->ClearRenderTargetView(d3d_render_target, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        d3d_swap_chain->Present(0, 0);
    }

    bool render()
    {
        MSG msg = { NULL };
        ZeroMemory(&msg, sizeof(MSG));

        while (msg.message != WM_QUIT)
        {

            UpdateWindow(globals.window_handle);
            ShowWindow(globals.window_handle, SW_SHOW);

            if (PeekMessageA(&msg, globals.window_handle, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            ImGuiIO& io = ImGui::GetIO();
            io.DeltaTime = 1.0f / 60.0f;


            POINT p_cursor;
            GetCursorPos(&p_cursor);
            io.MousePos.x = p_cursor.x;
            io.MousePos.y = p_cursor.y;

            if (GetAsyncKeyState(VK_LBUTTON)) {
                io.MouseDown[0] = true;
                io.MouseClicked[0] = true;
                io.MouseClickedPos[0].x = io.MousePos.x;
                io.MouseClickedPos[0].x = io.MousePos.y;
            }
            else
                io.MouseDown[0] = false;

            draw();
        }

        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        DestroyWindow(globals.window_handle);

        return true;
    }

    void start()
    {
        HijackWindow();
        InitImgui();

        CreateThread(0, 0, LPTHREAD_START_ROUTINE(render()), 0, 0, 0);
        std::thread([&]() { game_helper.get_camera(); }).detach();
    }
}