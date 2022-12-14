/**
 * @file
 *
 * @author OmniBlade
 *
 * @brief Proxy dll to maquerade as bandtest.dll and inject our hooking reimplementation at the same time.
 *
 * @copyright JustBusiness is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            3 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#include "hooker.h"
#include "sha1.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <io.h>
#include <windows.h>

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))
#endif // !ARRAY_SIZE

/**
 * Pointer for the hooking function from the payload.
 */
void (*Setup_Hooks)();

/**
 * Get the path for the exe we were loaded by.
 */
const wchar_t *Get_Path()
{
    static wchar_t buffer[MAX_PATH];
    DWORD size = GetModuleFileNameW(nullptr, buffer, ARRAY_SIZE(buffer));

    if (size == 0 || size >= ARRAY_SIZE(buffer)) {
        MessageBoxA(nullptr, "Failed to get path to target executable for code injection", "Proxy", MB_ICONERROR);
        ExitProcess(0);
    }

    return buffer;
}

/**
 * Get the hash for the exe we were loaded by.
 */
const char *Get_Hash()
{
    SHAEngine sha;
    char buffer[1024];

    std::ifstream in(Get_Path(), std::ios_base::in | std::ios_base::binary);

    // Get the hash of the binary.
    do {
        in.read(buffer, sizeof(buffer));
        sha.Hash(buffer, int(in.gcount()));
    } while (in.gcount() == sizeof(buffer));

    return sha.Print_Result();
}

/**
 * Get the payload dll name we expect for the binary based on its hash.
 */
const char *Get_Payload_Name()
{
    struct ExePayloads
    {
        const char *exe_hash;
        const char *payload_name;
    };

    static const ExePayloads Payloads[] = {
        {"18648049a0a8d2dc70d513a7d8f1ba7cbbf23c4b", "justbusiness.dll"},
    };

    const char *target_hash = Get_Hash();

    for (unsigned i = 0; i < ARRAY_SIZE(Payloads); ++i) {
        if (strcmp(Payloads[i].exe_hash, target_hash) == 0) {
            return Payloads[i].payload_name;
        }
    }

    return nullptr;
}

/**
 * Loads the dll payload and retrieves the Setup_Hooks function from it.
 */
bool Load_Setup_Hooks()
{
    const char *payload = Get_Payload_Name();

    if (payload == nullptr) {
#ifndef NDEBUG
        MessageBoxA(nullptr, "Cannot find the patch dll for this binary, thyme will not be active.", "Proxy", MB_ICONERROR);
#endif
        return false;
    }

    HMODULE dll = LoadLibraryA(payload);

    if (dll == nullptr) {
#ifndef NDEBUG
        MessageBoxA(nullptr, "Cannot load patch library", "Proxy", MB_ICONERROR);
#endif
        return false;
    }

    Setup_Hooks = (void (*)())GetProcAddress(dll, "Setup_Hooks");

    if (Setup_Hooks == nullptr) {
#ifndef NDEBUG
        MessageBoxA(nullptr, "Cannot load Setup_Hooks() function from the patch library", "Proxy", MB_ICONERROR);
#endif
        return false;
    }

    return true;
}

/**
 * Our proxy dll entry point, we load the dll we are proxying as well as set up our injection payload on process attach.
 */
BOOL WINAPI DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            // Now we work out which binary we have and load the payload dll if we have it.
            if (Load_Setup_Hooks()) {
                if (StartHooks()) {
                    Setup_Hooks();
                    StopHooks();
                }
            }
            break;

        case DLL_PROCESS_DETACH:
            // This DLL is supposed to be loaded via imports in an exe and stay loaded for the life of the process.
            // As a result we don't clean up after ourselves regarding calling FreeLibray which isn't best practice.
            // However the documentation for LoadLibrary states that the libraries loaded with it will unload on
            // process termination which is the behaviour we want anyhow.
            break;

        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        default:
            break;
    }

    return TRUE;
}
