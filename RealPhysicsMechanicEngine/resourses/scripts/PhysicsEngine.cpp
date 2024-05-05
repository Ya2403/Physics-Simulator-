#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{

}

void PhysicsEngine::update(Ball arrayOfBalls[], int numberOfBalls, Spring arrayOfSprings[], int numberOfSprings, double delta_time, LinearConstraint arrayOfConstraints[], int numberOfConstraints)
{
	double energy = 0;
	//check for colition
	//CheckForColitions(arrayOfBalls, numberOfBalls);

	RungeKuttaStep(arrayOfBalls, numberOfBalls, arrayOfSprings, numberOfSprings, delta_time);
	CalculateConstrainForces(arrayOfBalls, numberOfBalls, arrayOfConstraints, numberOfConstraints);
	
}

void PhysicsEngine::CalculateForces(Ball arrayOfBalls[], int numberOfBalls, Spring arrayOfSprings[], int numberOfSprings)
{
	for (int j = 0; j < numberOfSprings; j++)
	{
		arrayOfSprings[j].Update();//update connected springs
	}


	for (int j = 0; j < numberOfBalls; j++)
	{
		if (!arrayOfBalls[j]._physicsObject._isFixedPoint)
		{
			arrayOfBalls[j]._physicsObject.AddForce(Vector2(0, gravity * arrayOfBalls[j]._physicsObject._mass)); //gravity
			//arrayOfBalls[j]._physicsObject.AddForce(arrayOfBalls[j]._physicsObject._velocity * -1);//viscous friction
		}
	}
}

bool PhysicsEngine::CheckForColitions(Ball arrayOfBalls[], int numberOfBalls )
{
	int windowHight = 800;
	int windowWidht = 1000;

	 
	for (int i = 0; i < numberOfBalls; i++)
	{
		//between balls collition
		for (int j = i + 1; j < numberOfBalls; j++)
		{
			//std::cout << "colision" << std::endl;
			if (arrayOfBalls[i]._physicsObject._pos.Distance(arrayOfBalls[j]._physicsObject._pos) <= (arrayOfBalls[i]._radius + arrayOfBalls[j]._radius))
			{

				ProcessColition(arrayOfBalls[i], arrayOfBalls[j]);
				//perform colision
				
			}
		}

		if (arrayOfBalls[i]._physicsObject._pos.x - arrayOfBalls[i]._radius < 0)
		{
			arrayOfBalls[i]._physicsObject._pos.x = 0 + arrayOfBalls[i]._radius;
			if (arrayOfBalls[i]._physicsObject._velocity.x < 0)
			{

				arrayOfBalls[i]._physicsObject._velocity.x *= -1.0;
				//arrayOfBalls[ballIxdex].vx += abs(amplitude * (cos(2 * 3.14 * curBorderTime / period)- cos(2 * 3.14 * curBorderTime-1/60.0 / period))*30.0);
			}
		}
		else if (arrayOfBalls[i]._physicsObject._pos.x + arrayOfBalls[i]._radius > windowWidht)
		{

			arrayOfBalls[i]._physicsObject._pos.x = windowWidht - arrayOfBalls[i]._radius;
			if (arrayOfBalls[i]._physicsObject._velocity.x > 0)
			{

				arrayOfBalls[i]._physicsObject._velocity.x *= -1.0;
				//arrayOfBalls[ballIxdex].vx += abs(amplitude * (cos(2 * 3.14 * curBorderTime / period) - cos(2 * 3.14 * curBorderTime - 1 / 60.0 / period)) * 30.0);
			}

		}

		if (arrayOfBalls[i]._physicsObject._pos.y - arrayOfBalls[i]._radius < 0)
		{
			arrayOfBalls[i]._physicsObject._pos.y = 0 + arrayOfBalls[i]._radius;
			if (arrayOfBalls[i]._physicsObject._velocity.y < 0)
			{
				arrayOfBalls[i]._physicsObject._velocity.y *= -1.0;
			}
		}
		else if (arrayOfBalls[i]._physicsObject._pos.y + arrayOfBalls[i]._radius > windowHight)
		{
			arrayOfBalls[i]._physicsObject._pos.y = windowHight - arrayOfBalls[i]._radius;
			if (arrayOfBalls[i]._physicsObject._velocity.y > 0)
			{
				arrayOfBalls[i]._physicsObject._velocity.y *= -1.0;
			}
		}
	}


	return false;
}

