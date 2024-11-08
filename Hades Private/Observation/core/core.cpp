// Window Includes
#include <Windows.h>
#include <ntstatus.h>
#include <tchar.h>
#include <Shlobj.h>
#include <Psapi.h>
#include <iostream>
#include <thread>
#include <sstream>
#include <vector>
#include <utility>

// Custom Includes
#include "../overlay/render.h"
#include "../game/utils/settings.h"
#include "../kernal/driver.hpp"
#pragma comment(lib, "ntdll.lib")

#include "../framework/ImGui/imgui.h"
#include "../framework/ImGui/imgui_impl_dx11.h"
#include "../framework/ImGui/imgui_impl_win32.h"

#include "../console/console.h"
#include "../core/misc.h"
#include "core.h"

bool nigga = true;

void D3DX11CreateShaderResourceViewFromMemory();

void set_console_title()
{
    while (nigga)
    {
        auto title = core_misc.generate_string(30);
        SetConsoleTitleA(title.c_str());
    }
}

void core_t::start()
{
    std::thread title(set_console_title);
    title.detach();
    D3DX11CreateShaderResourceViewFromMemory();
    if (!core_misc.admincheck())
    {
        console.error("Please Run Loader As Admin!");
        console.beep(325, 500);
        console.sleep(5000);
        console.exit(0);
    }

    console.start();

    if (!handler::find_driver())
    {
        console.write("Driver Not Loaded, Try Agian!");
        MessageBox(NULL, L"OK?", L"HADES", MB_OK | MB_HELP);
        console.sleep(2000);
        console.exit(0);
    }

    console.write("Waiting For Fortnite.");

    HWND FortniteWindow = NULL;
    while (FortniteWindow == NULL)
    {
        FortniteWindow = FindWindowA(0, "Fortnite  ");
    }

    console.beep(325, 500);
    console.write("Game Found");

    MessageBox(NULL, L"Press Okay Once In Lobby", L"HADES", MB_OK | MB_HELP);

    handler::process_id = handler::find_process(L"FortniteClient-Win64-Shipping.exe");
    virtualaddy = handler::find_image();
    handler::fetch_cr3();

    for (auto i = 0; i < FLT_MAX; i++)
    {
        //globals.va_text = virtualaddy + i * 0x1000;
        auto uworld = read<uintptr_t>(virtualaddy + offsets::UWorld);   
        auto level = read<uintptr_t>(uworld + offsets::PersistentLevel); 
        auto GameInstance = read<uintptr_t>(uworld + offsets::OwningGameInstance);
        auto LocalPlayer = read<uintptr_t>(read<uintptr_t>(GameInstance + offsets::LocalPlayers)); 
        auto PlayerController = read<uintptr_t>(LocalPlayer + offsets::PlayerController); 
        auto GameState = read<uintptr_t>(uworld + offsets::GameState);  
        auto Mesh = read<uintptr_t>(CachePointers.AcknownledgedPawn + offsets::Mesh);

        std::cout << "Uworld: " << uworld;
        std::cout << "\nMesh: " << uworld;
        std::cout << "\nPlayer controller: " << PlayerController;
        std::cout << "\nGame instance: " << GameInstance;
        std::cout << "\nGame state: " << GameState; 
        std::cout << "\n Local player: " << LocalPlayer;

       // if (uworld && level && read<uintptr_t>(level + offsets::OwningWorld) == uworld)
        //{
            nigga = false;
            
            std::thread([&]() { { CacheLevels(); } }).detach();
            overlay::start();

        //}
    }

    std::thread([&]() { { CacheLevels(); } }).detach();
    overlay::start();
}