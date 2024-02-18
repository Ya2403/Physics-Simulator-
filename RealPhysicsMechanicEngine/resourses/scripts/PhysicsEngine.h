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
	void update(Ball arrayOfBalls[], int numberOfBalls);
	
	void Move(int ballIxdex);
	void CalculateColition(Ball *ball1, Ball* ball2);
	bool CheckForColitions(Ball arrayOfBalls[], int numberOfBalls);
	void lenearInterpolation(int ballIndex, int bounderyX);
	void ProcessColition(Ball &ball1, Ball &ball2);


private:
	double delta_time = 0.01;
	int x= 50;
	int y= 90;
	float velocityXModule = 1;
	float velocityY = 1;
	bool isRuning;
	int cnt = 0;
};

