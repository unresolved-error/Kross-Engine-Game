/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "ScriptRegistry.h"

namespace Kross
{
	ScriptRegistry* ScriptRegistry::s_Instance = nullptr;

	ScriptRegistry::~ScriptRegistry()
	{
		for (int i = 0; i < m_Scripts.size(); i++)
		{
			delete m_Scripts[i];
			m_Scripts[i] = nullptr;
		}

		m_Scripts.clear();
	}

	void ScriptRegistry::OnCreate()
	{
		if (!s_Instance)
			s_Instance = KROSS_NEW ScriptRegistry();
	}
	void ScriptRegistry::OnDestroy()
	{
		if (s_Instance)
			delete s_Instance;
	}

	void ScriptRegistry::Attach(Script* script)
	{
		s_Instance->m_Scripts.push_back(script);
	}
	void ScriptRegistry::Detach(std::string name)
	{
		for (int i = 0; i < s_Instance->m_Scripts.size(); i++)
		{
			if (typeid(*s_Instance->m_Scripts[i]).name() == name)
			{

			}
		}
	}
	void ScriptRegistry::Detach(int index)
	{
	}
	void ScriptRegistry::Detach(Script* script)
	{
	}
	Script* ScriptRegistry::GetScript(std::string name)
	{
		return nullptr;
	}
	Script* ScriptRegistry::GetScript(int index)
	{
		return nullptr;
	}
}