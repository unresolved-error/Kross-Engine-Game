#include <Kross.h>
#include "PlayerMovement.h"
#include "EnemyMovement.h"
#include "BackgroundManager.h"
#include "CameraLock.h"
#include "GunMovement.h"


using namespace Kross;

void AttachScripts()
{
	ScriptRegistry::OnCreate();
	ScriptRegistry::Attach(KROSS_NEW PlayerMovement());
	ScriptRegistry::Attach(KROSS_NEW EnemyMovement());
	ScriptRegistry::Attach(KROSS_NEW BackgroundManager());
	ScriptRegistry::Attach(KROSS_NEW CameraLock());
	ScriptRegistry::Attach(KROSS_NEW GunMovement());
}

#ifndef KROSS_RELEASE

	#define _CRTBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
	int main(int argc, char** argv)
	{
		MemoryState* memState = KROSS_NEW MemoryState();
	
		Application::OnCreate();
		
		AttachScripts();

		Application::OnStart();

		Object* rope = Object::OnCreate();

		RopeProperties* properties = rope->AttachComponent<RopeProperties>();
		std::vector<Vector2> positions;
		positions.push_back(Vector2(1, 1));
		positions.push_back(Vector2(5, 5));
		properties->SetLinkSize(1.0f);

		
		properties->SetPositions(positions);
		Rope* theActualRope = Rope::CreateRope(properties, properties->GetPhysicsScene());



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
	int WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show)
	{
		Application::OnCreate();

		AttachScripts();

		Application::OnStart();

		Application::OnUpdate();
		Application::OnShutdown();
		Application::OnDestroy();
		return 0;
	}

#endif