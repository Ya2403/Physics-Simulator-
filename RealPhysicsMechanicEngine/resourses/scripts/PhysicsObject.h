#pragma once
#include "Vector2.h"
#include "SDL.h"

class PhysicsObject
{
public:
	PhysicsObject(Vector2 Velocity, Vector2 Pos, double Mass, Vector2 totalForce);
	void AddForce(Vector2 force);



public:
	double _angulareVelocity = 0;
	Vector2 _velocity = _velocity.zeroVector(); //in m/s
	Vector2 _pos = _pos.zeroVector(); //in meters
	double _mass = 1; //in kg
	Vector2 _totalForce = _totalForce.zeroVector(); //in N
};
