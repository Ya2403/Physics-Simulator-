#pragma once
#include "Vector2.h"
#include "SDL.h"

class Balls
{
public:
	Balls();
	Balls(int Radius, Vector2 Velocity, Vector2 Pos, double Mass);
	void Draw();

private:
	int _radius;
	Vector2 _velocity;
	Vector2 _pos;
	double _mass;
	SDL_Renderer* _renderer;
	Vector2 _totalForce;
};
