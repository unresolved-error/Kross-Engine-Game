/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 *		- Chris Deitch.
 */

#pragma once

#include "../../Core.h"

#include "../Serialiser.h"
#include "../../Manager/ScriptRegistry.h"

namespace Kross
{
	template<>
	class KROSS_API Serialiser<Object>
	{
		Object* Load(std::vector<std::string> source)
		{
			/* Object to Return. */
			Object* newObject = Object::OnCreate();

			/* Go through the Objects Source. */
			for (int i = 0; i < source.size(); i++)
			{
				/* Temp Variable. */
				std::string line = source[i];

				/* Quick Variables. */
				size_t searchPosition = 0;
				std::string objectProperty;
				std::string lineSplitter = "->";

				/* Keep Searching till we reach the end of the Line.*/
				//while ((searchPosition = line.find(lineSplitter)) != std::string::npos)
				//{
				//	/* Extract the Data Once. */
				//	std::string extractedData = line.substr(0, searchPosition);
				//
				//	/* Grab the Property Type. */
				//	if (objectProperty.empty()) 
				//	{
				//		objectProperty = extractedData;
				//	}
				//
				//	/* Grab the Property Value. */
				//	else
				//	{
				//		
				//		/* Name Property. */
				//		if (objectProperty == "NAME")
				//		{
				//			newObject->SetName(extractedData);
				//		}
				//
				//		/* Static Property. */
				//		else if (objectProperty == "STATIC")
				//		{
				//			newObject->SetStatic((bool)std::stoi(extractedData));
				//		}
				//
				//		/* Enable Property. */
				//		else if (objectProperty == "ENABLE")
				//		{
				//			newObject->SetEnable((bool)std::stoi(extractedData));
				//		}
				//
				//		/* Layer Property. */
				//		else if (objectProperty == "LAYER")
				//		{
				//			newObject->SetLayer((Layer)std::stoi(extractedData));
				//		}
				//
				//		/* Transform Component Property. */
				//		else if (objectProperty == "TRANSFORM2D")
				//		{
				//			
				//		}
				//
				//		/* Animator Component Property. */
				//		else if (objectProperty == "ANIMATOR")
				//		{
				//			currentObject->AttachComponent<Animator>();
				//			animatorData.push_back(line);
				//		}
				//
				//		/* Audio Player Component Property. */
				//		else if (objectProperty == "AUDIO-PLAYER")
				//		{
				//			currentObject->AttachComponent<AudioPlayer>();
				//			audioPlayerData.push_back(line);
				//		}
				//
				//		/* Camera Component Property. */
				//		else if (objectProperty == "CAMERA")
				//		{
				//			currentObject->AttachComponent<Camera>();
				//			cameraData.push_back(line);
				//		}
				//
				//		/* Rigidbody 2D Component Property. */
				//		else if (objectProperty == "RIGIDBODY2D")
				//		{
				//			currentObject->AttachComponent<Rigidbody2D>();
				//			rigidbodyData.push_back(line);
				//		}
				//
				//		/* Sprite Renderer Component Property. */
				//		else if (objectProperty == "SPRITE-RENDERER")
				//		{
				//			currentObject->AttachComponent<SpriteRenderer>();
				//			spriteRendererData.push_back(line);
				//		}
				//
				//		/* Text Renderer Component Property. */
				//		else if (objectProperty == "TEXT-RENDERER")
				//		{
				//			currentObject->AttachComponent<TextRenderer>();
				//			textRendererData.push_back(line);
				//		}
				//
				//		/* Tile Map Renderer Component Property. */
				//		else if (objectProperty == "TILEMAP-RENDERER")
				//		{
				//			currentObject->AttachComponent<TileMapRenderer>();
				//			tileMapRendererData.push_back(line);
				//		}
				//
				//		/* Particle Emitter Component Property. */
				//		else if (objectProperty == "EMITTER")
				//		{
				//			currentObject->AttachComponent<ParticleEmitter>();
				//			//currentObject->AttachComponent<ParticleProperties>();
				//			particleEmitterData.push_back(line);
				//		}
				//
				//		else if (objectProperty == "SCRIPT")
				//		{
				//			Script* script = ScriptRegistry::GetScript(line.substr(0, line.size() - 2));
				//			script->m_GameObject = currentObject;
				//			currentObject->m_Components.push_back(script);
				//			Debug::LogLine(script->GetName() + " - Script was attached!");
				//		}
				//
				//		else if (objProperty == "PLAYER-CONTROLLER")
				//		{
				//			currentObject->AttachComponent<PlayerController>();
				//			playerControllerData.push_back(line);
				//		}
				//
				//	}
				//
				//	/* Erase parts of the line to not double up on data search. */
				//	line.erase(0, searchPosition + lineSplitter.length());
				//}
			}
		}
	};
}