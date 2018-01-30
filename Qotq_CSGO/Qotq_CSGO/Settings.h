#pragma once
struct SSettings
{
	struct{
		bool glow;
		bool esp;
		bool espname;
		bool espweapon;
		bool health;
		bool money;
		bool distance;
		bool chams;
	}visuals;
	struct {
		bool bhop;
	}misc;

}; extern SSettings g_Settings;