#include "ImMenu.h"
namespace ImMenu
{
	ImFont* Im_Font;
	void GuiInit(HWND window, IDirect3DDevice9 *pDevice)
	{
		ImGui_ImplDX9_Init(window, pDevice);
		ImGuiStyle &style = ImGui::GetStyle();
		//do some pStyles here

		Im_Font = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arial.ttf", 13);
		D3Init = true;
	}
	void Open() {

		static bool bDown = false;
		static bool bClicked = false;
		static bool bPrevMenuState = menuOpen;

		if (pressedKey[VK_INSERT])
		{
			bClicked = false;
			bDown = true;
		}
		else if (!pressedKey[VK_INSERT] && bDown)
		{
			bClicked = true;
			bDown = false;
		}
		else
		{
			bClicked = false;
			bDown = false;
		}

		if (bClicked)
		{
			menuOpen = !menuOpen;
		}

		if (bPrevMenuState != menuOpen)
		{
			std::string msg = "cl_mouseenable " + std::to_string(!menuOpen);
			g_pEngine->ExecuteClientCmd(msg.c_str());
		}

		bPrevMenuState = menuOpen;
	}
	void Draw() {
		ImGui::SetNextWindowSize(ImVec2(500, 300), ImGuiSetCond_FirstUseEver);
		if (ImGui::Begin("Qtoq Cheetos", &menuOpen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_OnlyDragByTitleBar))
		{

		}ImGui::End();
	}
}
