#include "SDK.h"

HWND m_hwndWindow = NULL;
//reso externals
CUtils* g_pUtils;
CGlow* g_pGlow;
CGlowObjectManager* g_pGlowObjectManager;


IBaseClientDLL* g_pCHLClient = nullptr;
IClientMode* g_pClientMode = nullptr;
IPanel* g_pVGuiPanel = nullptr;
ISurface* g_pVGuiSurface = nullptr;
IVEngineClient* g_pEngine = nullptr;
ICvar* g_pICvar = nullptr;

template< typename T >
T* GetInterface(char* mod, char* interf, bool exact = false)
{
	typedef T* (*CreateInterfaceFn)(const char* szName, int iReturn);
	CreateInterfaceFn CreateInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(mod), ("CreateInterface"));

	std::string sInterface, sInterfaceVersion = "0";

	if (!exact)
	{
		for (auto i = 0; i <= 99; i++)
		{
			sInterface = interf;
			sInterface += sInterfaceVersion;
			sInterface += std::to_string(i);

			T* funcPtr = CreateInterface(sInterface.c_str(), NULL);

			if (funcPtr != NULL)
			{
				g_pUtils->Print("%s -> 0x%x", sInterface.c_str(), funcPtr);
				return funcPtr;
			}

			if (i == 99 && sInterfaceVersion == "0")
			{
				sInterfaceVersion = "00";
				i = 0;
			}
			else if (i == 99 && sInterfaceVersion == "00")
			{
				g_pUtils->Print("%s -> Cant get pointer!", interf);
				return nullptr;
			}
		}
	}
	else
	{
		T* ptr = CreateInterface(interf, 0);

		if (ptr)
		{
			g_pUtils->Print("%s -> 0x%x", interf, ptr);
			return ptr;
		}
		else
		{
			g_pUtils->Print("%s ->  Cant get pointer!", interf);
			return nullptr;
		}
	}

	return nullptr;
}

void InstallQotq(void)
{
	while (!(m_hwndWindow = FindWindowA("Valve001", NULL)))
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

	while (!GetModuleHandleA("serverbrowser.dll"))
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

	g_pUtils->Print("-------------------------------------------------------------------------------");
	g_pUtils->Print("-------------------------------QotqCheetos-------------------------------------");
	g_pUtils->Print("-------------------------------------------------------------------------------");
	g_pUtils->Print("Got serverbrowser.dll(game is read)");
	g_pUtils->Print(" "); //don't ask dude
	g_pUtils->Print("-------------------------------------------------------------------------------");
	g_pUtils->Print("Getting Interfaces:");
	g_pCHLClient = GetInterface<IBaseClientDLL>("client.dll", "VClient");
	g_pClientMode = **reinterpret_cast<IClientMode***>((*(uintptr_t**)g_pCHLClient)[10] + 0x5);
	g_pUtils->Print("ClientMode -> 0x%x", g_pClientMode);
	g_pVGuiPanel = GetInterface<IPanel>("vgui2.dll", "VGUI_Panel");
	g_pVGuiSurface = GetInterface<ISurface>("vguimatsurface.dll", "VGUI_Surface");
	g_pEngine = GetInterface<IVEngineClient>("engine.dll", "VEngineClient");
	g_pICvar = GetInterface<ICvar>("vstdlib.dll", "VEngineCvar");
	g_pGlowObjectManager = *(CGlowObjectManager**)(g_pUtils->FindPatternIDA("client.dll", "0F 11 05 ? ? ? ? 83 C8 01") + 3);
	g_pUtils->Print("GlowObjectManager -> 0x%x", g_pGlowObjectManager);
	g_pUtils->Print("-------------------------------------------------------------------------------");
	g_pUtils->Print("Hooking:");
	CVMTHookManager* VGuiHook = new CVMTHookManager((PDWORD*)g_pVGuiPanel);
	oPaintTraverse = (PaintTraverse)(VGuiHook->HookMethod((DWORD)Hooks::PaintTraverseHook, 41));
	g_pUtils->Print("PaintTraverse(41) -> 0x%x", oPaintTraverse);
	CVMTHookManager* ClientModeHook = new CVMTHookManager((PDWORD*)g_pClientMode);
	oCreateMove = (CreateMove)(ClientModeHook->HookMethod((DWORD)Hooks::CreateMoveHook, 24));
	g_pUtils->Print("CreateMove -> 0x%x", oCreateMove);
	oDoPostScreenEffects = (DoPostScreenEffects)(ClientModeHook->HookMethod((DWORD)Hooks::DoPostScreenEffectsHook, 44));
	g_pUtils->Print("DoPostScreenEffects -> 0x%x", oDoPostScreenEffects);
}









