#include "Glow.h"

void CGlow::Start() {
	CGlowObjectManager* GlowObjectManager = g_pGlowObjectManager;
	CGlowObjectManager::GlowObjectDefinition_t* glowEntity;
	for (int i = 0; i < GlowObjectManager->size; i++)
	{
		glowEntity = &GlowObjectManager->m_GlowObjectDefinitions[i];
		C_BaseEntity* Entity = glowEntity->getEntity();
		if (!Entity) continue;
		ClientClass* EntityClass = (ClientClass*)Entity->GetClientClass();
		if (EntityClass->m_ClassID == ClassId_CCSPlayer)glowEntity->set(Color(255, 0, 0, 255));
	}
}