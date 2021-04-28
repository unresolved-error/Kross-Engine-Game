/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

/* --- README --- */
/*
 *  Add All API files here...
 *  Used in Game Project.
 */

#include "../Core/Application.h"
#include "../Core/FileSystem.h"
#include "../Core/Input.h"
#include "../Core/Object.h"
#include "../Core/Scene.h"

#include "../Core/Component/Component.h"

#include "../Core/Manager/ResourceManager.h"
#include "../Core/Manager/SceneManager.h"
#include "../Core/Manager/ShaderManager.h"

#include "../Core/Math/Math.h"
#include "../Core/Math/Random.h"

#include "../Core/Renderer/FrameBuffer.h"
#include "../Core/Renderer/Geometry.h"
#include "../Core/Renderer/IndexBuffer.h"
#include "../Core/Renderer/VertexArray.h"
#include "../Core/Renderer/VertexBuffer.h"

#include "../Core/Renderer/Image/Sprite.h"
#include "../Core/Renderer/Image/Texture.h"

#include "../Core/Renderer/Shader/Shader.h"

#include "../Core/Renderer/Text/Character.h"
#include "../Core/Renderer/Text/Font.h"
#include "../Core/Renderer/Text/Text.h"

#include "../Core/Window/Window.h"
#include "../Core/Window/WindowProperties.h"

Kross::Object* Kross::OnCreateObject(const std::string& name)
{
	/* Create an Empty Object with a name. */
	Kross::Object* object = Kross::Object::OnCreate(name);

	/* Attach it to the Current Scene. */
	Kross::SceneManager::GetCurrentScene()->AttachObject(object);

	/* Retutn the Object. */
	return object;
};

Kross::Object* Kross::OnCreateObject(const std::string& name, Kross::Vector2 position)
{
	/* Create an Empty Object with a name. */
	Kross::Object* object = Kross::Object::OnCreate(name);
	object->GetTransform()->m_Position = position;

	/* Attach it to the Current Scene. */
	Kross::SceneManager::GetCurrentScene()->AttachObject(object);

	/* Retutn the Object. */
	return object;
};

Kross::Object* Kross::OnCreateObject(const std::string& name, Kross::Vector2 position, float rotation)
{
	/* Create an Empty Object with a name. */
	Kross::Object* object = Kross::Object::OnCreate(name);
	object->GetTransform()->m_Position = position;
	object->GetTransform()->m_Rotation = rotation;

	/* Attach it to the Current Scene. */
	Kross::SceneManager::GetCurrentScene()->AttachObject(object);

	/* Retutn the Object. */
	return object;
};

Kross::Object* Kross::OnCreateObject(const std::string& name, Kross::Vector2 position, float rotation, Kross::Vector2 scale)
{
	/* Create an Empty Object with a name. */
	Kross::Object* object = Kross::Object::OnCreate(name);
	object->GetTransform()->m_Position = position;
	object->GetTransform()->m_Rotation = rotation;
	object->GetTransform()->m_Scale = scale;

	/* Attach it to the Current Scene. */
	Kross::SceneManager::GetCurrentScene()->AttachObject(object);

	/* Retutn the Object. */
	return object;
};