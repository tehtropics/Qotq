#include "Hooks.h"
//reso hooks
CreateMove oCreateMove;
DoPostScreenEffects oDoPostScreenEffects;
PaintTraverse oPaintTraverse;
OverrideView oOverrideView;
SceneEnd oSceneEnd;
FrameStageNotify oFrameStageNotify;
WriteUsercmdDeltaToBuffer oWriteUsercmdDeltaToBuffer;
PlaySoundT oPlaySound;
EndScene oEndScene;
Reset oReset;
DrawModelExecute oDrawModelExecute;
extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);



void __fastcall  Hooks::PaintTraverseHook(void *thisptr, void * _EDX,vgui::VPANEL panel, bool forceRepaint, bool allowForce) {
	static uint32_t FocusOverlayPanel;
	if (!FocusOverlayPanel)
	{
		const char* szName = g_pVGuiPanel->GetName(panel);

		if (lstrcmpA(szName, "MatSystemTopPanel") == 0)
		{
			FocusOverlayPanel = panel;
			g_pSDK->InitFonts();
			g_pEngine->ExecuteClientCmd("clear");
			g_pICvar->ConsoleColorPrintf(Color(255, 0, 176, 255), "Qotq Cheetos V2 \n");
			g_pICvar->ConsoleColorPrintf(Color(255, 0, 176, 255), "%s %s \n", __TIME__, __DATE__);
			g_pEngine->ExecuteClientCmd("toggleconsole");
		}
	}

	if (FocusOverlayPanel == panel)
	{
		auto local = g_pEntityList->GetClientEntity(g_pEngine->GetLocalPlayer());
		time_t _tm = time(NULL);
		struct tm * curtime = localtime(&_tm);
		std::string timee = asctime(curtime);
		Draw->String(F_Arial, false, 5, 3, Color(255, 255, 255, 255), "Qotq Cheetos");
		Draw->String(F_Arial, false, 5, 18, Color(255, 0, 0, 255), timee.c_str());
		if (local) {
			g_pESP->Start();
		}
		//do visuals here
	}

	return oPaintTraverse(thisptr, panel, forceRepaint, allowForce);
}

bool __stdcall Hooks::CreateMoveHook(float flInputSampleTime, CUserCmd* cmd) {
	C_BaseEntity* localplayer = g_pEntityList->GetClientEntity(g_pEngine->GetLocalPlayer());
	if (!cmd->command_number || !g_pEngine->IsConnected() && !g_pEngine->IsInGame() || !localplayer) 
	return oCreateMove(flInputSampleTime, cmd);
	if(g_Settings.misc.bhop) g_pMovement->Bhop(localplayer, cmd);
	return false;
}

int  __fastcall Hooks::DoPostScreenEffectsHook(void *thisptr, void * _EDX,int a1) {
	if(g_pEngine->GetLocalPlayer()) g_pGlow->Start();
	return oDoPostScreenEffects(thisptr,a1);
}
void __stdcall Hooks::OverrideViewHook(CViewSetup* pSetup) {

	 oOverrideView(pSetup);
}
void __stdcall Hooks::FrameStageNotifyHook(ClientFrameStage_t stage) {

	return oFrameStageNotify(stage);

 }

void __fastcall Hooks::SceneEndHook(void* thisptr, void* edx) {
	return oSceneEnd(thisptr);
	if (g_Settings.visuals.chams) g_pChams->Start();
 }
bool __fastcall Hooks::WriteUsercmdDeltaToBufferHook(IBaseClientDLL* this0, void * _EDX, int nSlot, void* buf, int from, int to, bool isNewCmd) {
	return true;
 }
void __stdcall Hooks::PlaySoundHook(const char *folderIme) {
	return oPlaySound(g_pVGuiSurface, folderIme);
 }
HRESULT __stdcall Hooks::EndSceneHook(IDirect3DDevice9 *pDevice)
{

	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFFF);

	if (!ImMenu::D3Init)
		ImMenu::GuiInit(m_hwndWindow, pDevice);

	ImGui::GetIO().MouseDrawCursor = menuOpen;

	ImGui_ImplDX9_NewFrame();

	if (menuOpen)
		ImMenu::Draw();

	ImGui::Render();


	return oEndScene(pDevice);
}

HRESULT __stdcall Hooks::ResetHook(IDirect3DDevice9 *pDevice, D3DPRESENT_PARAMETERS *pPresentationParameters)
{
	if (!ImMenu::D3Init)
		return oReset(pDevice, pPresentationParameters);

	ImGui_ImplDX9_InvalidateDeviceObjects();

	auto hr = oReset(pDevice, pPresentationParameters);

	if (hr >= 0)
		ImGui_ImplDX9_CreateDeviceObjects();

	return hr;
}
LRESULT __stdcall Hooks::WndProcHook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:

		pressedKey[VK_LBUTTON] = true;
		break;

	case WM_LBUTTONUP:

		pressedKey[VK_LBUTTON] = false;
		break;

	case WM_RBUTTONDOWN:

		pressedKey[VK_RBUTTON] = true;
		break;

	case WM_RBUTTONUP:

		pressedKey[VK_RBUTTON] = false;
		break;

	case WM_KEYDOWN:

		pressedKey[wParam] = true;
		break;

	case WM_KEYUP:

		pressedKey[wParam] = false;
		break;

	default: break;
	}
	ImMenu::Open();

	if (ImMenu::D3Init && menuOpen && ImGui_ImplDX9_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oldWindowProc, hWnd, uMsg, wParam, lParam);
}
void __stdcall Hooks::DrawModelExecuteHook(IMatRenderContext* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld) {
	return oDrawModelExecute(g_pMdlRender,ctx, state, pInfo, pCustomBoneToWorld);
}

