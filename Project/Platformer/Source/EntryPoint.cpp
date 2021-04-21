#include <Kross.h>
#include "PlayerMovement.h"

using namespace Kross;

int main(int argc, char** argv)
{
	Application::OnCreate();
	Application::OnStart();

	/* Create all Assets, Objects, Scenes etc. Bellow Start.*/
	/* Until a manifest file is introduced. */

	Texture* texture = Texture::OnCreate("Resources/Textures/Default.png", "Default");
	Sprite* sprite = Sprite::OnCreate(texture, 32, 32, "Default");

	Object* camera = Object::OnCreate("Camera");
	camera->AttachComponent<Camera>();
	camera->GetComponent<Camera>()->SetSize(2.0f);

	Object* player = Object::OnCreate("Player");
	player->AttachComponent<SpriteRenderer>();
	player->AttachComponent<PlayerMovement>();

	Object* textExample = Object::OnCreate("Text");
	textExample->AttachComponent<TextRenderer>();

	TextRenderer* textRenderer = textExample->GetComponent<TextRenderer>();
	textRenderer->SetFont(ResourceManager::GetResource<Font>(0));
	textRenderer->SetColour(Colour(1.0f, 1.0f, 1.0f, 1.0f));
	textRenderer->SetTextSize(2.0f);
	textRenderer->SetText("!@#$&*^ DFG0099--+");

	SpriteRenderer* renderer = player->GetComponent<SpriteRenderer>();
	renderer->SetSprite(sprite);

	Scene* scene = Scene::OnCreate("Main");
	scene->AttachObject(camera);
	scene->AttachObject(player);
	scene->AttachObject(textExample);

	SceneManager::AttachScene(scene);
	SceneManager::SetCurrentScene(0);

	Application::OnUpdate();
	Application::OnShutdown();
	Application::OnDestroy();
	return 0;
}