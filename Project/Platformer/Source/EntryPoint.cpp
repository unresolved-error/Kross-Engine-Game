#define _CRTBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <Kross.h>
#include "PlayerMovement.h"

using namespace Kross;

int main(int argc, char** argv)
{
	_CrtMemState* memState = KROSS_NEW _CrtMemState();

	Application::OnCreate();
	Application::OnStart();

	/* Create all Assets, Objects, Scenes etc. Bellow Start.*/

	Scene* scene = Scene::OnCreate("Main");

	Material* groundMaterial = ResourceManager::GetResource<Material>("Ground");

	Object* camera = Object::OnCreate("Camera");
	camera->AttachComponent<Camera>();
	camera->GetComponent<Camera>()->SetSize(5.0f);

	Object* player = Object::OnCreate("Player");
	player->AttachComponent<SpriteRenderer>();
	player->AttachComponent<Rigidbody2D>();
	player->AttachComponent<PlayerMovement>();
	player->AttachComponent<Animator>();
	player->GetComponent<PlayerMovement>()->camera = camera->GetComponent<Camera>();

	Animator* animator = player->GetComponent<Animator>();
	animator->AttachAnimation(ResourceManager::GetResource<Animation>("Idle"));
	animator->AttachAnimation(ResourceManager::GetResource<Animation>("Walk"));

	Object* textExample = Object::OnCreate("Text");
	textExample->AttachComponent<TextRenderer>();
	textExample->SetLayer(Layer::UI);

	TextRenderer* textRenderer = textExample->GetComponent<TextRenderer>();
	textRenderer->SetFont(ResourceManager::GetResource<Font>(0));
	textRenderer->SetColour(Colour(1.0f, 1.0f, 1.0f, 1.0f));
	textRenderer->SetTextSize(1.0f);
	textRenderer->SetText("Huh? TileMaps!?");

	Object* tileExample = Object::OnCreate("TileMap");
	tileExample->AttachComponent<TileMapRenderer>();
	tileExample->SetLayer(Layer::Background);

	TileMapRenderer* tilemap = tileExample->GetComponent<TileMapRenderer>();
	tilemap->SetTileMap(ResourceManager::GetResource<TileMap>("DirtTileMap"));
	tilemap->SetTileSet(ResourceManager::GetResource<TileSet>("DirtTileSet"));

	scene->AttachObject(tileExample);

	Object* tileExample1 = Object::OnCreate("TileMap");
	tileExample1->GetTransform()->m_Position.x += 1.0f;
	tileExample1->AttachComponent<TileMapRenderer>();
	tileExample1->SetLayer(Layer::Background);

	TileMapRenderer* tilemap1 = tileExample1->GetComponent<TileMapRenderer>();
	tilemap1->SetTileMap(ResourceManager::GetResource<TileMap>("DirtTileMap"));
	tilemap1->SetTileSet(ResourceManager::GetResource<TileSet>("DirtTileSet"));

	scene->AttachObject(tileExample1);

	Object* tileExample2 = Object::OnCreate("TileMap");
	tileExample2->GetTransform()->m_Position.x += 2.0f;
	tileExample2->AttachComponent<TileMapRenderer>();
	tileExample2->SetLayer(Layer::Background);

	TileMapRenderer* tilemap2 = tileExample2->GetComponent<TileMapRenderer>();
	tilemap2->SetTileMap(ResourceManager::GetResource<TileMap>("DirtTileMap"));
	tilemap2->SetTileSet(ResourceManager::GetResource<TileSet>("DirtTileSet"));

	scene->AttachObject(tileExample2);
	
	player->GetComponent<PlayerMovement>()->textObj = textRenderer;
	player->SetLayer(Layer::Background);

	player->AttachComponent<AudioPlayer>();
	
	SpriteRenderer* renderer = player->GetComponent<SpriteRenderer>();
	renderer->SetMaterial(ResourceManager::GetResource<Material>("Player"));

	scene->AttachObject(player);


	Rigidbody2D* rigidBody = player->GetComponent<Rigidbody2D>();
	rigidBody->CreateDynamicBox(Vector2(0.25f, 0.33f), player->GetTransform()->m_Position, true, ColliderFilters::Player, ColliderFilters::Environment);
	//rigidBody->SetMass(1.25f);


	//Object* particleEmitter = Object::OnCreate("Emitter");
	//particleEmitter->SetStaticStatus(true);
	//particleEmitter->AttachComponent<ParticleEmitter>();
	//particleEmitter->GetTransform()->m_Position = Vector2(0.0f, 0.0f);
	//particleEmitter->SetLayer(Layer::Fluids);
	//
	//scene->AttachObject(particleEmitter);
	//
	//ParticleEmitter* particle = particleEmitter->GetComponent<ParticleEmitter>();
	//particle->SetParticleType(ParticleType::ParticleGroup);
	//particle->SetColliderFilters(ColliderFilters::Fluid, ColliderFilters::Environment);
	//
	//particle->GetParticle()->AddParticleFlag(b2_waterParticle | b2_fixtureContactFilterParticle);
	//particle->GetParticle()->AddParticleGroupFlag(b2_solidParticleGroup);
	//particle->GetParticle()->SetShape(1.5f);
	////particle->GetParticle()->SetColor({ 0.0f, 100.0f, 207.0f, 255.0f });
	////particle->GetParticle()->SetPosition(Vector2(particleEmitter->GetTransform()->m_Position.x, particleEmitter->GetTransform()->m_Position.y));
	//particle->SetMaxCount(0);
	//particle->SetGroupCount(1);

	player->GetComponent<PlayerMovement>()->rigidBody = rigidBody;

	scene->AttachObject(camera);
	scene->AttachObject(textExample);
	
	//AudioSource* MarioJump = AudioSource::OnCreate("Resources/Audio/mario_jump.wav", "Mario-Jump");
	//player->GetComponent<AudioPlayer>()->AttachSoundToPlayer(MarioJump);
	//
	//player->GetComponent<AudioPlayer>()->PlaySoundEffect(MarioJump, 1, 0, false);
	


	//AudioSource* BulletProof = AudioSource::OnCreate("Resources/Audio/bulletproof-soundroll-main-version-02-19-1873.mp3", "Bullet-Proof", true);
	AudioSource* BulletProof = ResourceManager::GetResource<AudioSource>("Bullet-Proof");
	player->GetComponent<AudioPlayer>()->AttachSoundToPlayer(BulletProof);
	player->GetComponent<AudioPlayer>()->PlaySoundEffect(BulletProof,1,0,false);
	player->GetComponent<AudioPlayer>()->SetIfLooping(true);

	SceneManager::AttachScene(scene);
	SceneManager::SetCurrentScene(0);


	Application::OnUpdate();
	Application::OnShutdown();
	Application::OnDestroy();

	_CrtMemCheckpoint(memState);
	_CrtMemDumpStatistics(memState);

	delete memState;
	_CrtDumpMemoryLeaks();
	

	return 0;
}