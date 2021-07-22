#include "ObjectEditor.h"

namespace Kross {

	void ObjectEditor::Attach()
	{
		
	}

	void ObjectEditor::SetFlags()
	{
		m_WindowFlags = ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize;
	}

	void ObjectEditor::OnStart()
	{
		SetFlags();
		m_Title = "object editor panel";

	}
}