#pragma once

#include "../Core.h"

namespace Kross
{
	struct KROSS_API WindowProperties
	{
	private:
		int m_Width, m_Height, m_VSync;
		std::string m_Title;

	protected:

	public:
		WindowProperties()
			: m_Width(0), m_Height(0), m_VSync(0), m_Title("")
		{};

		// Get the Title Property.
		const std::string& GetTitle() const { return m_Title; };

		// Get the Width Property.
		const int GetWidth() const { return m_Width; };

		// Get the Height Property.
		const int GetHeight() const { return m_Height; };

		// Get the VSync value Property.
		const int GetVSync() const { return m_VSync; };

		// Set the Title Property.
		void SetTitle(const std::string& title) { m_Title = title; };

		// Set the Width Property.
		void SetWidth(int width) { m_Width = width; };

		// Set The Height Property.
		void SetHeight(int height) { m_Height = height; };

		// Turn on or off VSync.
		void SetVSync(int vSync) { m_VSync = ((vSync > 1) ? 1 : ((vSync < 0) ? 0 : vSync)); }; // This ternary clamps the vSync value from 1 to 0.
	};
}