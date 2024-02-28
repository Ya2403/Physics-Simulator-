#include "SystemState.h"

SystemState::SystemState()
{
}

SystemState::~SystemState()
{
}

SystemState::SystemState(Ball arrayOfBalls[], int numberOfBalls, Spring arrayOfSprings[], int numberOfSprings) :
	_numberOfBalls(numberOfBalls), _numberOfSprings(numberOfSprings)
{
	for (int i = 0; i < numberOfBalls; i++)
	{
		_arrayOfBalls[i] = arrayOfBalls[i];
	}

	for (int i = 0; i < numberOfSprings; i++)
	{
		_arrayOfSprings[i] = arrayOfSprings[i];
	}
}