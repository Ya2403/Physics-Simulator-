#pragma once
#include "Ball.h"
#include "Spring.h"

class SystemState
{
public:
	SystemState();
	~SystemState();
	SystemState(Ball arrayOfBalls[], int numberOfBalls, Spring arrayOfSprings[], int numberOfSprings);

	Ball _arrayOfBalls[100];
	int _numberOfBalls; 
	Spring _arrayOfSprings[100];
	int _numberOfSprings;

private:

};



