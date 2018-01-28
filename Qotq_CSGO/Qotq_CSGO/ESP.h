#pragma once
#include "SDK.h"
class CESP {
public:
	void Start();
	RECT GetBox(C_BaseEntity* pEntity);
	bool WorldToScreen(const Vector& in, Vector& out);
}; extern CESP* g_pESP;