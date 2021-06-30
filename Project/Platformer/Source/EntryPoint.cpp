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
	
	player->GetTransform()->m_Position = Vector2(0.0f, 0.0f);
	player->GetTransform()->m_Scale = Vector2(1.0f, 1.0f);
	player->GetTransform()->m_Rotation = 0.0f;

	Object* textExample = Object::OnCreate("Text");
	textExample->AttachComponent<TextRenderer>();
	textExample->SetLayer(Layer::UI);

	TextRenderer* textRenderer = textExample->GetComponent<TextRenderer>();
	textRenderer->SetFont(ResourceManager::GetResource<Font>(0));
	textRenderer->SetColour(Colour(1.0f, 1.0f, 1.0f, 1.0f));
	textRenderer->SetTextSize(1.0f);
	textRenderer->SetText("What? I Can Walk?!");
	
	player->GetComponent<PlayerMovement>()->textObj = textRenderer;
	player->SetLayer(Layer::Background);

	player->AttachComponent<AudioPlayer>();
	
	SpriteRenderer* renderer = player->GetComponent<SpriteRenderer>();
	renderer->SetMaterial(ResourceManager::GetResource<Material>("Player"));

	scene->AttachObject(player);

	Object* platforms[12];
	for (int i = 0; i < 12; i++)
	{
		Object* platform = Object::OnCreate("Platform");
		platform->SetStaticStatus(true);
		platform->AttachComponent<SpriteRenderer>();
		platform->GetTransform()->m_Position = Vector2(-((12.0f * 0.5f) / 2.0f) + 0.25f, -2.75f) + Vector2(i * 0.5f, 0.0f);
		platform->SetLayer(Layer::Ground);
		scene->AttachObject(platform);
	
		platforms[i] = platform;
	}
	for (int i = 0; i < 12; i++)
	{
		SpriteRenderer* renderer = platforms[i]->GetComponent<SpriteRenderer>();
		renderer->SetMaterial(groundMaterial);
	}

	Object* platformCollider = Object::OnCreate("Platform Collider");
	platformCollider->SetStaticStatus(true);
	platformCollider->AttachComponent<Rigidbody2D>();
	platformCollider->GetTransform()->m_Position = Vector2(0.0f, -2.75f);
	platformCollider->SetLayer(Layer::Ground);
	scene->AttachObject(platformCollider);

	Rigidbody2D* pcrb = platformCollider->GetComponent<Rigidbody2D>();
	pcrb->CreateWorldBox(Vector2(6.0f, 0.5f), platformCollider->GetTransform()->m_Position, ColliderFilters::Environment, ColliderFilters::Player | ColliderFilters::Fluid);

	Object* grounds[31];
	for (int i = 0; i < 31; i++)
	{
		Object* ground = Object::OnCreate("Ground");
		ground->SetStaticStatus(true);
		ground->AttachComponent<SpriteRenderer>();
		ground->AttachComponent<Rigidbody2D>();
		ground->GetTransform()->m_Position = Vector2(-7.5f, -4.0f) + Vector2(i * 0.5f, 0.0f);
		ground->SetLayer(Layer::Ground);
		scene->AttachObject(ground);

		grounds[i] = ground;
	}
	for (int i = 0; i < 31; i++)
	{
		Rigidbody2D* grb = grounds[i]->GetComponent<Rigidbody2D>();
		grb->CreateWorldBox(Vector2(0.5f, 0.5f), grounds[i]->GetTransform()->m_Position, ColliderFilters::Environment, ColliderFilters::Player | ColliderFilters::Fluid);

		SpriteRenderer* renderer = grounds[i]->GetComponent<SpriteRenderer>();
		renderer->SetMaterial(groundMaterial);
	}


	Object* roofs[31];
	for (int i = 0; i < 31; i++)
	{
		Object* roof = Object::OnCreate("Roof");
		roof->SetStaticStatus(true);
		roof->AttachComponent<SpriteRenderer>();
		roof->AttachComponent<Rigidbody2D>();
		roof->GetTransform()->m_Position = Vector2(-7.5f, 4.0f) + Vector2(i * 0.5f, 0.0f);
		roof->SetLayer(Layer::Default);
		scene->AttachObject(roof);

		roofs[i] = roof;
	}
	for (int i = 0; i < 31; i++)
	{
		Rigidbody2D* rrb = roofs[i]->GetComponent<Rigidbody2D>();
		rrb->CreateWorldBox(Vector2(0.5f, 0.5f), roofs[i]->GetTransform()->m_Position, ColliderFilters::Environment, ColliderFilters::Player | ColliderFilters::Fluid);

		SpriteRenderer* renderer = roofs[i]->GetComponent<SpriteRenderer>();
		renderer->SetMaterial(groundMaterial);
	}


	Object* rightWalls[17];
	for (int i = 0; i < 17; i++)
	{
		Object* rightWall = Object::OnCreate("RightWall");
		rightWall->SetStaticStatus(true);
		rightWall->AttachComponent<SpriteRenderer>();
		rightWall->AttachComponent<Rigidbody2D>();
		rightWall->GetTransform()->m_Position = Vector2(8.0f, -4.0f) + Vector2(0.0f, i * 0.5f);
		rightWall->SetLayer(Layer::Wall);
		scene->AttachObject(rightWall);

		rightWalls[i] = rightWall;
	}
	for (int i = 0; i < 17; i++)
	{
		Rigidbody2D* rwrb = rightWalls[i]->GetComponent<Rigidbody2D>();
		rwrb->CreateWorldBox(Vector2(0.5f, 0.5f), 0.0f, rightWalls[i]->GetTransform()->m_Position, ColliderFilters::Environment, ColliderFilters::Player | ColliderFilters::Fluid);

		SpriteRenderer* renderer = rightWalls[i]->GetComponent<SpriteRenderer>();
		renderer->SetMaterial(groundMaterial);
	}


	Object* leftWalls[17];
	for (int i = 0; i < 17; i++)
	{
		Object* leftWall = Object::OnCreate("LeftWall");
		leftWall->SetStaticStatus(true);
		leftWall->AttachComponent<Rigidbody2D>();
		leftWall->AttachComponent<SpriteRenderer>();
		leftWall->GetTransform()->m_Position = Vector2(-8.0f, -4.0f) + Vector2(0.0f, i * 0.5f);
		leftWall->SetLayer(Layer::Wall);
		scene->AttachObject(leftWall);

		leftWalls[i] = leftWall;
	}
	for (int i = 0; i < 17; i++)
	{
		Rigidbody2D* lwrb = leftWalls[i]->GetComponent<Rigidbody2D>();
		lwrb->CreateWorldBox(Vector2(0.5f, 0.5f), 0.0f, leftWalls[i]->GetTransform()->m_Position, ColliderFilters::Environment, ColliderFilters::Player | ColliderFilters::Fluid);

		SpriteRenderer* renderer = leftWalls[i]->GetComponent<SpriteRenderer>();
		renderer->SetMaterial(groundMaterial);
	}


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
	
	AudioSource* MarioJump = AudioSource::OnCreate("Resources/Audio/mario_jump.wav", "Mario-Jump");
	player->GetComponent<AudioPlayer>()->AttachSoundToPlayer(MarioJump);
	
	player->GetComponent<AudioPlayer>()->PlaySoundEffect(MarioJump, 1, 0, false);
	


	AudioSource* BulletProof = AudioSource::OnCreate("Resources/Audio/bulletproof-soundroll-main-version-02-19-1873.mp3", "Bullet-Proof", true);
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