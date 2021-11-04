#include <Kross.h>
#include "PlayerMovement.h"
#include "DonutMovement.h"
#include "BackgroundManager.h"
#include "CameraLock.h"
#include "GunMovement.h"
#include "Button.h"
#include "DoorFunny.h"
#include "HealthManager.h"
#include "TriggerLaser.h"
#include "EnvironmentalDamage.h"
#include "Start-Button.h"
#include "Exit-Button.h"

using namespace Kross;

void AttachScripts()
{
	ScriptRegistry::OnCreate();
	ScriptRegistry::Attach(KROSS_NEW Health());
	ScriptRegistry::Attach(KROSS_NEW Button());
	ScriptRegistry::Attach(KROSS_NEW DoorFunny());
	ScriptRegistry::Attach(KROSS_NEW CameraLock());
	ScriptRegistry::Attach(KROSS_NEW GunMovement());
	ScriptRegistry::Attach(KROSS_NEW DonutMovement());
	ScriptRegistry::Attach(KROSS_NEW HealthManager());
	ScriptRegistry::Attach(KROSS_NEW PlayerMovement());
	ScriptRegistry::Attach(KROSS_NEW BackgroundManager());
	ScriptRegistry::Attach(KROSS_NEW EnvironmentalDamage());   //REMOVED TO PREVENT INSTANT DEATH AT THE MOMENT.
	ScriptRegistry::Attach(KROSS_NEW TriggerLaser());
	ScriptRegistry::Attach(KROSS_NEW StartButton());
	ScriptRegistry::Attach(KROSS_NEW ExitButton());
}

#ifndef KROSS_RELEASE

	#define _CRTBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
	int main(int argc, char** argv)
	{
		MemoryState* memState = KROSS_NEW MemoryState();
		#ifdef KROSS_EDITOR
		Application::OnCreate("Kross Engine Editor");
		#else
		Application::OnCreate("Sweet Dreams of Destruction");
		#endif
		AttachScripts();

		Application::OnStart();

		Application::OnUpdate();
		Application::OnShutdown();
		Application::OnDestroy();
	
		_CrtMemCheckpoint(memState);
		_CrtMemDumpStatistics(memState);
	
		delete memState;
		_CrtDumpMemoryLeaks();
		
		return 0;
	}

#else
	#include <Windows.h>
	
	/* Run the program without the Debugging Console. */
	int WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show)	{
		Application::OnCreate("Sweet Dreams of Destruction");

		AttachScripts();

		Application::OnStart();

		Application::OnUpdate();
		Application::OnShutdown();
		Application::OnDestroy();
		return 0;
	}

#endif