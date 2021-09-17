/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *		- Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

#include "../../Object.h"

namespace Kross
{
	template<typename T>
	class KROSS_API Folder {};

	template<>
	class KROSS_API Folder<Object>
	{
	private:
		std::string m_Name;
		std::vector<Object*> m_Contents;

	protected:
		friend class SceneHierarchy;
		template<typename Type> friend class Serialiser;

	public:
		Folder() :
			m_Name		("New Folder"),
			m_Contents	(std::vector<Object*>())
		{};
		const std::string GetName() const { return m_Name; };
		void SetName(const std::string& name) { m_Name = name; };

		void Push(Object* object)
		{
			for (int i = 0; i < m_Contents.size(); i++)
			{
				if (m_Contents[i] == object)
					return;
			}

			m_Contents.push_back(object);
		}

		void Erase(Object* object)
		{
			for (int i = 0; i < m_Contents.size(); i++)
			{
				if (m_Contents[i] == object)
				{
					m_Contents[i] = nullptr;
					m_Contents.erase(m_Contents.begin() + i);

					return;
				}
			}
		}

		void Erase(int index)
		{
			if (index < 0 || index >= m_Contents.size())
				return;

			m_Contents[index] = nullptr;
			m_Contents.erase(m_Contents.begin() + index);
		}
	};
}