#include "CBaseEntity.h"
bool C_BaseEntity::IsPlayer()
{
	return VT::VFunc<bool(__thiscall*)(C_BaseEntity*)>(this, 152)(this);
}

ClientClass* C_BaseEntity::GetClientClass()
{
	void *pNetworked = (void*)(this + 0x8);
	typedef ClientClass*(__thiscall *OrigFn)(void*);
	return VT::VFunc<OrigFn>(pNetworked, 2)(pNetworked);
}
int C_BaseEntity::Health() {
	return *reinterpret_cast<int*>((uintptr_t)this + NetVars.m_iHealth);
}
int C_BaseEntity::Team() {
	return *reinterpret_cast<int*>((uintptr_t)this + NetVars.m_iTeamNum);
}