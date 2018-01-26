#pragma once
#include "SDK.h"
class C_BaseEntity {
public:
	bool IsPlayer();
	bool IsWeapon();
	ClientClass* GetClientClass();
};