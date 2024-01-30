#include "SDL.h"
#include "Game.h"

Game* game = nullptr;
int main(int argc, char* argv[])
{
	game = new Game();
	game->init("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0);
	while (game->isRuningCheck())
	{
		game->handeleEvents();
		game->update();
		game->render();
	}

	game->clean();
	return 0;
}