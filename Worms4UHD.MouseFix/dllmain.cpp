#include "pch.h"
#include "MemoryMgr.h"
#include <Windows.h>

using namespace Memory::VP;

void WINAPI SetMousePosDirectly(int ptr, int X, int Y)
{
    bool& bCursorVisible = *(bool*)0x97AC96;
    if (bCursorVisible)
        return;

    ((void(_stdcall*)(int, int, int))0x701D92)(ptr, X, Y);
}


void Init()
{
    Patch(0x89AE5C, &SetMousePosDirectly);
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Init();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
