/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "Object.h"

namespace Kross
{
	class KROSS_API GameObject : public Object
	{
	private:

	protected:

	public:
		GameObject() {};
		GameObject(const std::string& name) { SetName(name); };

		/* ---------------------------------------------------------------------------- 
			 Nothing else is really needed due to the Object class defining eveything.
		   ----------------------------------------------------------------------------  */
	};
}