#include "SDL.h"

#include "Window.h"

int main(int argc, char* argv[])
{
	Window window("simulation engine", 800, 800);
	while (!window.isClosed())
	{

		/*game->handeleEvents();
		game->update();
		game->render();*/
	}

	return 0;
}