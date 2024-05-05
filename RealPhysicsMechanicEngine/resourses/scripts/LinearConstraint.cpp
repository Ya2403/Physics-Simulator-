#include "LinearConstraint.h"


LinearConstraint::LinearConstraint()
{}

LinearConstraint::~LinearConstraint()
{
}


LinearConstraint::LinearConstraint(PhysicsObject& firstPoint, PhysicsObject& secondPoint):
_firstAttachmentPoint(&firstPoint), _secondAttachmentPoint(&secondPoint), _initialLenght(firstPoint._pos.Distance(secondPoint._pos))
{
}

LinearConstraint::LinearConstraint(PhysicsObject& firstPoint, PhysicsObject& secondPoint, int index1, int index2, double intialLenght) :
	_firstAttachmentPoint(&firstPoint), _secondAttachmentPoint(&secondPoint), _initialLenght(intialLenght), _firstAttachmentPointIndex(index1), _secondAttachmentPointIndex(index2)
{
}


//returns C = (r1-r2)*(r1-r2) - l0
double LinearConstraint::EvaluateConstraintFunction()
{
	Vector2 r12 = _firstAttachmentPoint->_pos - _secondAttachmentPoint->_pos;
	return r12 * r12 - _initialLenght * _initialLenght;
}

//returns dC/dt = 2*(r1-r2)*(v1-v2)
double LinearConstraint::EvaluateFirstTimeDerivatie()
{
	Vector2 v12 = _firstAttachmentPoint->_velocity - _secondAttachmentPoint->_velocity;
	Vector2 r12 = _firstAttachmentPoint->_pos - _secondAttachmentPoint->_pos;
	return (v12 * r12)*2;
}


//J = dC/dr matrix is [jx, jy] 
Matrix LinearConstraint::EvaluateJacobian(int numberOfObjects)
{
	Vector2 vectorJ = (_firstAttachmentPoint->_pos - _secondAttachmentPoint->_pos) * 2;
	unique_ptr<double[]> J (new double[2*numberOfObjects] {0});
	J.get()[_firstAttachmentPointIndex * 2] = vectorJ.x;
	J.get()[_firstAttachmentPointIndex * 2 + 1] = vectorJ.y;

	J.get()[_secondAttachmentPointIndex * 2] = vectorJ.x;
	J.get()[_secondAttachmentPointIndex * 2 + 1] = vectorJ.y;


	return Matrix((double**)J.get(), 1, 2 * numberOfObjects);
}

Matrix LinearConstraint::EvaluateJacobianTimeDerivative(int numberOfObjects)
{
	Vector2 vectorJDot = (_firstAttachmentPoint->_velocity - _secondAttachmentPoint->_velocity) * 2;
	unique_ptr<double[]> J (new double[2*numberOfObjects] {0});
	J.get()[_firstAttachmentPointIndex * 2] = vectorJDot.x;
	J.get()[_firstAttachmentPointIndex * 2+1] = vectorJDot.y;

	J.get()[_secondAttachmentPointIndex * 2] = vectorJDot.x;
	J.get()[_secondAttachmentPointIndex * 2+1] = vectorJDot.y;

	return Matrix((double**)(J.get()), 1, 2 * numberOfObjects);
}