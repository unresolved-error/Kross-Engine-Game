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

	Object* player = Object::OnCreate("Player");
	player->AttachComponent<SpriteRenderer>();
	player->AttachComponent<PlayerMovement>();

	SpriteRenderer* renderer = player->GetComponent<SpriteRenderer>();
	renderer->SetSprite(sprite);

	Scene* scene = Scene::OnCreate("Main");
	scene->AttachObject(camera);
	scene->AttachObject(player);

	SceneManager::AttachScene(scene);
	SceneManager::SetCurrentScene(0);

	Application::OnUpdate();
	Application::OnShutdown();
	Application::OnDestroy();
	return 0;
}