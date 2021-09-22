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

		float m_GroundSpeed;
		float m_AirSpeed;
		float m_JumpStrength;


	protected:
		friend class Rigidbody2D;
		friend class FileSystem;

		void OnStart() override;

		void OnCollisionEnter(Object* other) override;

		void OnCollisionStay(Object* other) override;

		void OnCollisionExit(Object* other) override;

	public:
		PlayerController() :
			m_Rigidbody			(nullptr),
			m_JumpResetLayers	(std::vector<Layer>()),

			m_MaxJumpCount		(1),
			m_JumpCount			(0),

			m_GroundSpeed		(4.0f),
			m_AirSpeed			(4.0f),
			m_JumpStrength		(0.4f)
		{};
		~PlayerController();

		void Move(Vector2 moveDirection);

		void Jump(Vector2 jumpDirection);

		const int GetMaxJumpCount() const { return m_MaxJumpCount; };
		const int GetJumpCount() const { return m_JumpCount; };
		const float GetGroundSpeed() const { return m_GroundSpeed; };
		const float GetAirSpeed() const { return m_AirSpeed; };
		const float GetJumpStrength() const { return m_JumpStrength; };

		std::vector<Layer> GetJumpResetLayers() const { return m_JumpResetLayers; };
		Layer GetJumpResetLayer(int index) const;

		void SetMaxJumpCount(int value) { m_MaxJumpCount = value; };
		void SetGroundSpeed(float value) { m_GroundSpeed = value; };
		void SetAirSpeed(float value) { m_AirSpeed = value; };
		void SetJumpStrength(float value) { m_JumpStrength = value; };

		void AttachJumpResetLayer(Layer layer);
		void DetachJumpResetLayer(int index);

	};
}