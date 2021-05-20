/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

namespace Kross
{
	struct KROSS_API WindowProperties
	{
	private:
		bool m_ChangedWindowMode;
		int m_Width, m_Height, m_VSync, m_Fullscreen;
		std::string m_Title;

	protected:

	public:
		WindowProperties() : 
			m_ChangedWindowMode	(true),
			m_Title				(""),
			m_Width				(0), 
			m_Height			(0),
			m_VSync				(1), 
			m_Fullscreen		(0)
		{};

		// Get the Title Property.
		const std::string& GetTitle() const { return m_Title; };

		// Get the Width Property.
		const int GetWidth() const { return m_Width; };

		// Get the Height Property.
		const int GetHeight() const { return m_Height; };

		// Get the VSync value Property.
		const int GetVSync() const { return m_VSync; };

		// Get the Fullscreen Mode Property.
		const int GetFullscreen() const { return m_Fullscreen; };

		// Gets the Fullscreen Window Mode Check.
		const bool GetChangedWindowModeStatus() const { return m_ChangedWindowMode; };

		// Set the Title Property.
		void SetTitle(const std::string& title) { m_Title = title; };

		// Set the Width Property.
		void SetWidth(int width) { m_Width = width; };

		// Set The Height Property.
		void SetHeight(int height) { m_Height = height; };

		// Turn on or off VSync.
		void SetVSync(int vSync) { m_VSync = ((vSync > 1) ? 1 : ((vSync < 0) ? 0 : vSync)); }; // This ternary clamps the vSync value from 1 to 0.

		// Turn on or off Fullscreen Mode.
		void SetFullscreen(int fullscreen) 
		{ 
			if (m_Fullscreen != fullscreen) 
			{
				m_Fullscreen = ((fullscreen > 1) ? 1 : ((fullscreen < 0) ? 0 : fullscreen)); // This ternary clamps the fullscreen value from 1 to 0.
				m_ChangedWindowMode = false;
			}
		};

		// Resets the Window Mode Status (USE CAREFULLY)
		void SetChangedWindowModeStatusDefault() { m_ChangedWindowMode = true; };
	};
}