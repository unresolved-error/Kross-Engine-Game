/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "../Renderer/Image/Sprite.h"
#include "../Math/Math.h"

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

		Vector2 m_Position;		/* 0. */
		float m_Rotation;		/* 1. */
		Vector2 m_Scale;		/* 2. */

		/* Image Variables. */
		Sprite* p_Sprite;		/* 3. */

		/* Data Setting information. */
		List<bool> m_DataSetPoints;

	protected:

	public:
		/*!
		    Keyframe Constuctor.
		*/
		Keyframe() : 
			m_Position			(Vector2(0.0f)),
			m_Rotation			(0.0f),
			m_Scale				(Vector2(1.0f)),
			p_Sprite			(nullptr),
			m_DataSetPoints		(List<bool>(4))
		{
			/* Go through the Data Points and set them to false. */
			for (int i = 0; i < m_DataSetPoints.size(); i++)
				m_DataSetPoints[i] = false;
		};

		/*!
			Gets if the Position Data has been set.
		*/
		const bool HasPositionData() const { return m_DataSetPoints[0]; };

		/*!
			 Gets if the Rotation Data has been set.
		*/
		const bool HasRotationData() const { return m_DataSetPoints[1]; };

		/*!
			Gets if the Scale Data has been set.
		*/
		const bool HasScaleData() const { return m_DataSetPoints[2]; };

		/*!
			Gets if the Sprite Data has been set.
		*/
		const bool HasSpriteData() const { return m_DataSetPoints[3]; };

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
		Sprite* GetSprite() const { return p_Sprite; };

		/*!
			Set the Position Data.
		*/
		void SetPosition(Vector2 position) 
		{ 
			/* Set Position. */
			m_Position = position;

			/* Acknowledge the Data Point has been set. */
			m_DataSetPoints[0] = true; 
		}

		/*!
			Set the Rotation Data.
		*/
		void SetRotation(float rotation)
		{
			/* Set Rotation. */
			m_Rotation = rotation;

			/* Acknowledge the Data Point has been set. */
			m_DataSetPoints[1] = true;
		}

		/*!
			Set the Scale Data.
		*/
		void SetScale(Vector2 scale)
		{
			/* Set Scale. */
			m_Scale = scale;

			/* Acknowledge the Data Point has been set. */
			m_DataSetPoints[2] = true;
		}

		/*!
			Set the Sprite Data.
		*/
		void SetSprite(Sprite* sprite)
		{
			/* Set Sprite. */
			p_Sprite = sprite;

			/* Acknowledge the Data Point has been set. */
			m_DataSetPoints[3] = true;
		}

		/*!
			Clears the Position Data.
		*/
		void ClearPosition()
		{
			/* Set Position. */
			m_Position = Vector2(0.0f);

			/* Acknowledge the Data Point has been reset. */
			m_DataSetPoints[0] = false;
		}

		/*!
			Clears the Rotation Data.
		*/
		void ClearRotation()
		{
			/* Set Rotation. */
			m_Rotation = 0.0f;

			/* Acknowledge the Data Point has been reset. */
			m_DataSetPoints[1] = false;
		}

		/*!
			Clears the Scale Data.
		*/
		void ClearScale()
		{
			/* Set Scale. */
			m_Scale = Vector2(1.0f);

			/* Acknowledge the Data Point has been reset. */
			m_DataSetPoints[2] = false;
		}

		/*!
			Clears the Sprite Data.
		*/
		void ClearSprite()
		{
			/* Set Scale. */
			p_Sprite = nullptr;

			/* Acknowledge the Data Point has been reset. */
			m_DataSetPoints[3] = false;
		}
	};
}