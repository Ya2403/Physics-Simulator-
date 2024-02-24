#pragma once
#include "PhysicsObject.h"

class Spring
{
public:
	Spring();
	~Spring();
	Spring(PhysicsObject& conectsPoin1, PhysicsObject& conectsPoin2, double stiffnessK);

public:
	void Update();

public:
	PhysicsObject* _connectionPoint1 = nullptr;
	PhysicsObject* _connectionPoint2 = nullptr;

	double _stiffness = 1;
	double _initianLenght = 1;
};

