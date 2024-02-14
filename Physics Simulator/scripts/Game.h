#pragma once

#include "SDL.h"
#include "Vector2.h"
#include "iostream"
#include <cstdlib>



struct Ball
{
	int radius;
	Vector2 velocity;
	Vector2 pos;
	double mass;

	Ball()
	{
		
		radius = 1;
		velocity = velocity.zeroVector();
		pos = pos.zeroVector();
		mass = 1;
	}

	Ball(int Radius, Vector2 Velocity, Vector2 Pos, double Mass)
	{
		radius = Radius;
		velocity = Velocity;
		pos = Pos;
		mass = Mass;

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
	float Distance(Vector2 pos1, Vector2 pos2);
	void ProcessColition(Ball &ball1, Ball &ball2);


private:
	double delta_time;
	static const int NUMBEROFBALLS = 400;
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

