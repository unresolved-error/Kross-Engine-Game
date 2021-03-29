#include <Kross.h>

using namespace Kross;

int main(int argc, char** argv)
{
	Application::OnCreate();
	Application::OnStart();

	/* Create all Assets, Objects, Scenes etc. Bellow Start.*/


	Application::OnUpdate();
	Application::OnShutdown();
	Application::OnDestroy();

	return 0;
}