void PhysicsEngine::RungeKuttaStep(Ball arrayOfBalls[], int numberOfBalls, Spring arrayOfSprings[], int numberOfSprings, double delta_time)
{
	Vector2 initialpos[1000];
	Vector2 initialvel[1000];


	Vector2 k1Vel[1000];
	Vector2 k1force[1000];

	Vector2 k2Vel[1000];
	Vector2 k2force[1000];

	Vector2 k3Vel[1000];
	Vector2 k3force[1000];

	Vector2 k4Vel[1000];
	Vector2 k4force[1000];

	CalculateForces(arrayOfBalls, numberOfBalls, arrayOfSprings, numberOfSprings);

	//physics object has v and f for t=t0
	for (int i = 0; i < numberOfBalls; i++)
	{
		if (!arrayOfBalls[i]._physicsObject._isFixedPoint)
		{
			initialpos[i] = arrayOfBalls[i]._physicsObject._pos;
			initialvel[i] = arrayOfBalls[i]._physicsObject._velocity; //saving initial position and velosity

			k1force[i] = arrayOfBalls[i]._physicsObject._totalForce;
			k1Vel[i] = arrayOfBalls[i]._physicsObject._velocity;

			arrayOfBalls[i]._physicsObject._velocity = arrayOfBalls[i]._physicsObject._velocity + arrayOfBalls[i]._physicsObject._totalForce * (1.0 / arrayOfBalls[i]._physicsObject._mass) * (delta_time / 2); //now v is for t0+dt/2
			arrayOfBalls[i]._physicsObject._pos = arrayOfBalls[i]._physicsObject._pos + arrayOfBalls[i]._physicsObject._velocity * (delta_time / 2);

			arrayOfBalls[i]._physicsObject._totalForce = arrayOfBalls[i]._physicsObject._totalForce.zeroVector();
		}
	}

	//physics object have v for t0+delta/2 
	CalculateForces(arrayOfBalls, numberOfBalls, arrayOfSprings, numberOfSprings);
	//physics object have v for t0+delta/2 

	for (int i = 0; i < numberOfBalls; i++)
	{
		if (!arrayOfBalls[i]._physicsObject._isFixedPoint)
		{
			k2force[i] = arrayOfBalls[i]._physicsObject._totalForce;
			k2Vel[i] = arrayOfBalls[i]._physicsObject._velocity;

			arrayOfBalls[i]._physicsObject._pos = initialpos[i] + arrayOfBalls[i]._physicsObject._velocity * (delta_time / 2); //pos in meter cos one pixel = 1 meter
			arrayOfBalls[i]._physicsObject._velocity = initialvel[i] + arrayOfBalls[i]._physicsObject._totalForce * (1.0 / arrayOfBalls[i]._physicsObject._mass) * (delta_time / 2); // velocity in meter/sec
			arrayOfBalls[i]._physicsObject._totalForce = arrayOfBalls[i]._physicsObject._totalForce.zeroVector(); //force in kg*miter/s^2
		}
	}

	CalculateForces(arrayOfBalls, numberOfBalls, arrayOfSprings, numberOfSprings);

	//physics object have v for t0+delta/2 

	for (int i = 0; i < numberOfBalls; i++)
	{
		if (!arrayOfBalls[i]._physicsObject._isFixedPoint)
		{
			k3force[i] = arrayOfBalls[i]._physicsObject._totalForce;
			k3Vel[i] = arrayOfBalls[i]._physicsObject._velocity;

			arrayOfBalls[i]._physicsObject._pos = initialpos[i] + arrayOfBalls[i]._physicsObject._velocity * (delta_time); //pos in meter cos one pixel = 1 meter
			arrayOfBalls[i]._physicsObject._velocity = initialvel[i] + arrayOfBalls[i]._physicsObject._totalForce * (1.0 / arrayOfBalls[i]._physicsObject._mass) * (delta_time); // velocity in meter/sec
			arrayOfBalls[i]._physicsObject._totalForce = arrayOfBalls[i]._physicsObject._totalForce.zeroVector(); //force in kg*miter/s^2
		}
	}


	CalculateForces(arrayOfBalls, numberOfBalls, arrayOfSprings, numberOfSprings);

	//physics object have v for t0+delta/2 

	for (int i = 0; i < numberOfBalls; i++)
	{
		if (!arrayOfBalls[i]._physicsObject._isFixedPoint)
		{
			k4force[i] = arrayOfBalls[i]._physicsObject._totalForce;
			k4Vel[i] = arrayOfBalls[i]._physicsObject._velocity;

			arrayOfBalls[i]._physicsObject._pos = initialpos[i] + (k1Vel[i] + k2Vel[i] * 2 + k3Vel[i] * 2 + k4Vel[i]) * (delta_time / 6); //pos in meter cos one pixel = 1 meter
			arrayOfBalls[i]._physicsObject._velocity = initialvel[i] + (k1force[i] + k2force[i] * 2 + k3force[i] * 2 + k4force[i]) * (1.0 / arrayOfBalls[i]._physicsObject._mass) * (delta_time / 6); // velocity in meter/sec
			arrayOfBalls[i]._physicsObject._totalForce = arrayOfBalls[i]._physicsObject._totalForce.zeroVector(); //force in kg*miter/s^2
		}
	}
}

