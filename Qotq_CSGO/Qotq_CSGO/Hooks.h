#pragma once
#include "SDK.h"
//typedefs
using CreateMove = bool(__stdcall*)(float, CUserCmd*);
extern CreateMove oCreateMove;

using DoPostScreenEffects = int(__thiscall*)(void*,int);
extern DoPostScreenEffects oDoPostScreenEffects;

using PaintTraverse = void(__thiscall*)(void*,vgui::VPANEL, bool, bool);
extern PaintTraverse oPaintTraverse;
//Hooking shit

namespace Hooks {
	extern bool __stdcall CreateMoveHook(float flInputSampleTime, CUserCmd* cmd);
	extern int  __fastcall DoPostScreenEffectsHook(void *thisptr, void * _EDX,int a1);
	extern void __fastcall PaintTraverseHook(void *thisptr, void * _EDX,vgui::VPANEL panel, bool forceRepaint, bool allowForce);
}