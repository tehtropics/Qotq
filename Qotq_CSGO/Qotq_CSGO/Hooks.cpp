#include "Hooks.h"

CreateMove oCreateMove;
DoPostScreenEffects oDoPostScreenEffects;
PaintTraverse oPaintTraverse;
void __fastcall  Hooks::PaintTraverseHook(void *thisptr, void * _EDX,vgui::VPANEL panel, bool forceRepaint, bool allowForce) {
	static uint32_t FocusOverlayPanel;
	if (!FocusOverlayPanel)
	{
		const char* szName = g_pVGuiPanel->GetName(panel);

		if (lstrcmpA(szName, "FocusOverlayPanel") == 0)
		{
			FocusOverlayPanel = panel;

			g_pEngine->ExecuteClientCmd("clear");
			g_pICvar->ConsoleColorPrintf(Color(255, 0, 176, 255), "Qotq Cheetos V2 \n");
			g_pICvar->ConsoleColorPrintf(Color(255, 0, 176, 255), "%s %s \n", __TIME__, __DATE__);
			g_pEngine->ExecuteClientCmd("toggleconsole");
		}
	}

	if (FocusOverlayPanel == panel)
	{
		//do visuals here
	}

	return oPaintTraverse(thisptr, panel, forceRepaint, allowForce);
}

bool __stdcall Hooks::CreateMoveHook(float flInputSampleTime, CUserCmd* cmd) {
	return oCreateMove(flInputSampleTime, cmd);
}

int  __fastcall Hooks::DoPostScreenEffectsHook(void *thisptr, void * _EDX,int a1) {
	if(g_pEngine->GetLocalPlayer()) g_pGlow->Start();
	return oDoPostScreenEffects(thisptr,a1);
}