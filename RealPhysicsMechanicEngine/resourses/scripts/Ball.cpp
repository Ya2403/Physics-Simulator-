#include "Ball.h"

Ball::Ball()
{
	_radius = 1;
	_velocity = _velocity.zeroVector();
	_pos = _pos.zeroVector();
	_mass = 1;
	_renderer = nullptr;
	_totalForce = _totalForce.zeroVector();
}