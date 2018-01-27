#pragma once
#include "SDK.h"
class C_BaseEntity {
public:
	bool IsPlayer();
	ClientClass* GetClientClass();
	int Health();
	int Team();
};