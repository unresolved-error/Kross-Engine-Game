/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 *		- Deklyn Palmer.
 */
#include "PlayerController.h"

#include "../Manager/SceneManager.h"
#include "../Manager/Time.h"
#include "../Application.h"

namespace Kross
{
	PlayerController::~PlayerController()
	{
		m_Rigidbody = nullptr;
	}

	void PlayerController::OnStart()
	{
		/* Assigns the rigidbody */
		m_Rigidbody = GetComponent<Rigidbody2D>();
	}

	void PlayerController::OnUpdate()
	{
		CollisionState state = m_Rigidbody->GetCollisionState();

		if (state == CollisionState::Enter) m_JumpCount = 0;
		else if (state == CollisionState::Stay) m_JumpCount = 0;
		else if (state == CollisionState::Exit) m_JumpCount = 0;
	}

	Layer PlayerController::GetJumpResetLayer(int index) const
	{
		/* If the index is outside the bounds of the array, early out. */
		if (index < 0 || index >= m_JumpResetLayers.size())
		{
			return Layer::None;
		}

		/* Return the Layer. */
		return m_JumpResetLayers[index];
	}

	void PlayerController::AttachJumpResetLayer(Layer layer)
	{
		/* Go through the Reset Layers and ind if the Layer has already been added. */
		for (int i = 0; i < m_JumpResetLayers.size(); i++)
		{
			if (m_JumpResetLayers[i] == layer)
			{
				return; /* Early out if it has. */
			}
		}

		/* Otherwise attach it. */
		m_JumpResetLayers.push_back(layer);
	}

	void PlayerController::DetachJumpResetLayer(int index)
	{
		/* If the index is outside the bounds of the array, early out. */
		if (index < 0 || index >= m_JumpResetLayers.size())
		{
			return;
		}

		/* Erase the Layer from the array. */
		m_JumpResetLayers.erase(m_JumpResetLayers.begin() + index);
	}

	void PlayerController::ActivateMotor(Vector2 moveDirection, float speed)
	{
		if (moveDirection.x > 0)
		{
			m_Rigidbody->GetRevJoint()->SetMotorSpeed(-speed);
			m_Rigidbody->GetRevJoint()->EnableMotor(true);
		}
		else if (moveDirection.x < 0)
		{
			m_Rigidbody->GetRevJoint()->SetMotorSpeed(speed);
			m_Rigidbody->GetRevJoint()->EnableMotor(true);
		}
		else
		{
			m_Rigidbody->GetRevJoint()->SetMotorSpeed(0.0f);
		}
	}

	void PlayerController::Move(Vector2 moveDirection)
	{
		//Debug::LogLine(std::to_string((char)m_Rigidbody->GetRigidbodyState()));

		/* If we are on the Ground. */
		if (m_Rigidbody->GetRigidbodyState() == RigidbodyState::Idle ||
			m_Rigidbody->GetRigidbodyState() == RigidbodyState::Walking || m_Rigidbody->GetRigidbodyState() == RigidbodyState::Running)
		{
			/* Applys force while the player is on the ground. */
			if (moveDirection != Vector2(0.0f) &&
				m_Rigidbody->GetBody()->GetLinearVelocity().x > -m_GroundSpeed && m_Rigidbody->GetBody()->GetLinearVelocity().x < m_GroundSpeed &&
				m_Rigidbody->GetBody()->GetLinearVelocity().y > -m_GroundSpeed && m_Rigidbody->GetBody()->GetLinearVelocity().y < m_GroundSpeed)
			{
				ActivateMotor(moveDirection, 40.0f);
			}
			else
			{
				ActivateMotor(moveDirection, 1.0f);
			}
		}
		/* If we aren't. */
		else if (m_Rigidbody->GetRigidbodyState() == RigidbodyState::Jumping ||	m_Rigidbody->GetRigidbodyState() == RigidbodyState::Falling)
		{
			/* Applys force while the player is in the air */
			if (moveDirection != Vector2(0.0f) &&
				m_Rigidbody->GetBody()->GetLinearVelocity().x > -m_AirSpeed && m_Rigidbody->GetBody()->GetLinearVelocity().x < m_AirSpeed &&
				m_Rigidbody->GetBody()->GetLinearVelocity().y > -m_AirSpeed && m_Rigidbody->GetBody()->GetLinearVelocity().y < m_AirSpeed)
			{
				m_Rigidbody->OnApplyForce(Vector2(moveDirection.x * 0.35f, 0.0f));
			}
			else
			{
				m_Rigidbody->OnApplyForce(Vector2(moveDirection.x * 0.01f, 0.0f));
			}
		}
		else if (m_Rigidbody->GetRigidbodyState() == RigidbodyState::Swimming)
		{
			m_Rigidbody->OnApplyForce(moveDirection * 0.5f);
		}

		if (moveDirection.x == 0.0f)
		{
			ActivateMotor(moveDirection);
		}
	}

	void PlayerController::Jump(Vector2 jumpDirection)
	{
		/* Bail out if the Jump count exceeds the max. */
		if (m_JumpCount >= m_MaxJumpCount)
		{
			return;
		}

		/* Checks the Rigidbody State. */
		if (m_Rigidbody->GetRigidbodyState() != RigidbodyState::Jumping && m_Rigidbody->GetRigidbodyState() != RigidbodyState::Falling)
		{
			/* Applys a jump impulse */
			if (m_Rigidbody->GetBody()->GetLinearVelocity().y <= 0.01f)
			{
				m_Rigidbody->OnApplyImpulse(jumpDirection * m_JumpStrength);
			}
			m_Rigidbody->SetRigidbodyState(RigidbodyState::Jumping);
			m_JumpCount++;
		}
	}

	//void PlayerController::OnCollisionEnter(Object* other)
	//{
	//	if (other != nullptr)
	//	{
	//		/* Reset the Jump Count. */
	//		for (int i = 0; i < m_JumpResetLayers.size(); i++)
	//		{
 	//			if (other && other->GetLayer() == m_JumpResetLayers[i])
	//			{
	//				m_JumpCount = 0;
	//			}
	//		}
	//	}
	//}
	//
	//void PlayerController::OnCollisionStay(Object* other)
	//{
	//	if (other != nullptr)
	//	{
	//		/* Reset the Jump Count. */
	//		for (int i = 0; i < m_JumpResetLayers.size(); i++)
	//		{
	//			if (other->GetLayer() == m_JumpResetLayers[i])
	//			{
	//				m_JumpCount = 0;
	//			}
	//		}
	//	}
	//}
	//
	//void PlayerController::OnCollisionExit(Object* other)
	//{
	//	if (other != nullptr)
	//	{
	//		/* Reset the Jump Count. */
	//		for (int i = 0; i < m_JumpResetLayers.size(); i++)
	//		{
	//			if (other->GetLayer() == m_JumpResetLayers[i])
	//			{
	//				m_JumpCount = 0;
	//			}
	//		}
	//	}
	//{
}