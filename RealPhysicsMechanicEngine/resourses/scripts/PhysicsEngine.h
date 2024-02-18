#pragma once

#include "SDL.h"
#include "Vector2.h"
#include "iostream"
#include <cstdlib>
#include "Ball.h"

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	void init(SDL_Renderer* renderer);
	void update();
	
	void Move(int ballIxdex);
	void CalculateColition(Ball *ball1, Ball* ball2);
	bool CheckForColitions();
	void lenearInterpolation(int ballIndex, int bounderyX);
	void ProcessColition(Ball &ball1, Ball &ball2);


private:
	double delta_time = 0.01;
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
};

