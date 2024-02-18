#pragma once

#include "PhysicsEngine.h"
#include "GraphicsSystem.h"

class Engine
{
	Engine();
	~Engine();

public:
	void Render();
	void Update();

	void RandomSpawnBalls(); //temporery funtion to spawn balls




private:
	//Graphics component
	GraphicsSystem _graphics;
	//Physics component
	PhysicsEngine physics;

	static const int MAX_NUMBER_OF_PHYSICS_OBJECTS = 20;
	//pool of all physics object 
	Ball ballsArrey[MAX_NUMBER_OF_PHYSICS_OBJECTS];

};

