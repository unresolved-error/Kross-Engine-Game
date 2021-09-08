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

	Layer PlayerController::GetJumpResetLayer(int index) const
	{
		/* If the index is outside the bounds of the array, early out. */
		if (index < 0 || index >= m_JumpResetLayers.size())
			return Layer::None;

		/* Return the Layer. */
		return m_JumpResetLayers[index];
	}

	void PlayerController::AttachJumpResetLayer(Layer layer)
	{
		/* Go through the Reset Layers and ind if the Layer has already been added. */
		for (int i = 0; i < m_JumpResetLayers.size(); i++)
		{
			if (m_JumpResetLayers[i] == layer)
				return; /* Early out if it has. */
		}

		/* Otherwise attach it. */
		m_JumpResetLayers.push_back(layer);
	}

	void PlayerController::DetachJumpResetLayer(int index)
	{
		/* If the index is outside the bounds of the array, early out. */
		if (index < 0 || index >= m_JumpResetLayers.size())
			return;

		/* Erase the Layer from the array. */
		m_JumpResetLayers.erase(m_JumpResetLayers.begin() + index);
	}

	void PlayerController::Move(Vector2 moveDirection)
	{
		/* If we are on the Ground. */
		if (m_JumpCount == 0)
		{
			/* Applys force while the player is on the ground. */
			if (moveDirection != Vector2(0.0f) && m_Rigidbody->GetBody()->GetLinearVelocity().x > -m_GroundSpeed &&
				m_Rigidbody->GetBody()->GetLinearVelocity().x < m_GroundSpeed &&
				m_Rigidbody->GetBody()->GetLinearVelocity().y > -m_GroundSpeed &&
				m_Rigidbody->GetBody()->GetLinearVelocity().y < m_GroundSpeed)
			{
				m_Rigidbody->OnApplyForce(moveDirection);
			}
			else
			{
				m_Rigidbody->OnApplyForce(moveDirection * 0.1f);
			}
		}
		/* If we aren't. */
		else
		{
			/* Applys force while the player is in the air */
			if (moveDirection != Vector2(0.0f) && m_Rigidbody->GetBody()->GetLinearVelocity().x > -m_AirSpeed &&
				m_Rigidbody->GetBody()->GetLinearVelocity().x < m_AirSpeed && 
				m_Rigidbody->GetBody()->GetLinearVelocity().y > -m_AirSpeed	&&
				m_Rigidbody->GetBody()->GetLinearVelocity().y < m_AirSpeed)
			{
				m_Rigidbody->OnApplyForce(moveDirection * 0.65f);
			}
			else
			{
				m_Rigidbody->OnApplyForce(moveDirection * 0.1f);
			}
		}
	}

	void PlayerController::Jump(Vector2 jumpDirection)
	{
		/* Checks the Rigidbody State and if the Controller hasn't hit max jump count.  */
		if (m_Rigidbody->GetRigidbodyState() != RigidbodyState::Falling && m_JumpCount < m_MaxJumpCount)
		{
			/* Applys a jump impulse */
			m_Rigidbody->OnApplyImpulse(jumpDirection * m_JumpStrength);
			m_JumpCount++;
		}
	}

	void PlayerController::OnCollisionEnter(Object* other)
	{
		if (other != nullptr)
		{
			/* Reset the Jump Count. */
			for (int i = 0; i < m_JumpResetLayers.size(); i++)
			{
 				if (other && other->GetLayer() == m_JumpResetLayers[i])
				{
					m_JumpCount = 0;
				}
			}
		}
	}

	void PlayerController::OnCollisionStay(Object* other)
	{
		if (other != nullptr)
		{
			/* Reset the Jump Count. */
			for (int i = 0; i < m_JumpResetLayers.size(); i++)
			{
				if (other->GetLayer() == m_JumpResetLayers[i])
				{
					m_JumpCount = 0;
				}
			}
		}
	}

	void PlayerController::OnCollisionExit(Object* other)
	{
		if (other != nullptr)
		{
			/* Reset the Jump Count. */
			for (int i = 0; i < m_JumpResetLayers.size(); i++)
			{
				if (other->GetLayer() == m_JumpResetLayers[i])
				{
					m_JumpCount = 0;
				}
			}
		}
	}
}