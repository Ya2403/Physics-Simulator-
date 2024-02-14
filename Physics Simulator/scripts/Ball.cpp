#include "Ball.h"

Ball::Ball()
{
	_radius = 1;
	_velocity = velocity.zeroVector();
	_pos = pos.zeroVector();
	_mass = 1;
	_renderer = nullptr;
}