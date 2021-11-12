#pragma once

#include <Kross.h>

#include "Health.h"
#include "bgAudioManager.h"
#include "DonutMovement.h"

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

	Object* m_Gun = nullptr;
	Window* m_Window = nullptr;
	Health* m_Health = nullptr;
	Object* m_Camera = nullptr;
	Animator* m_Animator = nullptr;
	Rigidbody2D* m_RigidBody = nullptr;
	AudioPlayer* m_AudioPlayer = nullptr;
	TextRenderer* m_TextRenderer = nullptr;
	PlayerController* m_Controller = nullptr;
	SpriteRenderer* m_SpriteRenderer = nullptr;

	Vector2 m_GunOffset = Vector2(0.0f, -0.11f);
	Vector2 m_TextRendererOffset = Vector2(0.0f, 1.5f);

	std::vector<SpriteRenderer*> m_HealthRenderers = std::vector<SpriteRenderer*>();
	std::vector<Sprite*> m_HealthSprites = std::vector<Sprite*>(); 

	Object* m_TopBar = nullptr;
	Object* m_BottomBar = nullptr;

	Sprite* m_HitSprite = nullptr;

	std::vector<AudioPlayer*> m_AudioPlayers;


	int m_ControllerID = 0;

	float m_VelocityThreshold = 0.05f;

	float m_CameraShakeMagnitudeMax = 0.025f;
	float m_CameraShakeMagnitude = 0.0f;
	float m_ShakeCoolDownTime = 0.1f;
	float m_ShakeCoolDownTimeElapsed = 0.0f;

	float m_GracePeriodTime = 0.5f;
	float m_GracePeriodTimeElapsed = 0.0f;

	float m_EndGameTimer = 0.0f;
	float m_EndGameTimerMax = 5.0f;

	float m_EndGameTransitionTimer = 0.0f;
	float m_EndGameTransitionTimerMax = 1.5f;

	bool m_ShakeCamera = false;
	bool m_IsHurt = false;
	bool m_VisualHurt = false;

	bool m_MoveCinematicBars = false;
	bool m_EndTriggered = false;

	Script* Duplicate() override
	{
		return KROSS_NEW PlayerMovement();
	}

	void Start() override
	{
		/* Grab All of the Local Components. */
		m_Health = GetComponent<Health>();
		m_Animator = GetComponent<Animator>();
		m_RigidBody = GetComponent<Rigidbody2D>();
		m_AudioPlayer = GetComponent<AudioPlayer>();
		m_Controller = GetComponent<PlayerController>();
		m_SpriteRenderer = GetComponent<SpriteRenderer>();

		/* Grab External Object Related things. */
		m_TextRenderer = SceneManager::GetScene()->FindObject("Text")->GetComponent<TextRenderer>();
		m_Gun = SceneManager::GetScene()->FindObject("Gun");
		m_Camera = SceneManager::GetScene()->GetCamera();

		m_HitSprite = ResourceManager::GetResource<Sprite>("Marshall-Mellow3-2");

		/* Get the Health Renderers. */
		m_HealthRenderers.push_back(SceneManager::GetScene()->FindObject("UIHealth-0")->GetComponent<SpriteRenderer>());
		m_HealthRenderers.push_back(SceneManager::GetScene()->FindObject("UIHealth-1")->GetComponent<SpriteRenderer>());
		m_HealthRenderers.push_back(SceneManager::GetScene()->FindObject("UIHealth-2")->GetComponent<SpriteRenderer>());
		m_HealthRenderers.push_back(SceneManager::GetScene()->FindObject("UIHealth-3")->GetComponent<SpriteRenderer>());
		m_HealthRenderers.push_back(SceneManager::GetScene()->FindObject("UIHealth-4")->GetComponent<SpriteRenderer>());

		m_HealthSprites.push_back(ResourceManager::GetResource<Sprite>("UI0-0"));
		m_HealthSprites.push_back(ResourceManager::GetResource<Sprite>("UI1-1"));
		m_HealthSprites.push_back(ResourceManager::GetResource<Sprite>("UI2-0"));

		m_AudioPlayers = GetComponents<AudioPlayer>();

		/* End Scene Stuff. */
		m_TopBar = SceneManager::GetScene()->FindObject("Bar-Top");
		m_BottomBar = SceneManager::GetScene()->FindObject("Bar-Bottom");

		/* Grab the Window. */
		m_Window = Application::GetWindow();

		/* See if a Controller is Connected. */
		m_ControllerID = -1; //Input::GetAvalibleController();
	}

	void Update() override
	{
		/* Create a Base Input Variable. */
		Vector2 input = Vector2(0.0f);
		Vector2 jumpDir = Vector2(0.0f);

		/* if the Controller is Connected. */
		if (Input::ControllerConnected(m_ControllerID))
		{
			/* Grab it's Input. */
			input = Vector2(Input::GetControllerAxis(m_ControllerID, Controller::LeftStickHorizontal, 0.1f), Input::GetControllerAxis(m_ControllerID, Controller::LeftStickVertical, 0.1f));
			jumpDir = Vector2(0.0f, (float)Input::GetControllerButtonPressed(m_ControllerID, Controller::A));
		}
		/* Use Keyboard and Mouse instead. */
		else
		{
			/* Keep Checking if a Controller Gets Connected. */
			m_ControllerID = Input::GetAvalibleController();

			/* Grab the Input needed. */
			input = Vector2(Input::GetAxis(Axis::KeyboardHorizontal), Input::GetAxis(Axis::KeyboardVertical));
			jumpDir = Vector2(0.0f, (float)glm::sign(Input::GetKeyPressed(Key::Space) + Input::GetKeyPressed(Key::W)));
		}
		
		/* If the Object isn't at the End of a Level. */
		if (!m_EndTriggered)
		{
			/* Move the Player. */
			VisualUpdate(input);
			m_Controller->Move(input);
			RigidbodyState rbState = m_RigidBody->GetRigidbodyState();

			if(rbState != RigidbodyState::Jumping && rbState != RigidbodyState::Falling && rbState != RigidbodyState::Underwater && jumpDir != Vector2(0.0f))
			{
				m_AudioPlayers[0]->Play();
			}
			m_Controller->Jump(jumpDir);
			
		}

		/* Lerp the Camera's Position to the Players. */
		m_Camera->m_Transform->m_Position = Math::Lerp(m_Camera->m_Transform->m_Position, m_GameObject->m_Transform->m_Position, Time::GetDeltaTime() * 4.0f);

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

		/* ----- END GAME STUFF ----- */

		if (!m_EndTriggered)
		{
			if (m_GameObject->m_Transform->m_Position.x > 154.0f && m_Health->GetHealth() > 0.0f)
			{
				m_TextRenderer->SetText("Level Cleared!");
				m_MoveCinematicBars = true;
				m_EndTriggered = true;
			}

			else if(m_Health->GetHealth() <= 0.0f)
			{
				m_TextRenderer->SetText("Game Over!");
				m_MoveCinematicBars = true;
				m_EndTriggered = true;
			}

			else if (SceneManager::GetScene()->GetName() == "Tute" && m_GameObject->m_Transform->m_Position.x > 29.9f)
			{
				m_TextRenderer->SetText("Tutorial Completed!");
				m_MoveCinematicBars = true;
				m_EndTriggered = true;
			}

			if (SceneManager::GetScene()->GetName() != "Tute")
			{
				/* Clamp the Camera Position. */
				m_Camera->m_Transform->m_Position.x = glm::clamp(m_Camera->m_Transform->m_Position.x, -1.25f, 215.75f);
				m_Camera->m_Transform->m_Position.y = glm::clamp(m_Camera->m_Transform->m_Position.y, -1.75f, 1.55f);
			}
			else
			{
				/* Clamp the Camera Position. */
				m_Camera->m_Transform->m_Position.x = glm::clamp(m_Camera->m_Transform->m_Position.x, -1.25f, 26.5f);
				m_Camera->m_Transform->m_Position.y = glm::clamp(m_Camera->m_Transform->m_Position.y, -1.75f, 1.55f);
			}
		}

		else
		{
			/* End Game Timer. */
			float t = m_EndGameTransitionTimer / m_EndGameTransitionTimerMax;
			if (m_EndGameTimer < m_EndGameTimerMax) m_EndGameTimer += Time::GetDeltaTime();
			if (m_EndGameTransitionTimer < m_EndGameTransitionTimerMax) m_EndGameTransitionTimer += Time::GetDeltaTime();

			/* Move The Bars to the Camera's Position to move. */
			if (m_MoveCinematicBars)
			{
				m_TopBar->m_Transform->m_Position = m_Camera->m_Transform->m_Position + Vector2(0.0f, 5.0f);
				m_BottomBar->m_Transform->m_Position = m_Camera->m_Transform->m_Position + Vector2(0.0f, -5.0f);
				m_MoveCinematicBars = false;
			}

			/* Zoom Camera. */
			Camera* camera = m_Camera->GetComponent<Camera>();
			camera->SetSize(Math::Lerp(camera->GetSize(), 3.0f, t));

			/* Change the Bar Colour. */
			Colour barColour = Math::Lerp(Vector4(0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), t);
			m_TopBar->m_Transform->m_Position = Math::Lerp(m_TopBar->m_Transform->m_Position, m_Camera->m_Transform->m_Position + Vector2(0.0f, 1.25f), t);
			m_BottomBar->m_Transform->m_Position = Math::Lerp(m_BottomBar->m_Transform->m_Position, m_Camera->m_Transform->m_Position + Vector2(0.0f, -1.25f), t);

			m_BottomBar->GetComponent<SpriteRenderer>()->SetColour(barColour);
			m_TopBar->GetComponent<SpriteRenderer>()->SetColour(barColour);

			/* Move Text. */
			m_TextRenderer->m_GameObject->m_Transform->m_Position = m_Camera->m_Transform->m_Position + Vector2(0.1f, 0.5f);

			/* Set Text Colour. */
			Colour textColour = Math::Lerp(m_TextRenderer->GetColour(), Vector4(1.0f), t);
			m_TextRenderer->SetColour(textColour);

			/* End Level Transition. */
			if (m_EndGameTimer >= m_EndGameTimerMax)
			{
				if (SceneManager::GetScene()->GetName() != "Tute")
				{
					leaveLevel = true;
					SceneManager::SetScene("Assets/Scenes/Menu.kscn");
				}
				else
				{
					SceneManager::SetScene("Assets/Scenes/Main.kscn");
				}
			}
		}

		/* --------------------------- */

		/* Camera Shake. */
		if (m_CameraShakeMagnitude > 0.0f)
		{
			m_Camera->m_Transform->m_Position.x += Random::GetRandomRange(-m_CameraShakeMagnitude, m_CameraShakeMagnitude);
			m_Camera->m_Transform->m_Position.y += Random::GetRandomRange(-m_CameraShakeMagnitude, m_CameraShakeMagnitude);
		}

		if (m_ShakeCamera)
		{
			m_CameraShakeMagnitude = m_CameraShakeMagnitudeMax;
			m_ShakeCoolDownTimeElapsed = 0.0f;
		}
		else
		{
			if (m_ShakeCoolDownTimeElapsed < m_ShakeCoolDownTime && m_CameraShakeMagnitude > 0.0f)
			{
				m_ShakeCoolDownTimeElapsed += Time::GetDeltaTime();
				m_CameraShakeMagnitude = m_CameraShakeMagnitudeMax * (1.0f - (m_ShakeCoolDownTime / m_ShakeCoolDownTimeElapsed));
			}

			else if (m_CameraShakeMagnitude <= 0.0f)
			{
				m_ShakeCoolDownTimeElapsed = 0.0f;
			}
		}

		/* --------- HEALTH ---------- */

		if (m_Health)
		{
			float health = m_Health->GetHealth();

			if (health >= 10.0f)		m_HealthRenderers[4]->GetMaterial()->SetDiffuse(m_HealthSprites[0]);
			else if (health >= 9.0f)	m_HealthRenderers[4]->GetMaterial()->SetDiffuse(m_HealthSprites[1]);
			else if (health <= 8.0f)	m_HealthRenderers[4]->GetMaterial()->SetDiffuse(m_HealthSprites[2]);

			if (health >= 8.0f)			m_HealthRenderers[3]->GetMaterial()->SetDiffuse(m_HealthSprites[0]);
			else if (health >= 7.0f)	m_HealthRenderers[3]->GetMaterial()->SetDiffuse(m_HealthSprites[1]);
			else if (health <= 6.0f)	m_HealthRenderers[3]->GetMaterial()->SetDiffuse(m_HealthSprites[2]);

			if (health >= 6.0f)			m_HealthRenderers[2]->GetMaterial()->SetDiffuse(m_HealthSprites[0]);
			else if (health >= 5.0f)	m_HealthRenderers[2]->GetMaterial()->SetDiffuse(m_HealthSprites[1]);
			else if (health <= 4.0f)	m_HealthRenderers[2]->GetMaterial()->SetDiffuse(m_HealthSprites[2]);

			if (health >= 4.0f)			m_HealthRenderers[1]->GetMaterial()->SetDiffuse(m_HealthSprites[0]);
			else if (health >= 3.0f)	m_HealthRenderers[1]->GetMaterial()->SetDiffuse(m_HealthSprites[1]);
			else if (health <= 2.0f)	m_HealthRenderers[1]->GetMaterial()->SetDiffuse(m_HealthSprites[2]);

			if (health >= 2.0f)			m_HealthRenderers[0]->GetMaterial()->SetDiffuse(m_HealthSprites[0]);
			else if (health >= 1.0f)	m_HealthRenderers[0]->GetMaterial()->SetDiffuse(m_HealthSprites[1]);
			else if (health <= 0.0f)	m_HealthRenderers[0]->GetMaterial()->SetDiffuse(m_HealthSprites[2]);
		}

		/* --------------------------- */

		if (!m_IsHurt)
		{
			for (b2ContactEdge* contact = m_RigidBody->GetBody()->GetContactList(); contact; contact = contact->next)
			{
				if (contact->contact->IsTouching())
				{
					Object* obj = (Object*)contact->other->GetUserData();

					if (obj == m_GameObject) continue;
					

					if (obj->GetName().find("Enemy") != std::string::npos)
					{
						if (DonutMovement* dm = obj->GetComponent<DonutMovement>())
						{
							if (!dm->dead && Physics::GetCollisionNormal(contact->contact) != Vector2(0.0f, 1.0f))
							{
								m_Health->TakeDamage(1.0f);

								Vector2 knockbackDirection = glm::normalize(m_GameObject->m_Transform->m_Position - obj->m_Transform->m_Position);
								m_RigidBody->OnApplyImpulse(knockbackDirection * 0.35f);

								m_AudioPlayers[2]->Play();
								m_IsHurt = true;
								m_VisualHurt = true;
								break;
							}
						}
					}
				}
			}
		}
		else
		{
			if (m_GracePeriodTimeElapsed >= m_GracePeriodTime * 0.25f) m_VisualHurt = false;
			if (m_GracePeriodTimeElapsed < m_GracePeriodTime) m_GracePeriodTimeElapsed += Time::GetDeltaTime();

			else
			{
				m_GracePeriodTimeElapsed = 0.0f;
				m_IsHurt = false;
			}
		}
	}

	/*! 
		Moves the Player Based on Input. 
	*/
	void VisualUpdate(Vector2 input)
	{
		/* Animation Setting.*/

		if (!m_VisualHurt)
		{
			if (!m_Animator->GetCurrentAnimation()->IsPlaying())
			{
				m_Animator->Play();
			}

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
				else if (m_RigidBody->GetBody()->GetLinearVelocity().y <= -m_VelocityThreshold)
				{
					/* Set to the Jump Down Animation. */
					m_Animator->SetCurrentAnimation(3);
				}
			}
		}
		else
		{
			m_Animator->Pause();
			m_SpriteRenderer->GetMaterial()->SetDiffuse(m_HitSprite);
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