void PhysicsEngine::ProcessColition(Ball  &ball1, Ball &ball2)
{
	if (ball1._physicsObject._isFixedPoint)
	{
		Vector2 centerOfgravityVelocity = centerOfgravityVelocity.zeroVector();// ball1._physicsObject._velocity * -1;//or hero mayby zero is better
		Vector2 centersDirVec = ((ball1._physicsObject._pos - ball2._physicsObject._pos));
		centersDirVec.normalizeVector();
		Vector2 CopycentersDirVec = centersDirVec;

		//Vector2 ball1VelInMref = ball1._physicsObject._velocity + centerOfgravityVelocity;
		Vector2 ball2VelInMref = ball2._physicsObject._velocity + centerOfgravityVelocity;

		//ball1VelInMref = ball1VelInMref - (centersDirVec * (centersDirVec * ball1VelInMref)) * 2.0;
		ball2VelInMref = ball2VelInMref - (centersDirVec * (centersDirVec * ball2VelInMref)) * 2.0;

		ball1._physicsObject._velocity = ball1._physicsObject._velocity.zeroVector();

		ball2._physicsObject._velocity = ball2VelInMref - centerOfgravityVelocity;

		double distance = ball1._physicsObject._pos.Distance(ball2._physicsObject._pos) - (ball1._radius + ball2._radius);

		if (distance < 0)// && abs(distance)>(ball1._radius + ball2._radius)/30.0)
		{
			ball2._physicsObject._pos = ball2._physicsObject._pos + CopycentersDirVec * (distance);
		}
	}
	else if (ball2._physicsObject._isFixedPoint)
	{
		Vector2 centerOfgravityVelocity = Vector2(0,0);
		Vector2 centersDirVec = ((ball1._physicsObject._pos - ball2._physicsObject._pos));
		centersDirVec.normalizeVector();
		Vector2 CopycentersDirVec = centersDirVec;
		centersDirVec.normalizeVector();
		Vector2 ball1VelInMref = ball1._physicsObject._velocity + centerOfgravityVelocity;

		ball1VelInMref = ball1VelInMref - (centersDirVec * (centersDirVec * ball1VelInMref)) * 2.0;

		ball1._physicsObject._velocity = ball1VelInMref - centerOfgravityVelocity;

		ball2._physicsObject._velocity = Vector2(0,0);

		double distance = ball1._physicsObject._pos.Distance(ball2._physicsObject._pos) - (ball1._radius + ball2._radius);
		if (distance < 0)// && abs(distance)>(ball1._radius + ball2._radius)/30.0)
		{
			ball1._physicsObject._pos = ball1._physicsObject._pos - CopycentersDirVec * (distance);
		}
	}
	else
	{
		Vector2 centerOfgravityVelocity = Vector2(-(ball1._physicsObject._mass * ball1._physicsObject._velocity.x + ball2._physicsObject._mass * ball2._physicsObject._velocity.x) / (ball1._physicsObject._mass + ball2._physicsObject._mass), -(ball1._physicsObject._mass * ball1._physicsObject._velocity.y + ball2._physicsObject._mass * ball2._physicsObject._velocity.y) / (ball1._physicsObject._mass + ball2._physicsObject._mass));
		Vector2 centersDirVec = ((ball1._physicsObject._pos - ball2._physicsObject._pos));
		centersDirVec.normalizeVector();
		Vector2 CopycentersDirVec = centersDirVec;
		centersDirVec.normalizeVector();
		Vector2 ball1VelInMref = ball1._physicsObject._velocity + centerOfgravityVelocity;
		Vector2 ball2VelInMref = ball2._physicsObject._velocity + centerOfgravityVelocity;

		ball1VelInMref = ball1VelInMref - (centersDirVec * (centersDirVec * ball1VelInMref)) * 2.0;
		ball2VelInMref = ball2VelInMref - (centersDirVec * (centersDirVec * ball2VelInMref)) * 2.0;

		ball1._physicsObject._velocity = ball1VelInMref - centerOfgravityVelocity;

		ball2._physicsObject._velocity = ball2VelInMref - centerOfgravityVelocity;

		double distance = ball1._physicsObject._pos.Distance(ball2._physicsObject._pos) - (ball1._radius + ball2._radius);
		if (distance < 0)// && abs(distance)>(ball1._radius + ball2._radius)/30.0)
		{
			ball1._physicsObject._pos = ball1._physicsObject._pos - CopycentersDirVec * (distance * ball2._physicsObject._mass / (ball1._physicsObject._mass + ball2._physicsObject._mass));
			ball2._physicsObject._pos = ball2._physicsObject._pos + CopycentersDirVec * (distance * ball1._physicsObject._mass / (ball1._physicsObject._mass + ball2._physicsObject._mass));
		}
	}
	
	
		/*else
		{
			ball1._physicsObject._pos = ball1._physicsObject._pos - CopycentersDirVec * (distance * ball2._physicsObject._mass / (ball1._physicsObject._mass + ball2._physicsObject._mass));
			ball2._physicsObject._pos = ball2._physicsObject._pos + CopycentersDirVec * (distance * ball1._physicsObject._mass / (ball1._physicsObject._mass + ball2._physicsObject._mass));
		}*/
}

