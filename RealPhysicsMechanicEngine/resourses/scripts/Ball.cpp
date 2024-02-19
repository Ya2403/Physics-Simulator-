#include "Ball.h"

Ball::Ball(int Radius, Vector2 Velocity, Vector2 Pos, double Mass, Vector2 totalForce) :
_radius(Radius), _physicsObject(PhysicsObject(Velocity, Pos, Mass, totalForce))
{

}

Ball::Ball():
_radius(1), _physicsObject(PhysicsObject())
{

}