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
		else if (state == CollisionState::Exit) m_JumpCount = 1;
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
		/* If we are on the Ground. */
		if (m_Rigidbody->GetRigidbodyState() == RigidbodyState::Idle ||
			m_Rigidbody->GetRigidbodyState() == RigidbodyState::Walking || m_Rigidbody->GetRigidbodyState() == RigidbodyState::Running)
		{
			/* Applys force while the player is on the ground. */
			if (moveDirection != Vector2(0.0f) &&
				m_Rigidbody->GetBody()->GetLinearVelocity().x > -m_MaxGroundSpeed && m_Rigidbody->GetBody()->GetLinearVelocity().x < m_MaxGroundSpeed &&
				m_Rigidbody->GetBody()->GetLinearVelocity().y > -m_MaxGroundSpeed && m_Rigidbody->GetBody()->GetLinearVelocity().y < m_MaxGroundSpeed)
			{
				ActivateMotor(moveDirection, m_WheelSpeed);
			}
			else if (moveDirection != Vector2(0.0f) &&
					 m_Rigidbody->GetBody()->GetLinearVelocity().x < -m_MaxGroundSpeed && m_Rigidbody->GetBody()->GetLinearVelocity().x > m_MaxGroundSpeed &&
					 m_Rigidbody->GetBody()->GetLinearVelocity().y < -m_MaxGroundSpeed && m_Rigidbody->GetBody()->GetLinearVelocity().y > m_MaxGroundSpeed)
			{
				m_Rigidbody->GetRevJoint()->EnableMotor(false);
				//ActivateMotor(moveDirection, m_WheelSpeed * 1 / m_WheelSpeed);
			}
			else
			{
				m_Rigidbody->GetRevJoint()->EnableMotor(true);
			}
		}
		/* If we aren't. */
		else if (m_Rigidbody->GetRigidbodyState() == RigidbodyState::Jumping || m_Rigidbody->GetRigidbodyState() == RigidbodyState::Falling)
		{
			/* Applys force while the player is in the air */
			if (moveDirection != Vector2(0.0f) &&
				m_Rigidbody->GetBody()->GetLinearVelocity().x > -m_MaxAirSpeed && m_Rigidbody->GetBody()->GetLinearVelocity().x < m_MaxAirSpeed &&
				m_Rigidbody->GetBody()->GetLinearVelocity().y > -m_MaxAirSpeed && m_Rigidbody->GetBody()->GetLinearVelocity().y < m_MaxAirSpeed)
			{
				m_Rigidbody->OnApplyForce(Vector2(moveDirection.x * m_AirSpeed, 0.0f));
			}
			else
			{
				m_Rigidbody->OnApplyForce(Vector2(moveDirection.x * 0.1f, 0.0f));
			}
			m_Rigidbody->GetRevJoint()->EnableMotor(false);
		}
		else if (m_Rigidbody->GetRigidbodyState() == RigidbodyState::Floating || m_Rigidbody->GetRigidbodyState() == RigidbodyState::Underwater &&
				 m_Rigidbody->GetBody()->GetLinearVelocity().x > -m_MaxSwimSpeed && m_Rigidbody->GetBody()->GetLinearVelocity().x < m_MaxSwimSpeed &&
				 m_Rigidbody->GetBody()->GetLinearVelocity().y > -m_MaxSwimSpeed && m_Rigidbody->GetBody()->GetLinearVelocity().y < m_MaxSwimSpeed)
		{
			if (m_Rigidbody->GetRigidbodyState() == RigidbodyState::Floating)
			{
				m_Rigidbody->OnApplyForce(moveDirection * m_SwimSpeed);
			}
			else
			{
				m_Rigidbody->OnApplyForce(moveDirection * m_SwimSpeed * 1.25f);
			}
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
			if (m_Rigidbody->GetBody()->GetLinearVelocity().y <= 0.01f ||
				m_Rigidbody->GetRigidbodyState() == RigidbodyState::Floating && m_Rigidbody->GetRigidbodyState() != RigidbodyState::Underwater)
			{
				if (jumpDirection != Vector2(0))
				{
					m_Rigidbody->OnApplyImpulse(jumpDirection * m_JumpStrength);
					m_Rigidbody->SetRigidbodyState(RigidbodyState::Jumping);
					m_JumpCount++;
					Debug::LogLine("We Jumped!");
				}
			}
		}
	}
}