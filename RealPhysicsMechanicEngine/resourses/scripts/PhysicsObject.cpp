#include "PhysicsObject.h"


PhysicsObject::PhysicsObject(Vector2 Velocity, Vector2 Pos, double Mass, Vector2 totalForce):
_velocity(Velocity), _pos(Pos), _mass(Mass), _totalForce(totalForce)
{

}

PhysicsObject::PhysicsObject():
_velocity(_velocity.zeroVector()), _mass(1), _totalForce(_totalForce.zeroVector()), _pos(_pos.zeroVector())
{
}

void PhysicsObject::AddForce(Vector2 force)
{
	_totalForce = _totalForce + force;
}
