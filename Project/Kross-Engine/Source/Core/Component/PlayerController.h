/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 *		- Deklyn Palmer.
 */
#pragma once

#include "../Core.h"

#include "Component.h"
#include "../Input.h"

namespace Kross
{
	class KROSS_API PlayerController : public Component
	{
	private:
		Rigidbody2D* m_Rigidbody;

		std::vector<Layer> m_JumpResetLayers;

		int m_MaxJumpCount;
		int m_JumpCount;

		float m_WheelSpeed;
		float m_MaxGroundSpeed;

		float m_AirSpeed;
		float m_MaxAirSpeed;

		float m_SwimSpeed;
		float m_MaxSwimSpeed;

		float m_JumpStrength;

		float m_CoolDownTimer = 0.05f;
		float m_CoolDownElapsed = 0.0f;


	protected:
		friend class Rigidbody2D;
		friend class FileSystem;

		void OnStart() override;

		void OnUpdate() override;

	public:
		PlayerController() :
			m_Rigidbody			(nullptr),
			m_JumpResetLayers	(std::vector<Layer>()),

			m_MaxJumpCount		(1),
			m_JumpCount			(0),

			m_WheelSpeed		(25.0f),
			m_MaxGroundSpeed	(2.5f),

			m_AirSpeed			(0.2f),
			m_MaxAirSpeed		(1.25f),

			m_SwimSpeed			(0.75f),
			m_MaxSwimSpeed		(1.25f),

			m_JumpStrength		(0.35f)
		{};
		~PlayerController();

		void Move(Vector2 moveDirection);

		void Jump(Vector2 jumpDirection);

		const int GetMaxJumpCount() const { return m_MaxJumpCount; };
		const int GetJumpCount() const { return m_JumpCount; };
		const float GetGroundSpeed() const { return m_MaxGroundSpeed; };
		const float GetAirSpeed() const { return m_MaxAirSpeed; };
		const float GetJumpStrength() const { return m_JumpStrength; };

		std::vector<Layer> GetJumpResetLayers() const { return m_JumpResetLayers; };
		Layer GetJumpResetLayer(int index) const;

		void SetMaxJumpCount(int value) { m_MaxJumpCount = value; };
		void SetGroundSpeed(float value) { m_MaxGroundSpeed = value; };
		void SetAirSpeed(float value) { m_MaxAirSpeed = value; };
		void SetJumpStrength(float value) { m_JumpStrength = value; };

		void AttachJumpResetLayer(Layer layer);
		void DetachJumpResetLayer(int index);


		void ActivateMotor(Vector2 moveDirection, float speed = 0.0f);
	};
}