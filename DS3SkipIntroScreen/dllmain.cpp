#include <Windows.h>
#include <MinHook.h>

#pragma comment(lib, "libMinHook.x64.lib")

struct Patch {
    DWORD64 relAddr;
    DWORD size;
    char patch[50]; 
    char orig[50];
};

typedef DWORD64(__stdcall *DIRECTINPUT8CREATE)(HINSTANCE, DWORD, REFIID, LPVOID *, LPUNKNOWN);
DIRECTINPUT8CREATE fpDirectInput8Create;
extern "C" __declspec(dllexport)  HRESULT __stdcall DirectInput8Create(
    HINSTANCE hinst,
    DWORD dwVersion,
    REFIID riidltf,
    LPVOID * ppvOut,
    LPUNKNOWN punkOuter
)
{
    return fpDirectInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter);
}
typedef DWORD64(__cdecl *STEAMINIT)();
STEAMINIT fpSteamInit = NULL;
DWORD64 __cdecl onSteamInit() {

    Patch patches[] = {
        //v1.8
        Patch{ 0x0BD6ACF, 20, { static_cast<char>(0x48), static_cast<char>(0x31), static_cast<char>(0xC0), static_cast<char>(0x48), static_cast<char>(0x89), static_cast<char>(0x02), static_cast<char>(0x49), static_cast<char>(0x89), static_cast<char>(0x04), static_cast<char>(0x24), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90) },{ static_cast<char>(0xE8), static_cast<char>(0xAC), static_cast<char>(0xC6), static_cast<char>(0xFB), static_cast<char>(0xFF), static_cast<char>(0x90), static_cast<char>(0x4D), static_cast<char>(0x8B), static_cast<char>(0xC7), static_cast<char>(0x49), static_cast<char>(0x8B), static_cast<char>(0xD4), static_cast<char>(0x48), static_cast<char>(0x8B), static_cast<char>(0xC8), static_cast<char>(0xE8), static_cast<char>(0x9D), static_cast<char>(0xC6), static_cast<char>(0xFB), static_cast<char>(0xFF) } },
        //v1.4
        Patch{ 0x0BBB0CF, 20, { static_cast<char>(0x48), static_cast<char>(0x31), static_cast<char>(0xC0), static_cast<char>(0x48), static_cast<char>(0x89), static_cast<char>(0x02), static_cast<char>(0x49), static_cast<char>(0x89), static_cast<char>(0x04), static_cast<char>(0x24), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90) },{ static_cast<char>(0xE8), static_cast<char>(0x8C), static_cast<char>(0x07), static_cast<char>(0xFC), static_cast<char>(0xFF), static_cast<char>(0x90), static_cast<char>(0x4D), static_cast<char>(0x8B), static_cast<char>(0xC7), static_cast<char>(0x49), static_cast<char>(0x8B), static_cast<char>(0xD4), static_cast<char>(0x48), static_cast<char>(0x8B), static_cast<char>(0xC8), static_cast<char>(0xE8), static_cast<char>(0x7D), static_cast<char>(0x07), static_cast<char>(0xFC), static_cast<char>(0xFF) } },
        //v1.11
        Patch{ 0x0BE6F8F, 20, { static_cast<char>(0x48), static_cast<char>(0x31), static_cast<char>(0xC0), static_cast<char>(0x48), static_cast<char>(0x89), static_cast<char>(0x02), static_cast<char>(0x49), static_cast<char>(0x89), static_cast<char>(0x04), static_cast<char>(0x24), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90) },{ static_cast<char>(0xE8), static_cast<char>(0x9C), static_cast<char>(0xBD), static_cast<char>(0xFB), static_cast<char>(0xFF), static_cast<char>(0x90), static_cast<char>(0x4D), static_cast<char>(0x8B), static_cast<char>(0xC7), static_cast<char>(0x49), static_cast<char>(0x8B), static_cast<char>(0xD4), static_cast<char>(0x48), static_cast<char>(0x8B), static_cast<char>(0xC8), static_cast<char>(0xE8), static_cast<char>(0x8D), static_cast<char>(0xBD), static_cast<char>(0xFB), static_cast<char>(0xFF) } },
        //v1.10
        Patch{ 0x0BD70FF, 20, { static_cast<char>(0x48), static_cast<char>(0x31), static_cast<char>(0xC0), static_cast<char>(0x48), static_cast<char>(0x89), static_cast<char>(0x02), static_cast<char>(0x49), static_cast<char>(0x89), static_cast<char>(0x04), static_cast<char>(0x24), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90) },{ static_cast<char>(0xE8), static_cast<char>(0xAC), static_cast<char>(0xC6), static_cast<char>(0xFB), static_cast<char>(0xFF), static_cast<char>(0x90), static_cast<char>(0x4D), static_cast<char>(0x8B), static_cast<char>(0xC7), static_cast<char>(0x49), static_cast<char>(0x8B), static_cast<char>(0xD4), static_cast<char>(0x48), static_cast<char>(0x8B), static_cast<char>(0xC8), static_cast<char>(0xE8), static_cast<char>(0x9D), static_cast<char>(0xC6), static_cast<char>(0xFB), static_cast<char>(0xFF) } },
        //v1.9
        Patch{ 0x0BD708F, 20, { static_cast<char>(0x48), static_cast<char>(0x31), static_cast<char>(0xC0), static_cast<char>(0x48), static_cast<char>(0x89), static_cast<char>(0x02), static_cast<char>(0x49), static_cast<char>(0x89), static_cast<char>(0x04), static_cast<char>(0x24), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90), static_cast<char>(0x90) },{ static_cast<char>(0xE8), static_cast<char>(0xAC), static_cast<char>(0xC6), static_cast<char>(0xFB), static_cast<char>(0xFF), static_cast<char>(0x90), static_cast<char>(0x4D), static_cast<char>(0x8B), static_cast<char>(0xC7), static_cast<char>(0x49), static_cast<char>(0x8B), static_cast<char>(0xD4), static_cast<char>(0x48), static_cast<char>(0x8B), static_cast<char>(0xC8), static_cast<char>(0xE8), static_cast<char>(0x9D), static_cast<char>(0xC6), static_cast<char>(0xFB), static_cast<char>(0xFF) } },
    
    };


    auto baseAddr = GetModuleHandle(NULL);
    for (auto i = 0; i < (sizeof(patches) / sizeof(patches[0])); i++) {
        auto patch = patches[i];
        auto addr = (void*)((DWORD64)baseAddr + patch.relAddr);
        auto size = patch.size;

        if (memcmp(addr, patch.orig, size) == 0) {
            DWORD old;
            VirtualProtect(addr, size, PAGE_EXECUTE_READWRITE, &old);
            memcpy(addr, patch.patch, size); 
            VirtualProtect(addr, size, old, &old);
            break;
        }
    }


    return fpSteamInit();
}



void AttachHook() {
    auto steamApiHwnd = GetModuleHandle(L"steam_api64.dll");
    auto initAddr = GetProcAddress(steamApiHwnd, "SteamAPI_Init");

    char syspath[320];
    GetSystemDirectoryA(syspath, 320);
    strcat_s(syspath, "\\dinput8.dll");
    auto hMod = LoadLibraryA(syspath);
    fpDirectInput8Create = (DIRECTINPUT8CREATE)GetProcAddress(hMod, "DirectInput8Create");


    MH_CreateHook(initAddr, &onSteamInit, reinterpret_cast<LPVOID*>(&fpSteamInit));
    MH_EnableHook(initAddr);
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        MH_Initialize();
        AttachHook();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

