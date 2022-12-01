/**
 * @file
 *
 * @author OmniBlade
 *
 * @brief Provides the exe patching/hooking entry point for the proxy loader.
 *
 * @copyright JustBusiness is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            3 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#ifndef DLL_BUILD
#error "This file should only be compiled for dll injection."
#endif

#include <hooker.h>
#include <windows.h>

void Setup_Hooks()
{
    // Put hooks here, e.g. Hook_Function(0xDEADBEEF, Some_Function)
}

// Use DLLMain to Set up our hooks when the DLL loads. The launcher should stall
// the main thread at the entry point so hooked code called after that should
// be our code.
BOOL WINAPI DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            break;

        case DLL_PROCESS_DETACH:
            // Currently does not unhook from module. Must shutdown.
            break;

        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        default:
            break;
    }

    return TRUE;
}
