#include <Windows.h>

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

void ApplyPatches() {

    DWORD patchCount = 2;
    Patch patches[] = {
        //Latest
        Patch{ 0x8320B0, 7, { static_cast<char>(0xE9) , static_cast<char>(0x27) , static_cast<char>(0x01) , static_cast<char>(0x00) , static_cast<char>(0x00) , static_cast<char>(0x90) , static_cast<char>(0x90) },{ static_cast<char>(0xFF) , static_cast<char>(0x24) , static_cast<char>(0x85) , static_cast<char>(0x24) , static_cast<char>(0x22) , static_cast<char>(0xC3) , static_cast<char>(0x00) } },
        Patch{ 0x8322B3, 2, { static_cast<char>(0x90) , static_cast<char>(0x90) }, { static_cast<char>(0x74) , static_cast<char>(0x0D) } },
        //Debug build
	Patch{ 0x831B30, 7, { static_cast<char>(0xE9) , static_cast<char>(0x27) , static_cast<char>(0x01) , static_cast<char>(0x00) , static_cast<char>(0x00) , static_cast<char>(0x90) , static_cast<char>(0x90) },{ static_cast<char>(0xFF) , static_cast<char>(0x24) , static_cast<char>(0x85) , static_cast<char>(0xA4) , static_cast<char>(0x1C) , static_cast<char>(0xC3) , static_cast<char>(0x00) } },
	Patch{ 0x831D33, 2, { static_cast<char>(0x90) , static_cast<char>(0x90) },{ static_cast<char>(0x74) , static_cast<char>(0x0D) } }
    };


    auto baseAddr = GetModuleHandle(NULL);
    for (auto i = 0; i < patchCount; i++) {
        auto patch = patches[i];
        auto addr = (void*)((DWORD64)baseAddr + patch.relAddr);
        auto size = patch.size;

        if (memcmp(addr, patch.orig, size) == 0) {
            DWORD old;
            VirtualProtect(addr, size, PAGE_EXECUTE_READWRITE, &old);
            memcpy(addr, patch.patch, size);
            VirtualProtect(addr, size, old, &old);
        }
    }

}



void AttachHook() {
    char syspath[320];
    GetSystemDirectoryA(syspath, 320);
    strcat_s(syspath, "\\dinput8.dll");
    auto hMod = LoadLibraryA(syspath);
    fpDirectInput8Create = (DIRECTINPUT8CREATE)GetProcAddress(hMod, "DirectInput8Create");
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        AttachHook();
        ApplyPatches();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

