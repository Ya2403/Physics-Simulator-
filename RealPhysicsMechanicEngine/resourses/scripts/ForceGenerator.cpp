#include "ForceGenerator.h"

void ForceGenerator::GenerateForce(Vector2 force, PhysicsObject & object)
{
	object._totalForce = force + object._totalForce;
}
