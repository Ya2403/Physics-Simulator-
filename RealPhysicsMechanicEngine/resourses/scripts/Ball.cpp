#include "Ball.h"

Ball::Ball(int Radius, Vector2 Velocity, Vector2 Pos, double Mass, Vector2 totalForce, bool isFixedPoint) :
_radius(Radius), _physicsObject(PhysicsObject(Velocity, Pos, Mass, totalForce, isFixedPoint))
{

}

Ball::Ball():
_radius(1), _physicsObject(PhysicsObject())
{

}