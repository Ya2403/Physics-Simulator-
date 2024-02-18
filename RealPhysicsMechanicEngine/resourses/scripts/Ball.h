
#pragma once
#include "Vector2.h"
#include "SDL.h"
#include "PhysicsObject.h"

class Ball
{
public:
	Ball(int Radius, Vector2 Velocity, Vector2 Pos, double Mass, Vector2 totalForce);


public:
	int _radius;
	PhysicsObject _physicsObject;
};
