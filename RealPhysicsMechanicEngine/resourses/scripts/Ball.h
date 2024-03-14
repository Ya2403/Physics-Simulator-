
#pragma once
#include "Vector2.h"
#include "SDL.h"
#include "PhysicsObject.h"

class Ball
{
public:
	Ball(int Radius, Vector2 Velocity, Vector2 Pos, double Mass, Vector2 totalForce, bool isFixedPoint);
	Ball();

public:
	int _radius = 1;
	PhysicsObject _physicsObject;
};
