#include "LinearConstraint.h"

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
Matrix LinearConstraint::EvaluateJacobian()
{
	Vector2 vectorJ = (_firstAttachmentPoint->_pos - _secondAttachmentPoint->_pos) * 2;
	double J[4] = { vectorJ.x, vectorJ.y, vectorJ.x, vectorJ.y };
}

Matrix LinearConstraint::EvaluateJacobianTimeDerivative()
{
	Vector2 vectorJDot = (_firstAttachmentPoint->_velocity - _secondAttachmentPoint->_velocity) * 2;
	double J[1][2*maxNumberOfObjects] = {0};
	J[1][_firstAttachmentPointIndex * 2] = vectorJDot.x;
	J[1][_firstAttachmentPointIndex * 2+1] = vectorJDot.y;

	J[1][_secondAttachmentPointIndex * 2] = vectorJDot.x;
	J[1][_secondAttachmentPointIndex * 2+1] = vectorJDot.y;

	return Matrix((double**)J, 1, maxNumberOfObjects);
}