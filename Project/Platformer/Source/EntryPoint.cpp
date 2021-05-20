#include <Kross.h>
#include "PlayerMovement.h"

using namespace Kross;

int main(int argc, char** argv)
{
	Application::OnCreate();
	Application::OnStart();

	/* Create all Assets, Objects, Scenes etc. Bellow Start.*/
	/* Until a manifest file is introduced. */
	int renderMode = 0;

	Scene* scene = Scene::OnCreate("Main");

	Texture* texture = Texture::OnCreate("Resources/Textures/Default.png", "Default");
	Texture* wallTexture = Texture::OnCreate("Resources/Textures/TempWall.png", "Wall");
	Sprite* sprite = Sprite::OnCreate(texture, 32, 32, "Default");
	Sprite* wallSprite = Sprite::OnCreate(wallTexture, 128,128, "Wall");

	Object* camera = Object::OnCreate("Camera");
	camera->AttachComponent<Camera>();
	camera->GetComponent<Camera>()->SetSize(8.0f);

	Object* player = Object::OnCreate("Player");
	player->AttachComponent<SpriteRenderer>();
	player->AttachComponent<Rigidbody2D>();
	player->AttachComponent<PlayerMovement>();
	player->GetComponent<PlayerMovement>()->camera = camera->GetComponent<Camera>();
	
	player->GetTransform()->m_Position = Vector2(0.0f, 0.0f);
	player->GetTransform()->m_Scale = Vector2(1.0f, 1.0f);
	player->GetTransform()->m_Rotation = 0.0f;
	

	Object* textExample = Object::OnCreate("Text");
	textExample->AttachComponent<TextRenderer>();

	TextRenderer* textRenderer = textExample->GetComponent<TextRenderer>();
	textRenderer->SetFont(ResourceManager::GetResource<Font>(0));
	textRenderer->SetColour(Colour(1.0f, 1.0f, 1.0f, 1.0f));
	textRenderer->SetTextSize(3.0f);
	textRenderer->SetText("Hello AIE!");
	
	player->GetComponent<PlayerMovement>()->textObj = textRenderer;
	player->SetLayer(Layer::Background);
	
	SpriteRenderer* renderer = player->GetComponent<SpriteRenderer>();
	renderer->SetSprite(sprite);

	scene->AttachObject(player);



	Object* platforms[6];
	for (int i = 0; i < 6; i++)
	{
		Object* platform = Object::OnCreate("Platform");
		platform->SetStaticStatus(true);
		platform->AttachComponent<SpriteRenderer>();
		platform->AttachComponent<Rigidbody2D>();
		platform->GetTransform()->m_Position = Vector2(-3.0f, -2.75f) + Vector2(i, 0.0f);
		platform->SetLayer(Layer::Ground);
		scene->AttachObject(platform);
	
		platforms[i] = platform;
	}
	for (int i = 0; i < 6; i++)
	{
		Rigidbody2D* prb = platforms[i]->GetComponent<Rigidbody2D>();
		prb->CreateWorldBox(Vector2(1.0f, 1.0f), platforms[i]->GetTransform()->m_Position, ColliderFilters::Environment, ColliderFilters::Player | ColliderFilters::Fluid);
	
		SpriteRenderer* renderer = platforms[i]->GetComponent<SpriteRenderer>();
		renderer->SetSprite(wallSprite);
	}


	Object* grounds[15];
	for (int i = 0; i < 15; i++)
	{
		Object* ground = Object::OnCreate("Ground");
		ground->SetStaticStatus(true);
		ground->AttachComponent<SpriteRenderer>();
		ground->AttachComponent<Rigidbody2D>();
		ground->GetTransform()->m_Position = Vector2(-7.0f, -4.0f) + Vector2(i, 0.0f);
		ground->SetLayer(Layer::Ground);
		scene->AttachObject(ground);

		grounds[i] = ground;
	}
	for (int i = 0; i < 15; i++)
	{
		Rigidbody2D* grb = grounds[i]->GetComponent<Rigidbody2D>();
		grb->CreateWorldBox(Vector2(1.0f, 1.0f), grounds[i]->GetTransform()->m_Position, ColliderFilters::Environment, ColliderFilters::Player | ColliderFilters::Fluid);

		SpriteRenderer* renderer = grounds[i]->GetComponent<SpriteRenderer>();
		renderer->SetSprite(wallSprite);
	}


	Object* roofs[15];
	for (int i = 0; i < 15; i++)
	{
		Object* roof = Object::OnCreate("Roof");
		roof->SetStaticStatus(true);
		roof->AttachComponent<SpriteRenderer>();
		roof->AttachComponent<Rigidbody2D>();
		roof->GetTransform()->m_Position = Vector2(-7.0f, 4.0f) + Vector2(i, 0.0f);
		scene->AttachObject(roof);

		roofs[i] = roof;
	}
	for (int i = 0; i < 15; i++)
	{
		Rigidbody2D* rrb = roofs[i]->GetComponent<Rigidbody2D>();
		rrb->CreateWorldBox(Vector2(1.0f, 1.0f), roofs[i]->GetTransform()->m_Position, ColliderFilters::Environment, ColliderFilters::Player | ColliderFilters::Fluid);

		SpriteRenderer* renderer = roofs[i]->GetComponent<SpriteRenderer>();
		renderer->SetSprite(wallSprite);
	}


	Object* rightWalls[9];
	for (int i = 0; i < 9; i++)
	{
		Object* rightWall = Object::OnCreate("RightWall");
		rightWall->SetStaticStatus(true);
		rightWall->AttachComponent<SpriteRenderer>();
		rightWall->AttachComponent<Rigidbody2D>();
		rightWall->GetTransform()->m_Position = Vector2(8.0f, -4.0f) + Vector2(0.0f, i);
		rightWall->SetLayer(Layer::Wall);
		scene->AttachObject(rightWall);

		rightWalls[i] = rightWall;
	}
	for (int i = 0; i < 9; i++)
	{
		Rigidbody2D* rwrb = rightWalls[i]->GetComponent<Rigidbody2D>();
		rwrb->CreateWorldBox(Vector2(1.0f, 1.0f), 0.0f, rightWalls[i]->GetTransform()->m_Position, ColliderFilters::Environment, ColliderFilters::Player | ColliderFilters::Fluid);

		SpriteRenderer* renderer = rightWalls[i]->GetComponent<SpriteRenderer>();
		renderer->SetSprite(wallSprite);
	}


	Object* leftWalls[9];
	for (int i = 0; i < 9; i++)
	{
		Object* leftWall = Object::OnCreate("LeftWall");
		leftWall->SetStaticStatus(true);
		leftWall->AttachComponent<SpriteRenderer>();
		leftWall->AttachComponent<Rigidbody2D>();
		leftWall->GetTransform()->m_Position = Vector2(-8.0f, -4.0f) + Vector2(0.0f, i);
		leftWall->SetLayer(Layer::Wall);
		scene->AttachObject(leftWall);

		leftWalls[i] = leftWall;
	}
	for (int i = 0; i < 9; i++)
	{
		Rigidbody2D* lwrb = leftWalls[i]->GetComponent<Rigidbody2D>();
		lwrb->CreateWorldBox(Vector2(1.0f, 1.0f), 0.0f, leftWalls[i]->GetTransform()->m_Position, ColliderFilters::Environment, ColliderFilters::Player | ColliderFilters::Fluid);

		SpriteRenderer* renderer = leftWalls[i]->GetComponent<SpriteRenderer>();
		renderer->SetSprite(wallSprite);
	}


	Rigidbody2D* rigidBody = player->GetComponent<Rigidbody2D>();
	rigidBody->CreateDynamicBox(Vector2(0.25, 0.25f), player->GetTransform()->m_Position,  true, ColliderFilters::Player, ColliderFilters::Environment);
	//rigidBody->SetMass(1.25f);


	Object* particleEmitter = Object::OnCreate("Emitter");
	particleEmitter->SetStaticStatus(true);
	particleEmitter->AttachComponent<ParticleEmitter>();
	particleEmitter->GetTransform()->m_Position = Vector2(0.0f, 0.0f);
	particleEmitter->SetLayer(Layer::Fluids);
	
	scene->AttachObject(particleEmitter);

	ParticleEmitter* particle = particleEmitter->GetComponent<ParticleEmitter>();
	particle->SetParticleType(ParticleType::ParticleGroup);
	particle->SetColliderFilters(ColliderFilters::Fluid, ColliderFilters::Environment);
	
	particle->GetParticle()->AddParticleFlag(b2_waterParticle | b2_fixtureContactFilterParticle);
	particle->GetParticle()->AddParticleGroupFlag(b2_solidParticleGroup);
	particle->GetParticle()->SetShape(0.75f);
	//particle->GetParticle()->SetColor({ 0.0f, 100.0f, 207.0f, 255.0f });
	//particle->GetParticle()->SetPosition(Vector2(particleEmitter->GetTransform()->m_Position.x, particleEmitter->GetTransform()->m_Position.y));
	particle->SetMaxCount(0);
	particle->SetGroupCount(1);

	player->GetComponent<PlayerMovement>()->rigidBody = rigidBody;

	scene->AttachObject(camera);
	scene->AttachObject(textExample);

	SceneManager::AttachScene(scene);
	SceneManager::SetCurrentScene(0);


	Application::OnUpdate();
	Application::OnShutdown();
	Application::OnDestroy();
	
	return 0;
}