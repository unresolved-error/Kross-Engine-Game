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
	camera->GetComponent<Camera>()->SetSize(3.0f);

	Object* player = Object::OnCreate("Player");
	player->AttachComponent<Rigidbody2D>();
	player->AttachComponent<SpriteRenderer>();
	player->AttachComponent<PlayerMovement>();

	player->GetTransform()->m_Position = Vector2(0.0f, 0.0f);

	Object* textExample = Object::OnCreate("Text");
	textExample->AttachComponent<TextRenderer>();

	TextRenderer* textRenderer = textExample->GetComponent<TextRenderer>();
	textRenderer->SetFont(ResourceManager::GetResource<Font>(0));
	textRenderer->SetColour(Colour(1.0f, 1.0f, 1.0f, 1.0f));
	textRenderer->SetTextSize(2.0f);
	textRenderer->SetText("!@#$&*^ DFG0099--+");

	player->GetComponent<PlayerMovement>()->rend = textRenderer;

	SpriteRenderer* renderer = player->GetComponent<SpriteRenderer>();
	renderer->SetSprite(sprite);

	scene->AttachObject(player);

	Rigidbody2D* rigidBody = player->GetComponent<Rigidbody2D>();
	rigidBody->CreateDynamicBox(Vector2(1.0f, 1.0f), player->GetTransform()->m_Position);
	rigidBody->SetSprite(debugBoxSprite);


	Object* ground = Object::OnCreate("Ground");
	ground->AttachComponent<Rigidbody2D>();

	ground->GetTransform()->m_Position = Vector2(0.0f, -1.0f);

	scene->AttachObject(ground);

	Rigidbody2D* grb = ground->GetComponent<Rigidbody2D>();
	
	grb->CreateWorldBox(Vector2(16.5f, 0.5f), ground->GetTransform()->m_Position);
	grb->SetSprite(debugBoxSprite);
	

	Object* roof = Object::OnCreate("Roof");
	roof->AttachComponent<Rigidbody2D>();
	
	roof->GetTransform()->m_Position = Vector2(0, 1.0f);
	
	scene->AttachObject(roof);
	
	Rigidbody2D* rfb = roof->GetComponent<Rigidbody2D>();
	
	rfb->CreateWorldBox(Vector2(16.5f, -0.5f), roof->GetTransform()->m_Position);
	rfb->SetSprite(debugBoxSprite);
	
	
	Object* rightWall = Object::OnCreate("RightWall");
	rightWall->AttachComponent<Rigidbody2D>();
	
	rightWall->GetTransform()->m_Position = Vector2(2.0f, 0.0f);
	
	scene->AttachObject(rightWall);
	
	Rigidbody2D* rwb = rightWall->GetComponent<Rigidbody2D>();
	
	rwb->CreateWorldBox(Vector2(-0.5f, 8.0f), rightWall->GetTransform()->m_Position);
	rwb->SetSprite(debugBoxSprite);
	
	
	Object* leftWall = Object::OnCreate("LeftWall");
	leftWall->AttachComponent<Rigidbody2D>();
	
	leftWall->GetTransform()->m_Position = Vector2(-2.0f, 0.0f);
	
	scene->AttachObject(leftWall);
	
	Rigidbody2D* lwb = leftWall->GetComponent<Rigidbody2D>();
	
	lwb->CreateWorldBox(Vector2(-0.5f, 8.0f), leftWall->GetTransform()->m_Position);
	lwb->SetSprite(debugBoxSprite);


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