#pragma once
#include "SDK.h"

class CUtils {
public:
	void Print(const char* fmt, ...);
	DWORD FindPatternIDA(std::string moduleName, std::string pattern);
}; extern CUtils* g_pUtils;