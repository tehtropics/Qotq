#pragma once
#include "SDK.h"
class DrawManager
{
public:
	void textW(bool center, int font, int x, int y, Color c, wchar_t *pszString);
	void String(int font, bool bCenter, int x, int y, Color c, const char *fmt, ...);
	void textWRight(bool right, int font, int x, int y, Color c, wchar_t *pszString);
	void StringRight(int font, bool right, int x, int y, Color c, const char *fmt, ...);

	void OutlinedRect(int x, int y, int w, int h, Color &c);
	void FilledRect(int x, int y, int w, int h, Color &c);
	void Line(int x, int y, int x1, int y2, Color c);
	void OutlinedCircle(int x, int y, int r, int seg, Color c);

}; extern DrawManager* Draw;