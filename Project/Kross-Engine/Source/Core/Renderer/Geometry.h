/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "../Math/Math.h"

namespace Kross
{
	struct KROSS_API Geometry
	{
	private:
		Vector2 m_Size;
		std::string m_Name;

	protected:
		friend class Sprite;

		// Sets the Geometry Name.
		void SetName(const std::string& name) { m_Name = name; };

		// Sets the Size of the Geometry.
		void SetSize(Vector2 size) { m_Size = size; };

	public:
		Geometry() :
			m_Size		(Vector2(0.0f)),
			m_Name		("")
		{};
		~Geometry() {};

		// Gets the Geometry Name.
		const std::string GetName() const { return m_Name; };

		// Gets the Size of the Geometry. (FULL WIDTH AND HEIGHT)
		Vector2 GetSize() const { return m_Size; };
	};
}