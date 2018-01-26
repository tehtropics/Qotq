#include "CBaseEntity.h"

ClientClass* C_BaseEntity::GetClientClass()
{
	void *pNetworked = (void*)(this + 0x8);
	typedef ClientClass*(__thiscall *OrigFn)(void*);
	return VT::VFunc<OrigFn>(pNetworked, 2)(pNetworked);
}