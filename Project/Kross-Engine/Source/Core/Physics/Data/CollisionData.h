/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#pragma once


#include "../../Core.h"

#include "../Collision/ContactFilter.h"
#include "RaycastData.h"

namespace Kross
{
	class KROSS_API CollisionData
	{
	private:
		RaycastData* p_RayData;

	public:
		CollisionData() : 
			p_RayData		(KROSS_NEW RaycastData())
		{}
		~CollisionData()
		{
			delete p_RayData;
		}

		RaycastData* GetRayData() { return p_RayData; }
	};
}
