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
			if (s_Instance->m_Scripts[i]->GetName() == name)
			{
				delete s_Instance->m_Scripts[i];
				s_Instance->m_Scripts.erase(s_Instance->m_Scripts.begin() + i);
			}
		}
	}
	void ScriptRegistry::Detach(int index)
	{
		if (index < 0 && index >= s_Instance->m_Scripts.size())
			return;

		delete s_Instance->m_Scripts[index];
		s_Instance->m_Scripts.erase(s_Instance->m_Scripts.begin() + index);
	}
	void ScriptRegistry::Detach(Script* script)
	{
		for (int i = 0; i < s_Instance->m_Scripts.size(); i++)
		{
			if (s_Instance->m_Scripts[i] == script)
			{
				delete s_Instance->m_Scripts[i];
				s_Instance->m_Scripts.erase(s_Instance->m_Scripts.begin() + i);
			}
		}
	}

	Script* ScriptRegistry::GetScript(std::string name)
	{
		for (int i = 0; i < s_Instance->m_Scripts.size(); i++)
		{
			if (s_Instance->m_Scripts[i]->GetName() == name)
			{
				//return KROSS_NEW Script(*s_Instance->m_Scripts[i]);
				return s_Instance->m_Scripts[i]->Duplicate();
			}
		}

		return nullptr;
	}
	Script* ScriptRegistry::GetScript(int index)
	{
		if(index < 0 && index >= s_Instance->m_Scripts.size())
			return nullptr;

		return s_Instance->m_Scripts[index]->Duplicate();
	}
}