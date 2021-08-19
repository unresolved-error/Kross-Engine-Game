#include <Kross.h>
#include "PlayerMovement.h"
#include "EnemyMovement.h"
#include "BackgroundManager.h"
#include "CameraLock.h"
#include "GunMovement.h"

using namespace Kross;

// Runs the Engine / Game.
void OnRun()
{
	Application::OnCreate();

	ScriptRegistry::OnCreate();
	ScriptRegistry::Attach(KROSS_NEW PlayerMovement());
	ScriptRegistry::Attach(KROSS_NEW EnemyMovement());
	ScriptRegistry::Attach(KROSS_NEW BackgroundManager());
	ScriptRegistry::Attach(KROSS_NEW CameraLock());
	ScriptRegistry::Attach(KROSS_NEW GunMovement());

	Application::OnStart();

	/* Create all Assets, Objects, Scenes etc. Bellow Start.*/

	Object* ppEmitter = Object::OnCreate("ppEmitter");
	ppEmitter->SetStatic(true);
	ppEmitter->AttachComponent<ParticleEmitter>();
	ppEmitter->GetTransform()->m_Position = Vector2(4.0f, -1.5f);
	ppEmitter->SetLayer(Layer::Fluids);
	
	SceneManager::GetCurrentScene()->AttachObject(ppEmitter);
	
	ParticleEmitter* particleEm = ppEmitter->GetComponent<ParticleEmitter>();
	WaterParticle* tempParticle2 = new WaterParticle();
	
	tempParticle2->ParticleGroup(false);
	particleEm->SetColliderFilters(ColliderFilters::Fluid, ColliderFilters::Environment);
	
	particleEm->SetMaxCount(700);
	particleEm->SetGroupCount(0);
	
	tempParticle2->SetColor(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	particleEm->SetPosition(ppEmitter->GetTransform()->m_Position);
	tempParticle2->SetShape(2.0f);
	
	particleEm->AttachParticle(tempParticle2);
	particleEm->SpawnParticles();
	
	Application::OnUpdate();
	Application::OnShutdown();
	Application::OnDestroy();
}

#ifndef KROSS_RELEASE

	#define _CRTBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
	int main(int argc, char** argv)
	{
		_CrtMemState* memState = KROSS_NEW _CrtMemState();
	
		OnRun();
	
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
		OnRun();
		return 0;
	}

#endif