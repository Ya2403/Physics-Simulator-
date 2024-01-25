#pragma once

#include "SDL.h"

#include "iostream"

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int x, int y, int width, int height, bool fullscreen);

	void handeleEvents();
	void update();
	void render();
	void clean();

	bool isRuningCheck() { return isRuning; };


private:
	bool isRuning;
	int cnt = 0;
	SDL_Window* window;
	SDL_Renderer* renderer;

};


