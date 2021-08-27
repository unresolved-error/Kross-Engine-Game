/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "ScriptRegistry.h"

namespace Kross
{
	ScriptRegistry* ScriptRegistry::m_Instance = nullptr;

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
		if (!m_Instance)
			m_Instance = KROSS_NEW ScriptRegistry();
	}
	void ScriptRegistry::OnDestroy()
	{
		if (m_Instance)
			delete m_Instance;
	}

	void ScriptRegistry::Attach(Script* script)
	{
		m_Instance->m_Scripts.push_back(script);
	}
	void ScriptRegistry::Detach(std::string name)
	{
		for (int i = 0; i < m_Instance->m_Scripts.size(); i++)
		{
			if (m_Instance->m_Scripts[i]->GetName() == name)
			{
				delete m_Instance->m_Scripts[i];
				m_Instance->m_Scripts.erase(m_Instance->m_Scripts.begin() + i);
			}
		}
	}
	void ScriptRegistry::Detach(int index)
	{
		if (index < 0 && index >= m_Instance->m_Scripts.size())
			return;

		delete m_Instance->m_Scripts[index];
		m_Instance->m_Scripts.erase(m_Instance->m_Scripts.begin() + index);
	}
	void ScriptRegistry::Detach(Script* script)
	{
		for (int i = 0; i < m_Instance->m_Scripts.size(); i++)
		{
			if (m_Instance->m_Scripts[i] == script)
			{
				delete m_Instance->m_Scripts[i];
				m_Instance->m_Scripts.erase(m_Instance->m_Scripts.begin() + i);
			}
		}
	}

	Script* ScriptRegistry::GetScript(std::string name)
	{
		for (int i = 0; i < m_Instance->m_Scripts.size(); i++)
		{
			if (m_Instance->m_Scripts[i]->GetName() == name)
			{
				return m_Instance->m_Scripts[i]->Duplicate();
			}
		}

		return nullptr;
	}
	Script* ScriptRegistry::GetScript(int index)
	{
		if(index < 0 && index >= m_Instance->m_Scripts.size())
			return nullptr;

		return m_Instance->m_Scripts[index]->Duplicate();
	}
}