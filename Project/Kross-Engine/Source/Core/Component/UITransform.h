/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "Component.h"
#include "../Math/Math.h"

namespace Kross
{
	class KROSS_API UITransform : public Component
	{
	private:
		Vector2 m_Ratio;

	protected:
		/*!
			Update Method.
		*/
		void OnUpdate() override;

	public:
		UITransform();
		~UITransform();

		/*!
			Get's the Ratio.
		*/
		const Vector2 GetRatio() const;

		/*!
			Set's the Ratio.
		*/
		void SetRatio(Vector2 offset);
	};
}