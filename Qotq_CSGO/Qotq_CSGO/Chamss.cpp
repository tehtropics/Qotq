#include "Chamss.h"
void CChamss::Start() {
	for (int i = 0; i <= g_pEngine->GetMaxClients(); i++) {
		auto pLocal = g_pEntityList->GetClientEntity(g_pEngine->GetLocalPlayer());
		C_BaseEntity* pEntity = g_pEntityList->GetClientEntity(i);
		if (!pEntity) continue;
		if (pEntity == pLocal) continue;
		if (pEntity->GetDormant()) continue;
		if (pEntity->GetHealth() < 1) continue;
		IMaterial *mat = g_pMatSystem->FindMaterial("debug/debugdrawflat", TEXTURE_GROUP_MODEL);
		g_pRenderView->SetColorModulation(197, 255, 0);
		g_pMdlRender->ForcedMaterialOverride(mat);
		pEntity->DrawModel(0x1/*STUDIO_RENDER*/, 255);
		g_pMdlRender->ForcedMaterialOverride(nullptr);
	}
}