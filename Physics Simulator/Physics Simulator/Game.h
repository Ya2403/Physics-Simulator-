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
	void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);
	bool isRuningCheck() { return isRuning; };
	void Move();


private:
	int x= 50;
	int y= 90;
	float velocityX = 2;
	float velocityY = 1;
	bool isRuning;
	int cnt = 0;
	SDL_Window* window;
	SDL_Renderer* renderer;

};


