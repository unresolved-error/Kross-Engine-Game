/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 *		- Chris Deitch
 */

#pragma once

/* --- README --- */
/*
 *  Add All API files here...
 *  Used in Game Project.
 */

#include "../Core/Application.h"
#include "../Core/Input.h"
#include "../Core/Layer.h"
#include "../Core/Object.h"
#include "../Core/Scene.h"

#include "../Core/Animation/Animation.h"
#include "../Core/Animation/Keyframe.h"

#include "../Core/Audio/AudioSource.h"

#include "../Core/Component/Component.h"

#include "../Core/File-IO/FileSystem.h"

#include "../Core/Manager/ResourceManager.h"
#include "../Core/Manager/SceneManager.h"
#include "../Core/Manager/ShaderManager.h"
#include "../Core/Manager/Time.h"
#include "../Core/Manager/AudioManager.h"

#include "../Core/Math/Math.h"
#include "../Core/Math/Random.h"

#include "../Core/Physics/Physics.h"
#include "../Core/Physics/PhysicsScene.h"

#include "../Core/Physics/Collision/ContactFilter.h"
#include "../Core/Physics/Collision/Raycast2DCallback.h"
#include "../Core/Physics/Data/CollisionData.h"

#include "../Core/Physics/Particles/Particle.h"

#include "../Core/Physics/Shape/Box.h"
#include "../Core/Physics/Shape/Circle.h"
#include "../Core/Physics/Shape/Plane.h"
#include "../Core/Physics/Shape/Shape.h"

#include "../Core/Renderer/FrameBuffer.h"
#include "../Core/Renderer/Geometry.h"
#include "../Core/Renderer/IndexBuffer.h"
#include "../Core/Renderer/Material.h"
#include "../Core/Renderer/VertexArray.h"
#include "../Core/Renderer/VertexBuffer.h"

#include "../Core/Renderer/Batch/Batch.h"
#include "../Core/Renderer/Batch/BatchRenderer.h"

#include "../Core/Renderer/Image/Atlas.h"
#include "../Core/Renderer/Image/Sprite.h"
#include "../Core/Renderer/Image/Texture.h"
#include "../Core/Renderer/Image/TextureType.h"

#include "../Core/Renderer/Shader/Shader.h"
#include "../Core/Renderer/Shader/ShaderFlags.h"

#include "../Core/Renderer/Text/Character.h"
#include "../Core/Renderer/Text/Font.h"
#include "../Core/Renderer/Text/TextAlignment.h"

#include "../Core/Renderer/Tilemap/Tile.h"
#include "../Core/Renderer/Tilemap/TileMap.h"
#include "../Core/Renderer/Tilemap/TileSet.h"

#include "../Core/Renderer/Vertex/Vertex.h"

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

Kross::Object* Kross::OnCreateObject(Kross::Object* object)
{
	/* Attach it to the Current Scene. */
	Kross::SceneManager::GetCurrentScene()->AttachObject(object);

	/* Return the Object. */
	return object;
};