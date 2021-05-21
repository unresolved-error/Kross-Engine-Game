/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Character.h"

#include "../../Manager/ResourceManager.h"

#include "../../Manager/ShaderManager.h"

namespace Kross
{
	Character::Character() : 
		p_Shader	(nullptr), 
		p_Sprite	(nullptr), 
		m_Position	(Vector2(0.0f)),
		m_Scale		(Vector2(1.0f)), 
		u_Model		(Matrix4(1.0f))
	{
		/* Grab the Text Shader. */
		p_Shader = ResourceManager::GetResource<Shader>("TextShader");
	}

	Character::~Character()
	{
		/* Remove the Shader from the Shader Manager. */
		ShaderManager::DetachShader(p_Shader);

		/* Null out Shader and Sprite. */
		p_Shader = nullptr;
		p_Sprite = nullptr;
	}

	void Character::SetPosition(Vector2 position)
	{
		m_Position = position;

		/* Create a model transform. */
		Matrix4 modelPosition = glm::translate(Matrix4(1.0f), Vector3(position, 0.0f));
		Matrix4 modelRotation = glm::rotate(Matrix4(1.0f), glm::radians(0.0f), Vector3(0.0f, 0.0f, 1.0f)); /* Set this to Zero as text isn't rotating... */
		Matrix4 modelScale = glm::scale(Matrix4(1.0f), Vector3(m_Scale, 0.0f));							  /* Atleast not now anyway. */

		/* Update the Model. */
		u_Model = modelPosition * modelRotation * modelScale;
	}

	void Character::SetScale(Vector2 scale)
	{
		m_Scale = scale;

		/* Create a model transform. */
		Matrix4 modelPosition = glm::translate(Matrix4(1.0f), Vector3(m_Position, 0.0f));
		Matrix4 modelRotation = glm::rotate(Matrix4(1.0f), glm::radians(0.0f), Vector3(0.0f, 0.0f, 1.0f)); /* Set this to Zero as text isn't rotating... */
		Matrix4 modelScale = glm::scale(Matrix4(1.0f), Vector3(scale, 0.0f));							  /* Atleast not now anyway. */

		/* Update the Model. */
		u_Model = modelPosition * modelRotation * modelScale;
	}

	void Character::SetColour(Colour colour)
	{
		/* Set the Colour Directly in the Shader. */
		p_Shader->SetUniform("u_Colour", colour);
	}

	void Character::SetSprite(Sprite* sprite)
	{
		/* Set the Sprite. */
		p_Sprite = sprite;

		/* Set Shader Values. */
		p_Shader->SetUniform("u_UVRatio", p_Sprite->GetUVRatio());
		p_Shader->SetUniform("u_UVOffset", p_Sprite->GetUVOffset());
	}

	void Character::OnRender()
	{
		/* If we have a Sprite. */
		if (p_Sprite)
		{
			/* Update the Model inside of the Shader. */
			p_Shader->SetUniform("u_Model", u_Model);

			/* Set the Texture Slot. */
			Texture* spriteTexture = p_Sprite->GetTexture();

			/* Set the Shader */
			spriteTexture->SetSlot(0);
			spriteTexture->Attach();
			p_Shader->SetUniform("u_Texture", spriteTexture);

			/* Render. */
			p_Shader->Attach();
			p_Sprite->OnRender();

			/* Un Bind all Textures. */
			Texture::Detach();
		}
	}
}