#include <Windows.h>
#include <thread>

#include "core/Interfaces.h"
#include "core/Memory.h"

DWORD WINAPI CheatMain(LPVOID hinstDLL) // Cheat thread
{
	// Waiting for game fully initialized
	while (!GetModuleHandle("client.dll"))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	while (!GetModuleHandle("engine.dll"))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	while (!GetModuleHandle("serverbrowser.dll"))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	try
	{
		interfaces = std::make_unique<const Interfaces>();
		memory = std::make_unique<const Memory>();
		netvar = std::make_unique<Netvar>();
	}
	catch (const std::exception& e)
	{
		MessageBeep(MB_ICONSTOP);
		MessageBoxA(NULL, e.what(), "CheatBase", MB_OK | MB_ICONERROR);
		FreeLibraryAndExitThread(static_cast<HMODULE>(hinstDLL), EXIT_FAILURE);
		return FALSE;
	}

	// Waiting for user END key press
	while (!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(200L));

	FreeLibraryAndExitThread(static_cast<HMODULE>(hinstDLL), EXIT_SUCCESS); // Uninstall cheat
	return FALSE;
}

// How to create a dll file -> https://learn.microsoft.com/en-US/windows/win32/dlls/dllmain
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH) // Called when dll attach
	{
		DisableThreadLibraryCalls(hinstDLL); // Disable the call of thread attach or thread detach on this dll
		const HANDLE thread = CreateThread(nullptr, NULL, CheatMain, hinstDLL, NULL, nullptr); // Create cheat thread
		if (thread)
			CloseHandle(thread); // Avoid memory leak
	}

	return TRUE;
}