#pragma once
#include "Vector2.h"
#include "PhysicsObject.h"


class ForceGenerator
{
	ForceGenerator();
public:
	void GenerateForce(Vector2 force, PhysicsObject& object);
};

