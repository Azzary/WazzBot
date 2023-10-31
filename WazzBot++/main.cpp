#include <thread>
#include <cstdio>
#include <Windows.h>
#include <jni.h>
#include "JNI.h"
#include "Hooks.h"
#include "LocalPlayerCharacter.h"
#include <thread>
#include "MainWindow.h"


void MainThread(HMODULE module)
{
    static std::thread ui_thread;

    p_jni = std::make_unique<JNI>();
    p_hooks = std::make_unique<Hooks>();
    MSG msg = { 0 };
    MainWindow mainWindow(module);
    mainWindow.Show(SW_SHOW);

    while (!GetAsyncKeyState(VK_END))
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (GetAsyncKeyState(VK_XBUTTON1)) {
            LocalPlayerCharacter* localPlayer = p_jni->p_wakfu_game_entity->GetLocalPlayerCharacter();
            if (localPlayer != nullptr) {
                localPlayer->move(103, -20, 0);
                Sleep(1000);
                localPlayer->UpdatePlayerPosition();
            }
            delete (localPlayer);
        }
    }

    FreeLibrary(module);
}


bool __stdcall DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved) 
{
    static FILE* p_file{ nullptr };
    static std::thread main_thread;

    if (reason == DLL_PROCESS_ATTACH)
    {
        AllocConsole();
        freopen_s(&p_file, "CONOUT$", "w", stdout);

        main_thread = std::thread([instance] { MainThread(instance); });
        if (main_thread.joinable())
            main_thread.detach();
    }
    else if (reason == DLL_PROCESS_DETACH)
    {
        fclose(p_file);
        FreeConsole();
    }

    return true;
}
