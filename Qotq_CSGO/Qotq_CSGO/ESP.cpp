#include "ESP.h"
void CESP::Start() {
	for (int i = 0; i <= g_pEngine->GetMaxClients(); i++) {
		auto pLocal = g_pEntityList->GetClientEntity(g_pEngine->GetLocalPlayer());
		auto pEntity = g_pEntityList->GetClientEntity(i);
		if (!pEntity) continue;
		if (pEntity == pLocal)continue;
		if (pEntity->GetDormant()) continue;
		if (pEntity->GetHealth() < 1) continue;
		RECT EspRect;
		player_info_t info;
		EspRect = GetBox(pEntity);
		if (IsRectEmpty(&EspRect)) continue;
		Color BoxClr = pEntity->GetTeam() == pLocal->GetTeam() ? Color(0, 255, 0, 255) : Color(255, 0, 0, 255);
		g_pEngine->GetPlayerInfo(pEntity->GetIndex(), &info);
		if (g_Settings.visuals.esp)PlayerBox(pEntity, EspRect, BoxClr);
		if (g_Settings.visuals.espname)PlayerName(pEntity, EspRect, info);
		if (g_Settings.visuals.espweapon)PlayerWeapon(pEntity, EspRect);
		if (g_Settings.visuals.distance) PlayerDistance(pEntity, EspRect, pLocal);
		if (g_Settings.visuals.health) PlayerHealth(pEntity, EspRect);
		if (g_Settings.visuals.money) PlayerMoney(pEntity, EspRect);
	}
}
void CESP::PlayerBox(C_BaseEntity* pEntity, RECT EspRect, Color BoxClr){	
	Draw->OutlinedRect(EspRect.left, EspRect.top, EspRect.right - EspRect.left, EspRect.bottom - EspRect.top, BoxClr);
	Draw->OutlinedRect(EspRect.left - 1, EspRect.top - 1, EspRect.right - EspRect.left + 2, EspRect.bottom - EspRect.top + 2, Color(0, 0, 0, 255));
	Draw->OutlinedRect(EspRect.left + 1, EspRect.top + 1, EspRect.right - EspRect.left - 2, EspRect.bottom - EspRect.top - 2, Color(0, 0, 0, 255));
}
void CESP::PlayerHealth(C_BaseEntity* pEntity, RECT EspRect) {
	Draw->StringRight(true, F_ESP, EspRect.left - 7, EspRect.top - 2, Color(255, 255, 255, 255), "HP:%d", pEntity->GetHealth());
	auto hp = pEntity->GetHealth();
	auto green = int(hp * 2.55f);
	auto red = 255 - green;
	auto height = ((EspRect.bottom - EspRect.top) * hp) / 100;
	Draw->FilledRect(EspRect.left - 5, EspRect.top - 1, 3, EspRect.bottom - EspRect.top + 2, Color(0, 0, 0, 255));
	Draw->FilledRect(EspRect.left - 4, EspRect.bottom - height, 1, height, Color(red, green, 0, 255));
}
void CESP::PlayerWeapon(C_BaseEntity* pEntity, RECT EspRect) {
	auto weapon = pEntity->GetActiveWeapon();
	auto weapondata = weapon->GetCSWeaponData();
	Draw->String(F_ESP, true, (EspRect.left + EspRect.right) / 2, EspRect.bottom + 1, Color(255, 255, 255, 255), "%s[%d/%d]", weapon->GetWeaponName().c_str(), weapon->Clip1(), weapondata->iMaxClip1);

}
void CESP::PlayerMoney(C_BaseEntity* pEntity, RECT EspRect) {
	auto money = pEntity->GetMoney();
	Draw->String(F_ESP, false, EspRect.right + 3, EspRect.top + 10, Color(0, 222, 0, 255), "%d$", money);
}
void CESP::PlayerName(C_BaseEntity* pEntity, RECT EspRect,player_info_t info) {
	std::string name = info.szName;
	Draw->String(F_ESP, true, (EspRect.left + EspRect.right) / 2, EspRect.top - 12, Color(255, 255, 255, 255), name.c_str());

}
void CESP::PlayerDistance(C_BaseEntity* pEntity, RECT EspRect, C_BaseEntity* pLocal) {
	auto a = pLocal->GetOrigin();
	auto b = pEntity->GetOrigin();
	int distance = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2)) * 0.0254f;
	Draw->String(F_ESP, false, EspRect.right + 3, EspRect.top, Color(255, 255, 255, 255), "%dM", distance);
}
bool CESP::WorldToScreen(const Vector& in, Vector& out) {
	static ptrdiff_t ptrViewMatrix;
	if (!ptrViewMatrix)
	{
		ptrViewMatrix = static_cast<ptrdiff_t>(g_pUtils->FindPatternIDA("client.dll", "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9"));
		ptrViewMatrix += 0x3;
		ptrViewMatrix = *reinterpret_cast<uintptr_t*>(ptrViewMatrix);
		ptrViewMatrix += 176;
	}
	const matrix3x4_t& worldToScreen = *(matrix3x4_t*)ptrViewMatrix;

	int ScrW, ScrH;

	g_pEngine->GetScreenSize(ScrW, ScrH);

	float w = worldToScreen[3][0] * in[0] + worldToScreen[3][1] * in[1] + worldToScreen[3][2] * in[2] + worldToScreen[3][3];
	out.z = 0;
	if (w > 0.01)
	{
		float inverseWidth = 1 / w;
		out.x = (ScrW / 2) + (0.5 * ((worldToScreen[0][0] * in[0] + worldToScreen[0][1] * in[1] + worldToScreen[0][2] * in[2] + worldToScreen[0][3]) * inverseWidth) * ScrW + 0.5);
		out.y = (ScrH / 2) - (0.5 * ((worldToScreen[1][0] * in[0] + worldToScreen[1][1] * in[1] + worldToScreen[1][2] * in[2] + worldToScreen[1][3]) * inverseWidth) * ScrH + 0.5);
		return true;
	}
	return false;
}
RECT CESP::GetBox(C_BaseEntity* pEntity) {
	RECT rect{};
	auto collideable = pEntity->GetCollideable();

	if (!collideable)
		return rect;

	auto min = collideable->OBBMins();
	auto max = collideable->OBBMaxs();

	auto trans = pEntity->GetCoordinateFrame();

	Vector points[] = {
		Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z)
	};

	Vector pointsTransformed[8];
	for (int i = 0; i < 8; i++) {
		Math::VectorTransform(points[i], trans, pointsTransformed[i]);
	}

	Vector screen_points[8] = {};

	for (int i = 0; i < 8; i++) {
		if (!WorldToScreen(pointsTransformed[i], screen_points[i]))
			return rect;
	}

	auto left = screen_points[0].x;
	auto top = screen_points[0].y;
	auto right = screen_points[0].x;
	auto bottom = screen_points[0].y;

	for (int i = 1; i < 8; i++) {
		if (left > screen_points[i].x)
			left = screen_points[i].x;
		if (top < screen_points[i].y)
			top = screen_points[i].y;
		if (right < screen_points[i].x)
			right = screen_points[i].x;
		if (bottom > screen_points[i].y)
			bottom = screen_points[i].y;
	}
	return RECT{ (long)left, (long)bottom, (long)right, (long)top };

}
