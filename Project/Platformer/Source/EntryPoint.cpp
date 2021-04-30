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
	Texture* debugBoxTexture = Texture::OnCreate("Resources/Textures/DebugBox.png", "Box");
	Texture* debugCircleTexture = Texture::OnCreate("Resources/Textures/DebugCircle.png", "Circle");
	Sprite* sprite = Sprite::OnCreate(texture, 32, 32, "Default");
	Sprite* debugBoxSprite = Sprite::OnCreate(debugBoxTexture, 32, 32, "Box");
	Sprite* debugCircleSprite = Sprite::OnCreate(debugCircleTexture, 32, 32, "Circle");

	Object* camera = Object::OnCreate("Camera");
	camera->AttachComponent<Camera>();
	camera->GetComponent<Camera>()->SetSize(6.0f);

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

	SpriteRenderer* renderer = player->GetComponent<SpriteRenderer>();
	renderer->SetSprite(sprite);

	scene->AttachObject(player);


	Object* particleEmitter = Object::OnCreate("Emitter");
	particleEmitter->AttachComponent<ParticleEmitter>();
	particleEmitter->GetTransform()->m_Position = Vector2(2.0f, 2.0f);

	scene->AttachObject(particleEmitter);

	ParticleEmitter* particle = particleEmitter->GetComponent<ParticleEmitter>();
	particle->GetParticle()->AddParticleFlag(b2_waterParticle);
	particle->GetParticle()->AddParticleFlag(b2_staticPressureParticle);
	particle->GetParticle()->SetPosition({ particleEmitter->GetTransform()->m_Position.x, particleEmitter->GetTransform()->m_Position.y });
	particle->GetParticle()->SetColor({ 0.0f, 100.0f, 207.0f, 255.0f });
	particle->GetParticle()->SetPosition(Vector2(particleEmitter->GetTransform()->m_Position.x, particleEmitter->GetTransform()->m_Position.y));
	particle->SetParticleCount(100);


	Object* platform = Object::OnCreate("Platform");
	platform->AttachComponent<Rigidbody2D>();
	platform->GetTransform()->m_Position = Vector2(0.0f, -2.5f);

	scene->AttachObject(platform);

	Rigidbody2D* prb = platform->GetComponent<Rigidbody2D>();
	prb->CreateWorldBox(Vector2(2.0f, 0.5f), platform->GetTransform()->m_Position);


	Object* ground = Object::OnCreate("Ground");
	ground->AttachComponent<Rigidbody2D>();

	ground->GetTransform()->m_Position = Vector2(0.0f, -4.0f);
	
	scene->AttachObject(ground);

	Rigidbody2D* grb = ground->GetComponent<Rigidbody2D>();
	grb->CreateWorldBox(Vector2(17.0f, 1.0f), ground->GetTransform()->m_Position);
	

	Object* roof = Object::OnCreate("Roof");
	roof->AttachComponent<Rigidbody2D>();
	
	roof->GetTransform()->m_Position = Vector2(0, 4.0f);
	
	scene->AttachObject(roof);
	
	Rigidbody2D* rrb = roof->GetComponent<Rigidbody2D>();
	
	rrb->CreateWorldBox(Vector2(17.0f, 1.0f), roof->GetTransform()->m_Position);
	
	
	Object* rightWall = Object::OnCreate("RightWall");
	rightWall->AttachComponent<Rigidbody2D>();
	
	rightWall->GetTransform()->m_Position = Vector2(8.0f, 0.0f);
	
	scene->AttachObject(rightWall);
	
	Rigidbody2D* rwrb = rightWall->GetComponent<Rigidbody2D>();
	
	rwrb->CreateWorldBox(Vector2(1.0f, 9.0f), rightWall->GetTransform()->m_Position);
	
	
	Object* leftWall = Object::OnCreate("LeftWall");
	leftWall->AttachComponent<Rigidbody2D>();
	
	leftWall->GetTransform()->m_Position = Vector2(-8.0f, 0.0f);
	
	scene->AttachObject(leftWall);
	
	Rigidbody2D* lwrb = leftWall->GetComponent<Rigidbody2D>();
	
	lwrb->CreateWorldBox(Vector2(1.0f, 9.0f), leftWall->GetTransform()->m_Position);


	Rigidbody2D* rigidBody = player->GetComponent<Rigidbody2D>();
	rigidBody->CreateDynamicBox(Vector2(0.25, 0.25f), player->GetTransform()->m_Position, true);
	rigidBody->SetMass(0.25f);

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