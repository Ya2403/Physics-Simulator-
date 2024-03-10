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

void PhysicsObject::Update(double time_step)
{
	_pos = _pos + _velocity * time_step;

	_velocity = _velocity + _totalForce * (1.0 /_mass) * time_step;
	
	_totalForce = _totalForce.zeroVector();//total_force should be now zero so that it wont summ up
}

void PhysicsObject::UpdateWithKnownForce(double time_step, Vector2 totaleForce)
{
	_velocity = _velocity + totaleForce * (1.0 / _mass) * time_step;

	_totalForce = totaleForce.zeroVector();//total_force should be now zero so that it wont summ up
	_pos = _pos + _velocity * time_step;
}

//void PhysicsObject::AddConnection(Spring &spring)
//{
//	_connectionsArray[_numberOfConnections] = &spring;
//	_numberOfConnections++;
//}
