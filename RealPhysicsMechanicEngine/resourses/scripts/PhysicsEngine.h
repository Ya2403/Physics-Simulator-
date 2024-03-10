#pragma once

#include "SDL.h"
#include "Vector2.h"
#include "iostream"
#include <cstdlib>
#include "Ball.h"
#include "Spring.h"
#include "SystemState.h"


using namespace std;

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();
	void update(Ball arrayOfBalls[], int numberOfBalls, Spring arrayOfSprings[], int numberOfSprings, double delta_time);

	bool CheckForColitions(Ball arrayOfBalls[], int numberOfBalls);

	void lenearInterpolation(int ballIndex, int bounderyX); //isn't yet a thing but in the near future should be
	void ProcessColition(Ball &ball1, Ball &ball2);


private:
	//double delta_time = 0.01;
	int scale = 1 / 100; //1 meter = 100 picels
	double curr_Time = 0;
	double gravity = 10;
	bool isRuning;
};


