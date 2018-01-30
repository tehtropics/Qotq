#pragma once
#include "SDK.h"
class CESP {
public:
	void Start();
private:
	void PlayerBox(C_BaseEntity* pEntity, RECT EspRect, Color BoxClr);
	void PlayerHealth(C_BaseEntity* pEntity, RECT EspRect);
	void PlayerWeapon(C_BaseEntity* pEntity, RECT EspRect);
	void PlayerMoney(C_BaseEntity* pEntity, RECT EspRect);
	void PlayerName(C_BaseEntity* pEntity, RECT EspRect, player_info_t info);
	void PlayerDistance(C_BaseEntity* pEntity, RECT EspRect,  C_BaseEntity* pLocal);
	RECT GetBox(C_BaseEntity* pEntity);
	bool WorldToScreen(const Vector& in, Vector& out);
}; extern CESP* g_pESP;