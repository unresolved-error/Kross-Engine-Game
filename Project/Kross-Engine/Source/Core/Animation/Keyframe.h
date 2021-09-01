/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"


#include "../Renderer/Image/Sprite.h"
#include "../Math/Math.h"
#include "KeyframeDataFlags.h"

namespace Kross
{
	/*!
		\class Keyframe
		\details Storage of Sprite, position, rotation and scaling information.
	*/
	class KROSS_API Keyframe
	{
	private:
		/* Transform Variables. */

		Vector2 m_Position;
		float m_Rotation;
		Vector2 m_Scale;

		/* Image Variables. */

		Sprite* m_Sprite;

		/* Data Checking information. */

		unsigned short m_DataFlags;

	protected:

	public:
		/*!
		    Keyframe Constuctor.
		*/
		Keyframe() : 
			m_Position			(Vector2(0.0f)),
			m_Rotation			(0.0f),
			m_Scale				(Vector2(1.0f)),
			m_Sprite			(nullptr),
			m_DataFlags			(KeyframeDataFlags::Empty)
		{};

		/*!
			Gets the Data Flags.
		*/
		unsigned short GetFlags() const { return m_DataFlags; };

		/*!
			Gets the Position Data.
		*/
		Vector2 GetPosition() const { return m_Position; };

		/*!
			Gets the Rotation Data.
		*/
		float GetRotation() const { return m_Rotation; };

		/*!
			Gets the Scale Data.
		*/
		Vector2 GetScale() const { return m_Scale; };

		/*!
			Gets the Sprite Data.
		*/
		Sprite* GetSprite() const { return m_Sprite; };

		/*!
			Set the Position Data.
		*/
		void SetPosition(Vector2 position) 
		{ 
			/* Set Position. */
			m_Position = position;

			/* Acknowledge the Data Point has been set. */
			if (!(m_DataFlags & KeyframeDataFlags::PositionData))
				m_DataFlags |= KeyframeDataFlags::PositionData;
		}

		/*!
			Set the Rotation Data.
		*/
		void SetRotation(float rotation)
		{
			/* Set Rotation. */
			m_Rotation = rotation;

			/* Acknowledge the Data Point has been set. */
			if (!(m_DataFlags & KeyframeDataFlags::RotationData))
				m_DataFlags |= KeyframeDataFlags::RotationData;
		}

		/*!
			Set the Scale Data.
		*/
		void SetScale(Vector2 scale)
		{
			/* Set Scale. */
			m_Scale = scale;

			/* Acknowledge the Data Point has been set. */
			if (!(m_DataFlags & KeyframeDataFlags::ScaleData))
				m_DataFlags |= KeyframeDataFlags::ScaleData;
		}

		/*!
			Set the Sprite Data.
		*/
		void SetSprite(Sprite* sprite)
		{
			/* Set Sprite. */
			m_Sprite = sprite;

			/* Acknowledge the Data Point has been set. */
			if (!(m_DataFlags & KeyframeDataFlags::SpriteData))
				m_DataFlags |= KeyframeDataFlags::SpriteData;
		}

		/*!
			Clears the Position Data.
		*/
		void ClearPosition()
		{
			/* Set Position. */
			m_Position = Vector2(0.0f);

			/* Acknowledge the Data Point has been reset. */
			if (m_DataFlags & KeyframeDataFlags::PositionData)
				m_DataFlags &= ~KeyframeDataFlags::PositionData;
		}

		/*!
			Clears the Rotation Data.
		*/
		void ClearRotation()
		{
			/* Set Rotation. */
			m_Rotation = 0.0f;

			/* Acknowledge the Data Point has been reset. */
			if (m_DataFlags & KeyframeDataFlags::RotationData)
				m_DataFlags &= ~KeyframeDataFlags::RotationData;
		}

		/*!
			Clears the Scale Data.
		*/
		void ClearScale()
		{
			/* Set Scale. */
			m_Scale = Vector2(1.0f);

			/* Acknowledge the Data Point has been reset. */
			if (m_DataFlags & KeyframeDataFlags::ScaleData)
				m_DataFlags &= ~KeyframeDataFlags::ScaleData;
		}

		/*!
			Clears the Sprite Data.
		*/
		void ClearSprite()
		{
			/* Set Scale. */
			m_Sprite = nullptr;

			/* Acknowledge the Data Point has been reset. */
			if (m_DataFlags & KeyframeDataFlags::SpriteData)
				m_DataFlags &= ~KeyframeDataFlags::SpriteData;
		}
	};
}