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
		delete p_PhysicsWorld;
	}

	void PhysicsScene::DetachBody(Body* body)
	{
		int deleteIndex = 0;
		for (int i = 0; i < m_bodies.size(); i++)
		{
			if (m_bodies[i] == body)
			{
				deleteIndex = i;
				m_bodies[i] = nullptr;
				break;
			}
		}

		p_PhysicsWorld->DestroyBody(body);
		m_bodies.erase(m_bodies.begin() + deleteIndex);
	}
}
