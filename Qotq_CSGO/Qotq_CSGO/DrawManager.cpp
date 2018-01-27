#include "DrawManager.h"

void DrawManager::textW(bool center, int font, int x, int y, Color c, wchar_t *pszString)
{
	if (center)
	{
		int wide, tall;
		g_pVGuiSurface->GetTextSize(font, pszString, wide, tall);
		x -= wide / 2;
		y -= tall / 2;
	}
	g_pVGuiSurface->DrawSetTextColor(c);
	g_pVGuiSurface->DrawSetTextFont(font);
	g_pVGuiSurface->DrawSetTextPos(x, y);
	g_pVGuiSurface->DrawPrintText(pszString, (int)wcslen(pszString), FONT_DRAW_DEFAULT);
}

void DrawManager::String(int font, bool Center, int x, int y, Color c, const char *fmt, ...)
{
	int apple = 0;
	/* set up buffer */
	char Buffer[2048] = { '\0' };

	/* set up varargs*/
	va_list Args;

	va_start(Args, fmt);
	vsprintf_s(Buffer, fmt, Args);
	va_end(Args);

	size_t Size = strlen(Buffer) + 1;

	/* set up widebuffer*/
	wchar_t* WideBuffer = new wchar_t[Size];

	/* char -> wchar */
	mbstowcs_s(0, WideBuffer, Size, Buffer, Size - 1);

	/* check center */
	int Width = 0, Height = 0;

	if (Center)
	{
		g_pVGuiSurface->GetTextSize(font, WideBuffer, Width, Height);
	}

	/* call and draw*/
	g_pVGuiSurface->DrawSetTextColor(c);
	g_pVGuiSurface->DrawSetTextFont(font);
	g_pVGuiSurface->DrawSetTextPos(x - (Width / 2), y);
	g_pVGuiSurface->DrawPrintText(WideBuffer, wcslen(WideBuffer));

	return;
}
void DrawManager::textWRight(bool right, int font, int x, int y, Color c, wchar_t *pszString)
{
	if (right)
	{
		int wide, tall;
		g_pVGuiSurface->GetTextSize(font, pszString, wide, tall);
		x -= wide;
	}
	g_pVGuiSurface->DrawSetTextColor(c);
	g_pVGuiSurface->DrawSetTextFont(font);
	g_pVGuiSurface->DrawSetTextPos(x, y);
	g_pVGuiSurface->DrawPrintText(pszString, (int)wcslen(pszString), FONT_DRAW_DEFAULT);
}

void DrawManager::StringRight(int font, bool bRight, int x, int y, Color c, const char *fmt, ...)
{
	wchar_t *pszStringWide = reinterpret_cast< wchar_t* >(malloc((strlen(fmt) + 1) * sizeof(wchar_t)));

	mbstowcs(pszStringWide, fmt, (strlen(fmt) + 1) * sizeof(wchar_t));

	textWRight(bRight, font, x, y, c, pszStringWide);

	free(pszStringWide);
}
void DrawManager::OutlinedRect(int x, int y, int w, int h, Color &c) {
	g_pVGuiSurface->DrawSetColor(c);
	g_pVGuiSurface->DrawOutlinedRect(x, y, x + w, y + h);
}
void DrawManager::FilledRect(int x, int y, int w, int h, Color &c) {
	g_pVGuiSurface->DrawSetColor(c);
	g_pVGuiSurface->DrawFilledRect(x, y, x + w, y + h);
}
void DrawManager::Line(int x, int y, int x1, int y2, Color c) {
	g_pVGuiSurface->DrawSetColor(c);
	g_pVGuiSurface->DrawLine(x, y, x1, y2);
}
void DrawManager::OutlinedCircle(int x, int y, int r, int seg, Color c) {
	g_pVGuiSurface->DrawSetColor(c);
	g_pVGuiSurface->DrawOutlinedCircle(x, y, r, seg);
}
