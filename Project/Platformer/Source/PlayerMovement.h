#pragma once

#include <Kross.h>

using namespace Kross;

class PlayerMovement : public Script
{
public:
	PlayerMovement()
	{
		/* Every Script Must do this! */
		m_Name = "PlayerMovement";
	};
	~PlayerMovement() {};

	Object* m_Camera = nullptr;
	Object* m_Gun = nullptr;

	TextRenderer* m_TextRenderer = nullptr;
	PlayerController* m_Controller = nullptr;
	SpriteRenderer* m_SpriteRenderer = nullptr;
	Window* m_Window = nullptr;
	Rigidbody2D* m_RigidBody = nullptr;
	AudioPlayer* m_AudioPlayer = nullptr;
	Animator* m_Animator = nullptr;

	Vector2 m_GunOffset = Vector2(0.0f, -0.11f);
	Vector2 m_TextRendererOffset = Vector2(0.0f, 1.5f);

	int m_ControllerID = 0;
	int m_FrameCount = 0;

	float m_TimeElapsed = 0.0f;

	float m_VelocityThreshold = 0.05f;

	Script* Duplicate() override
	{
		return KROSS_NEW PlayerMovement();
	}

	void Start() override
	{
		/* Grab All of the Local Components. */
		m_SpriteRenderer = GetComponent<SpriteRenderer>();
		m_RigidBody = GetComponent<Rigidbody2D>();
		m_Animator = GetComponent<Animator>();
		m_AudioPlayer = GetComponent<AudioPlayer>();
		m_Controller = GetComponent<PlayerController>();

		/* Grab External Object Related things. */
		m_TextRenderer = SceneManager::GetCurrentScene()->FindObject("Text")->GetComponent<TextRenderer>();
		m_Gun = SceneManager::GetCurrentScene()->FindObject("Gun");
		m_Camera = SceneManager::GetCurrentScene()->GetCamera();
		
		/* Grab the Window. */
		m_Window = Application::GetWindow();

		/* See if a Controller is Connected. */
		m_ControllerID = Input::GetAvalibleController();
	}

