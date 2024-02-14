#include "Balls.h"

Balls::Balls()
{
	_radius = 1;
	_velocity = _velocity.zeroVector();
	_pos = _pos.zeroVector();
	_mass = 1;
	_renderer = nullptr;
}