#pragma once
#include "PhysicsObject.h"
#include "matrix.h"

class LinearConstraint 
{
public:
	LinearConstraint();
	~LinearConstraint();
	LinearConstraint(PhysicsObject &firstPoint, PhysicsObject& secondPoint);
	LinearConstraint(PhysicsObject& firstPoint, PhysicsObject& secondPoint, int index1, int index2, double initialLenght);
	double EvaluateConstraintFunction(); 
	double EvaluateFirstTimeDerivatie();;
	Matrix EvaluateJacobian(int);
	Matrix EvaluateJacobianTimeDerivative(int );
	
	
private:
	static const int maxNumberOfObjects = 1000;
	PhysicsObject *_firstAttachmentPoint;
	PhysicsObject* _secondAttachmentPoint;
	int _firstAttachmentPointIndex;
	int _secondAttachmentPointIndex;
	double _initialLenght;
		
};

