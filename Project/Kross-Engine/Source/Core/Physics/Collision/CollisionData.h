/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#pragma once


#include "../../Core.h"

#include "ContactFilter.h"
#include "../Data/RaycastData.h"
#include "../Data/ColliderData.h"

namespace Kross
{
	class KROSS_API CollisionData
	{
	private:
		ColliderData* p_ColliderData;
		RaycastData* p_RayData;

	public:
		CollisionData() : 
			p_ColliderData	(KROSS_NEW ColliderData()),
			p_RayData		(KROSS_NEW RaycastData())
		{}
		~CollisionData()
		{
			delete p_ColliderData;
			delete p_RayData;
		}

		ColliderData* GetCollisionData() { return p_ColliderData; }

		RaycastData* GetRayData() { return p_RayData; }
	};
}