Matrix PhysicsEngine::CalculateConstrainForces(Ball arrayOfBalls[], int numberOfBalls, LinearConstraint arrayOfConstraints[], int numberOfConstrtain)
{
	//JWJ^t*x = -Jdot*qdot-JWQ - ks*C - kd*Cdot the last part with C 

	//evaluate J and Jdot 2n*m
	// q 1*2n

	Matrix* arrayJ = new Matrix[numberOfConstrtain];
	Matrix* arrayJdot = new Matrix[numberOfConstrtain];
	for (int i = 0; i < numberOfConstrtain; i++)
	{
		arrayJ[i] = arrayOfConstraints[i].EvaluateJacobian(numberOfBalls);
		arrayJdot[i] = arrayOfConstraints[i].EvaluateJacobianTimeDerivative(numberOfBalls);
	}
	Matrix J = J.ConcatenateMatrix(arrayJ, numberOfConstrtain, 1, numberOfBalls);
	Matrix Jdot = Jdot.ConcatenateMatrix(arrayJ, numberOfConstrtain, 1, numberOfBalls);

	//need to construct the Q matrix
	Matrix Q = Matrix(2*numberOfBalls,1);

	//need to construct matrix of velocities qdot
	Matrix qdot = Matrix(2 * numberOfBalls, 1);


	Matrix W = Matrix(2 * numberOfBalls, 2*numberOfBalls);
	for (int i = 0; i < W.rows_; i++)
	{
		if (i % 2 == 0)
		{
			Q.p[i][1] = arrayOfBalls[i / 2]._physicsObject._totalForce.x;
			qdot.p[2 * i + 1][1] = arrayOfBalls[i / 2]._physicsObject._velocity.x;
		}
		else
		{
			Q.p[i + 1][1] = arrayOfBalls[i / 2]._physicsObject._totalForce.y;
			qdot.p[2 * i + 1][1] = arrayOfBalls[i / 2]._physicsObject._velocity.y;
		}

		for (int j = 0; j < W.cols_; j++)
		{
			if (i == j)
			{
				W.p[i][j] = 1 / arrayOfBalls[i/2]._physicsObject._mass;
			}
		}
	}

	//now we forme the matrix A and be of our equation Ax=B

	Matrix A = (J * W).MatrixMultiplyByMatrixTransform(J);
	Matrix B = -1 * Jdot * qdot - 1 * J * W * Q;

	return A;

}
