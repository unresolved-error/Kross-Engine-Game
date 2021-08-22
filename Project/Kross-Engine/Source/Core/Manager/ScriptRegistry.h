/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "../Component/Script.h"

namespace Kross
{
	class KROSS_API ScriptRegistry
	{
	private:
		static ScriptRegistry* s_Instance;

		std::vector<Script*> m_Scripts;

		ScriptRegistry() :
			m_Scripts	(std::vector<Script*>())
		{};
		~ScriptRegistry();
	protected:
		friend class ObjectEditor;

	public:
		// Creates a Instance of Script Registry.
		static void OnCreate();

		// Destroys the Instance of Script Registry.
		static void OnDestroy();

		// Adds a Script to the Registry.
		static void Attach(Script* script);

		// Removes a Script. (NAME)
		static void Detach(std::string name);

		// Removes a Script. (INDEX)
		static void Detach(int index);

		// Removes a Script. (POINTER)
		static void Detach(Script* script);

		// Gets a Script. (NAME)
		static Script* GetScript(std::string name);

		// Gets a Script. (INDEX)
		static Script* GetScript(int index);
	};
}