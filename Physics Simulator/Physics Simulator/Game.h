#pragma once

#include "SDL.h"

#include "iostream"
#include <cstdlib>


struct Ball
{
	int radius;
	float vx;
	float vy;
	float pos[2];

	Ball()
	{
		radius = 1;
		vx = 0;
		vy = 0;
		pos[1] = 0;
		pos[0] = 0;
	}

	Ball(int Radius, float Vx, float Vy, float X, float Y)
	{
		radius = Radius;
		vx = Vx;
		vy = Vy;
		pos[0] = X;
		pos[1] = Y;
	}
};

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
	void Move(int ballIxdex);
	void RandomSpawnBalls();
	void CalculateColition(Ball *ball1, Ball* ball2);
	bool CheckForColitions();
	void lenearInterpolation(int ballIndex, int bounderyX);
	float Distance(float pos1[2], float pos2[2]);


private:
	static const int NUMBEROFBALLS = 20;
	Ball ballsArrey[NUMBEROFBALLS];

	float borderX = 0;
	float period = 1;
	float curBorderTime = 0;
	float amplitude = 100;
	int numOfBall = 0;
	int x= 50;
	int y= 90;
	float velocityXModule = 1;
	float velocityY = 1;
	bool isRuning;
	int cnt = 0;
	SDL_Window* window;
	SDL_Renderer* renderer;

};

