#include "SDL.h"
#include "PhysicsEngine.h"
#include "Window.h"

int main(int argc, char* argv[])
{
	PhysicsEngine engine = PhysicsEngine();
	Window window("simulation engine", 800, 800);
	engine.init(window._renderer);
	while (!window.isClosed())
	{
		window.PollEvent();
		engine.update();
		engine.render();

	}

	return 0;
}