	void Update() override
	{
		/* Create a Base Input Variable. */
		Vector2 input = Vector2(0.0f);

		/* if the Controller is Connected. */
		if (Input::ControllerConnected(m_ControllerID))
		{
			/* Grab it's Input. */
			input = Vector2(Input::GetControllerAxis(m_ControllerID, Controller::LeftStickHorizontal, 0.2f), 0.0f);
		}

		/* Use Keyboard and Mouse instead. */
		else
		{
			/* Keep Checking if a Controller Gets Connected. */
			m_ControllerID = Input::GetAvalibleController();

			/* Grab the Input needed. */
			input = Vector2(Input::GetAxis(Axis::KeyboardHorizontal), 0.0f);
		}

		/* If the Object isn't at the End of a Level. */
		if (m_GameObject->m_Transform->m_Position.x < 217.0f) 
		{
			/* Move the Player. */
			VisualUpdate(input);
			m_Controller->Move(input);
			Vector2 jumpDir = Vector2(0.0f, (float)Input::GetKeyPressed(Key::Space));
			m_Controller->Jump(jumpDir);
		}

		/* Lerp the Camera's Position to the Players. */
		m_Camera->m_Transform->m_Position = Math::Lerp(m_Camera->m_Transform->m_Position, m_GameObject->m_Transform->m_Position, Time::GetDeltaTime() * 4.0f);

		/* Clamp the Camera Position. */
		m_Camera->m_Transform->m_Position.x = glm::clamp(m_Camera->m_Transform->m_Position.x, -1.25f, 215.75f);
		m_Camera->m_Transform->m_Position.y = glm::clamp(m_Camera->m_Transform->m_Position.y, -2.0f, 1.5f);

		/* --- FRAME COUNTER STUFF --- */

		/* If the Elapsed Time hasn't hit a second yet. */
		if (m_TimeElapsed < 1.0f)
		{
			/* Keep tickign up, add one to the Frame Counter. */
			m_TimeElapsed += Time::GetDeltaTime();
			m_FrameCount++;
		}

		/* If it happens to be a second or a little more. */
		else
		{
			/* Reset Everything. */
			m_TimeElapsed = 0.0f;

			/*	
				Normally text would be changed here... 
				Display the previous Frame Count before resetting... 
			*/

			m_FrameCount = 0;
		}

		/* --------------------------- */

		/* --- GUN RELATED THINGS --- */

		/* If the Gun Obejct Exists. */
		if (m_Gun)
		{
			/* Grab the True Offset. */
			Vector2 trueOffset;

			if (m_SpriteRenderer->GetFlipX())
			{
				trueOffset = Vector2(-1.0f, 1.0f);
			}
			else
			{
				trueOffset = Vector2(1.0f, 1.0f);
			}
			
			/* Set the Guns Position based on the true offset. */
			m_Gun->m_Transform->m_Position = m_GameObject->m_Transform->m_Position + (m_GunOffset * trueOffset);
		}

		/* -------------------------- */

		/* --- TEXT RENDERER STUFF --- */

		/* If we have found a Text Renderer*/
		if (m_TextRenderer)
		{
			/* If the Object less than 188 on the x. */
			if (m_GameObject->m_Transform->m_Position.x < 188)
			{
				/* Grab the Colour and Extract it's alpha. */
				Colour textcol = m_TextRenderer->GetColour();
				textcol.a = 0;

				/* Set its Colour. */
				m_TextRenderer->SetColour(textcol);
			}
			/* If the Object is Less than 217 on the x but larger than 188. */
			else if (m_GameObject->m_Transform->m_Position.x < 216.9)
			{
				/* Calculate its Alpha Value. */
				float alph = (m_GameObject->m_Transform->m_Position.x - 188.0f) / 10.0f;

				/* Grab the Colour and Extract it's alpha. */
				Colour textcol = m_TextRenderer->GetColour();
				textcol.a = alph;

				/* Set its Colour. */
				m_TextRenderer->SetColour(textcol);

			}

			/* Set the Text Renderer's Position. */
			m_TextRenderer->m_GameObject->m_Transform->m_Position = m_GameObject->m_Transform->m_Position + m_TextRendererOffset;

		}
		/* --------------------------- */
	}

	/*! 
		Moves the Player Based on Input. 
	*/
	void VisualUpdate(Vector2 input)
	{
		/* Animation Setting.*/

		/* If the Rigidbody's Velocity in the Vertical direction is inside of the threshold. */
		if (m_RigidBody->GetBody()->GetLinearVelocity().y <= m_VelocityThreshold && m_RigidBody->GetBody()->GetLinearVelocity().y >= -m_VelocityThreshold)
		{
			/* If the Rigidbody's Velocity in the Horizontal direction is inside of the threshold. */
			if (m_RigidBody->GetBody()->GetLinearVelocity().x <= m_VelocityThreshold && m_RigidBody->GetBody()->GetLinearVelocity().x >= -m_VelocityThreshold)
			{
				/* Set to the Idle Animation. */
				m_Animator->SetCurrentAnimation(0);
			}
			/* If the Horizontal Velocity has breached the threshold. */
			else
			{
				/* Set to the Walk Animation. */
				m_Animator->SetCurrentAnimation(1);
			}
		}
		/* If the Vertical Velocity has breached the threshold. */
		else
		{
			/* If moving upwards. */
			if (m_RigidBody->GetBody()->GetLinearVelocity().y >= m_VelocityThreshold)
			{
				/* Set to the Jump Up Animation. */
				m_Animator->SetCurrentAnimation(2);
			}

			/* If moving downwards. */
			else if(m_RigidBody->GetBody()->GetLinearVelocity().y <= -m_VelocityThreshold)
			{
				/* Set to the Jump Down Animation. */
				m_Animator->SetCurrentAnimation(3);
			}
		}

		/* Flip Based on the Input x Value. */

		if (input.x > 0)
		{
			/* Face Right. */
			m_SpriteRenderer->SetFlipX(false);
		}
		else if (input.x < 0)
		{
			/* Face Left. */
			m_SpriteRenderer->SetFlipX(true);
		}
	}
};