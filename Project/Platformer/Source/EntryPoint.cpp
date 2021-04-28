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
	camera->GetComponent<Camera>()->SetSize(2.0f);

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
	rigidBody->CreateDynamicBox({1, 1}, player->GetTransform()->m_Position);
	rigidBody->SetSprite(debugBoxSprite);

	Object* ground = Object::OnCreate("Ground");
	ground->AttachComponent<Rigidbody2D>();

	ground->GetTransform()->m_Position = Vector2(0, -1.0f);

	scene->AttachObject(ground);

	Rigidbody2D* grb = ground->GetComponent<Rigidbody2D>();

	grb->CreateWorldBox(Vector2(6.0f, 2.0f), ground->GetTransform()->m_Position);
	grb->SetSprite(debugBoxSprite);
	//rigidBody->CreateWorldBox({ 5,1 }, { 0,-1.0f });
	//rigidBody->SetSprite(debugBoxSprite);

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