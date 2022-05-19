#include "pch.h"
#include "MemoryMgr.h"
#include <Windows.h>

using namespace Memory::VP;

typedef int(__cdecl* tsub_701348)(int a1);
tsub_701348 sub_701348 = (tsub_701348)0x701348;
typedef int(__cdecl* tsub_6405AC)();
tsub_6405AC sub_6405AC = (tsub_6405AC)0x6405AC;

DWORD isInGame = 0;

int WINAPI SetMousePosDirectly(int ptr, int X, int Y)
{
    if (*(BYTE*)isInGame)
    {
        return 0;
    }

    struct tagPOINT Point; // [sp+Ch] [bp-8h]@1
    GetCursorPos(&Point);

    int v3; // eax@3
    int v4; // esi@3
    HWND v5; // eax@4
    HWND v6; // eax@4
    struct tagPOINT v8; // [sp+4h] [bp-10h]@4

    if (Point.x != X || Point.y != Y)
    {
        v3 = (*(int(__stdcall**)(int, signed int))(*(DWORD*)ptr + 60))(ptr, 1);
        v4 = sub_701348(v3);
        if (v4)
        {
            v8.y = Y;
            v8.x = X;
            v5 = (HWND)sub_6405AC();
            ScreenToClient(v5, &v8);
            v6 = (HWND)sub_6405AC();
            ScreenToClient(v6, &Point);
            *(DWORD*)(v4 + 176) += v8.x - Point.x;
            *(DWORD*)(v4 + 180) += v8.y - Point.y;
        }
        #ifdef DEBUG
            printf("set cursor (%d, %d) to pos %d %d\n", Point.x, Point.y, X, Y);
        #endif 
        SetCursorPos(X, Y);
    }

    return 0;
}

HMODULE myhModule;

void Init()
{
    #ifdef DEBUG
        AllocConsole();
        freopen("conin$", "r", stdin);
        freopen("conout$", "w", stdout);
        freopen("conout$", "w", stderr);
        printf("Debugging Window enabled\n");
    #endif 

    DWORD Base = (DWORD)GetModuleHandleA("WormsMayhem.exe");
    isInGame = Base + 0x57AC96;

    #ifdef DEBUG
        printf("InGame %x\n", inGame);
    #endif 


    InjectHook(0x701D92, SetMousePosDirectly, PATCH_JUMP);
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        myhModule = hModule;
        Init();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
