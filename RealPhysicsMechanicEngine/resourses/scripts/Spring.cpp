#include "Spring.h"

Spring::Spring(PhysicsObject& conectsPoin1, PhysicsObject& conectsPoin2, double stiffnessK) :
	_stiffness(stiffnessK), _connectionPoint1(&conectsPoin1), _connectionPoint2(&conectsPoin2), _initianLenght(conectsPoin1._pos.Distance(conectsPoin2._pos))
{
	//conectsPoin2.AddConnection(*this);
	//conectsPoin1.AddConnection(*this);
}

Spring::Spring()
{
}

Spring::~Spring()
{
}
void Spring::Update()
{
	Vector2 normalToTheSpring = _connectionPoint2->_pos - _connectionPoint1->_pos;
	normalToTheSpring.normalizeVector();

	double forceAbsValue =  _stiffness * (_initianLenght - _connectionPoint2->_pos.Distance(_connectionPoint1->_pos)); 
	_connectionPoint2->AddForce(normalToTheSpring * forceAbsValue);
	_connectionPoint1->AddForce(normalToTheSpring * forceAbsValue * (-1));
}