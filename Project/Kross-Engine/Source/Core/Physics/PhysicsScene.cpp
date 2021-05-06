/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#include "PhysicsScene.h"

namespace Kross
{
	PhysicsScene::~PhysicsScene()
	{
		for (int i = 0; i < p_ParticleSystem->GetParticleCount(); i++)
		{
			p_ParticleSystem->DestroyParticle(i);
		}
		delete p_PhysicsWorld;

	}
}
