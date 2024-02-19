#pragma once

#include "PhysicsEngine.h"
#include "GraphicsSystem.h"

class Engine
{
	Engine(const std::string& windowtitle, int width, int height); //should have all the stuff to inti the window that's 
	~Engine();

public:
	void Render();
	void Update();

	void RandomSpawnBalls(); //temporery funtion to spawn balls




private:
	//Graphics component
	GraphicsSystem _graphics;
	//Physics component
	PhysicsEngine _physics;

	static const int MAX_NUMBER_OF_PHYSICS_OBJECTS = 20;
	//pool of all physics object 
	Ball ballsArrey[MAX_NUMBER_OF_PHYSICS_OBJECTS];

};

