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

	//Scene* scene = Scene::OnCreate("Main");
	
	//Material* groundMaterial = ResourceManager::GetResource<Material>("Ground");
	
	//Object* camera = Object::OnCreate("Camera");
	//camera->AttachComponent<Camera>();
	//camera->GetComponent<Camera>()->SetSize(5.0f);
	
	//Object* player = Object::OnCreate("Player");
	//player->AttachComponent<SpriteRenderer>();
	//player->AttachComponent<Rigidbody2D>();
	//player->AttachComponent<PlayerMovement>();
	
	//player->AttachComponent<Animator>();
	//player->GetComponent<PlayerMovement>()->camera = camera->GetComponent<Camera>();
	
	//Animator* animator = player->GetComponent<Animator>();
	//animator->AttachAnimation(ResourceManager::GetResource<Animation>("Idle"));
	//animator->AttachAnimation(ResourceManager::GetResource<Animation>("Walk"));
	
	//player->GetTransform()->m_Position = Vector2(3.0f, -2.0f);
	//player->GetTransform()->m_Scale = Vector2(1.0f, 1.0f);
	//player->GetTransform()->m_Rotation = 0.0f;
	
	//Object* textExample = Object::OnCreate("Text");
	//textExample->AttachComponent<TextRenderer>();
	//textExample->SetLayer(Layer::UI);
	
	//TextRenderer* textRenderer = textExample->GetComponent<TextRenderer>();
	//textRenderer->SetFont(ResourceManager::GetResource<Font>(0));
	//textRenderer->SetColour(Colour(1.0f, 1.0f, 1.0f, 1.0f));
	//textRenderer->SetTextSize(1.0f);
	//textRenderer->SetText("");
	
	//Object* tileExample = Object::OnCreate("TileMap");
	//tileExample->AttachComponent<TileMapRenderer>();
	//tileExample->AttachComponent<Rigidbody2D>();
	//tileExample->SetLayer(Layer::Background);
	
	//TileMapRenderer* tilemap = tileExample->GetComponent<TileMapRenderer>();
	//tilemap->SetTileMap(ResourceManager::GetResource<TileMap>("DirtTileMap"));
	//tilemap->SetTileSet(ResourceManager::GetResource<TileSet>("DirtTileSet"));
	
	//tileExample->GetComponent<Collider>()->SetTileMapCollider(true);
	
	//scene->AttachObject(tileExample);
	
	////player->GetComponent<PlayerMovement>()->textObj = textRenderer;
	//player->SetLayer(Layer::Player);
	
	//player->AttachComponent<AudioPlayer>();
	
	//SpriteRenderer* renderer = player->GetComponent<SpriteRenderer>();
	//renderer->SetMaterial(ResourceManager::GetResource<Material>("Player"));
	
	//scene->AttachObject(player);
	
	
	//Rigidbody2D* rigidBody = player->GetComponent<Rigidbody2D>();
	//rigidBody->CreateDynamicBox(Vector2(0.25f, 0.35f), player->GetTransform()->m_Position, true, ColliderFilters::Player, ColliderFilters::Environment);
	
	//Object* particleEmitter = Object::OnCreate("Emitter");
	//particleEmitter->SetStatic(true);
	//particleEmitter->AttachComponent<ParticleEmitter>();
	//particleEmitter->GetTransform()->m_Position = Vector2(5.0f, -3.1f);
	//particleEmitter->SetLayer(Layer::Fluids);
	
	//SceneManager::GetCurrentScene()->AttachObject(particleEmitter);
	
	//ParticleEmitter* particle = particleEmitter->GetComponent<ParticleEmitter>();
	//WaterParticle* tempParticle = new WaterParticle();
	
	//tempParticle->ParticleGroup(false);
	//particle->SetColliderFilters(ColliderFilters::Fluid, ColliderFilters::Environment);
	
	//particle->SetMaxCount(0);
	//particle->SetGroupCount(1);
	
	//particle->SetPosition(particleEmitter->GetTransform()->m_Position);
	//tempParticle->SetShape(1.0f);
	
	//particle->AttachParticle(tempParticle);
	//particle->SpawnParticles();
	
	
	Object* ppEmitter = Object::OnCreate("ppEmitter");
	ppEmitter->SetStatic(true);
	ParticleProperties* properties = ppEmitter->AttachComponent<ParticleProperties>();
	ppEmitter->AttachComponent<ParticleEmitter>();
	ppEmitter->GetTransform()->m_Position = Vector2(5.0f, -5.5f);
	ppEmitter->SetLayer(Layer::Fluids);
	
	properties->AddParticleFlags(b2_waterParticle | b2_fixtureContactFilterParticle);
	properties->SetColliderFilters(ColliderFilters::Fluid, ColliderFilters::Environment | ColliderFilters::Fluid);
	properties->SetRadius(0.025f);

	SceneManager::GetCurrentScene()->AttachObject(ppEmitter);
	
	ParticleEmitter* particleEm = ppEmitter->GetComponent<ParticleEmitter>();

	
	//player->GetComponent<PlayerMovement>()->rigidBody = rigidBody;
	//
	//tileExample->SetLayer(Layer::Ground);
	//
	//scene->AttachObject(camera);
	//scene->AttachObject(textExample);
	//
	////AudioSource* MarioJump = AudioSource::OnCreate("Resources/Audio/mario_jump.wav", "Mario-Jump");
	////player->GetComponent<AudioPlayer>()->AttachSoundToPlayer(MarioJump);
	//
	////player->GetComponent<AudioPlayer>()->PlaySoundEffect(MarioJump, 1, 0, false);
	//
	//Rigidbody2D* tileMapCollider = tileExample->GetComponent<Rigidbody2D>();
	//tileMapCollider->CreateTileMapColliders(tilemap->GetTileMap(), tilemap->GetTileList()[0], 0.45f);
	//
	////AudioSource* BulletProof = AudioSource::OnCreate("Resources/Audio/bulletproof-soundroll-main-version-02-19-1873.mp3", "Bullet-Proof", true);
	////AudioSource* BulletProof = ResourceManager::GetResource<AudioSource>("Bullet-Proof");
	////player->GetComponent<AudioPlayer>()->AttachSoundToPlayer(BulletProof);
	////player->GetComponent<AudioPlayer>()->PlaySoundEffect(BulletProof,1,0,false);
	////player->GetComponent<AudioPlayer>()->SetIfLooping(true);
	//
	//SceneManager::AttachScene(scene);
	//SceneManager::SetCurrentScene(0);


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