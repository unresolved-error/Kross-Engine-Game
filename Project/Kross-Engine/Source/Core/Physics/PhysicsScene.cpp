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
}
