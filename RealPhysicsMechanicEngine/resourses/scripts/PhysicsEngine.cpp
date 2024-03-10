#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{

}

void PhysicsEngine::update(Ball arrayOfBalls[], int numberOfBalls, Spring arrayOfSprings[], int numberOfSprings, double delta_time)
{
	double energy = 0;
	//check for colition
	//CheckForColitions(arrayOfBalls, numberOfBalls);

	Vector2 initialpos[1000];
	Vector2 initialvel[1000];
	//std::copy(arrayOfBalls, arrayOfBalls + numberOfBalls, newArrayOfBalls);
	for (int j = 0; j < numberOfSprings; j++)
	{
		arrayOfSprings[j].Update();//update connected springs
	}

	for (int j = 1; j < numberOfBalls; j++)
	{
		arrayOfBalls[j]._physicsObject.AddForce(Vector2(0, gravity * arrayOfBalls[j]._physicsObject._mass));
	}

	//physics object has v and f for t=t0
	for (int i = 0; i < numberOfBalls; i++)
	{
		initialpos[i] = arrayOfBalls[i]._physicsObject._pos;
		initialvel[i] = arrayOfBalls[i]._physicsObject._velocity; //saving initial position and velosity
		arrayOfBalls[i]._physicsObject._velocity = arrayOfBalls[i]._physicsObject._velocity + arrayOfBalls[i]._physicsObject._totalForce * (1.0 / arrayOfBalls[i]._physicsObject._mass)* (delta_time / 2); //now v is for t0+dt/2
		arrayOfBalls[i]._physicsObject._pos = arrayOfBalls[i]._physicsObject._pos + arrayOfBalls[i]._physicsObject._velocity * (delta_time / 2);

		arrayOfBalls[i]._physicsObject._totalForce = arrayOfBalls[i]._physicsObject._totalForce.zeroVector();
	}

	//physics object have v for t0+delta/2 
	for (int j = 0; j < numberOfSprings; j++)
	{
		arrayOfSprings[j].Update();//update connected springs
	}

	for (int j = 1; j < numberOfBalls; j++)
	{
		arrayOfBalls[j]._physicsObject.AddForce(Vector2(0, gravity * arrayOfBalls[j]._physicsObject._mass));
	}
	//physics object have v for t0+delta/2 

	for (int i = 0; i < numberOfBalls; i++)
	{
		arrayOfBalls[i]._physicsObject._pos = initialpos[i];
		//initialvel[i] = arrayOfBalls[i]._physicsObject._velocity;
	}

	for (int i = 0; i < numberOfBalls; i++)
	{
		arrayOfBalls[i]._physicsObject._pos = initialpos[i] + arrayOfBalls[i]._physicsObject._velocity * delta_time; //pos in meter cos one pixel = 1 meter
		arrayOfBalls[i]._physicsObject._velocity = initialvel[i] + arrayOfBalls[i]._physicsObject._totalForce * (1.0 / arrayOfBalls[i]._physicsObject._mass) * delta_time; // velocity in meter/sec
		arrayOfBalls[i]._physicsObject._totalForce = arrayOfBalls[i]._physicsObject._totalForce.zeroVector(); //force in kg*miter/s^2
	}

	curr_Time += delta_time;

	if (arrayOfBalls[1]._physicsObject._velocity.getMag() < 1)
	{
		std::cout << curr_Time << std::endl;
	}



	for (int i = 0; i < numberOfBalls; i++)
	{
		if (i >0)
		{
			energy += arrayOfBalls[i]._physicsObject._mass * pow(arrayOfBalls[i]._physicsObject._velocity.getMag(), 2);
			energy += -2 * arrayOfBalls[i]._physicsObject._mass * gravity * arrayOfBalls[i]._physicsObject._pos.y;
		}
	}

	//for (int i = 0; i < numberOfSprings; i++)
	//{
	//	energy += arrayOfSprings[i]._stiffness * pow(arrayOfSprings[i]._connectionPoint1->_pos.Distance(arrayOfSprings[i]._connectionPoint2->_pos) - arrayOfSprings[i]._initianLenght, 2);
	//}


	std::cout << energy << std::endl;
	
	

	
	//SDL_Delay(4);
}

bool PhysicsEngine::CheckForColitions(Ball arrayOfBalls[], int numberOfBalls )
{
	int windowHight = 1000;
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

void PhysicsEngine::ProcessColition(Ball  &ball1, Ball &ball2)
{
	Vector2 centerOfgravityVelocity = Vector2(-(ball1._physicsObject._mass * ball1._physicsObject._velocity.x + ball2._physicsObject._mass * ball2._physicsObject._velocity.x) / (ball1._physicsObject._mass + ball2._physicsObject._mass), -(ball1._physicsObject._mass * ball1._physicsObject._velocity.y + ball2._physicsObject._mass * ball2._physicsObject._velocity.y) / (ball1._physicsObject._mass + ball2._physicsObject._mass));
	Vector2 centersDirVec = ((ball1._physicsObject._pos - ball2._physicsObject._pos));
	centersDirVec.normalizeVector();
	Vector2 CopycentersDirVec = centersDirVec;
	centersDirVec.normalizeVector();
	Vector2 ball1VelInMref = ball1._physicsObject._velocity + centerOfgravityVelocity;
	Vector2 ball2VelInMref = ball2._physicsObject._velocity + centerOfgravityVelocity;

	ball1VelInMref = ball1VelInMref - (centersDirVec*(centersDirVec * ball1VelInMref))*2.0;
	ball2VelInMref = ball2VelInMref - (centersDirVec * (centersDirVec * ball2VelInMref))*2.0;

	ball1._physicsObject._velocity = ball1VelInMref - centerOfgravityVelocity;
	
	ball2._physicsObject._velocity = ball2VelInMref - centerOfgravityVelocity;

	double distance = ball1._physicsObject._pos.Distance(ball2._physicsObject._pos) - (ball1._radius + ball2._radius);
	if (distance<0)// && abs(distance)>(ball1._radius + ball2._radius)/30.0)
	{
		ball1._physicsObject._pos = ball1._physicsObject._pos - CopycentersDirVec * (distance * ball2._physicsObject._mass / (ball1._physicsObject._mass + ball2._physicsObject._mass));
		ball2._physicsObject._pos = ball2._physicsObject._pos + CopycentersDirVec * (distance * ball1._physicsObject._mass / (ball1._physicsObject._mass + ball2._physicsObject._mass));
	}
}

//void Game::lenearInterpolation(int ballIndex, int bounderyX)
//{
//	if(arrayOfBalls[ballIndex].x + arrayOfBalls[ballIndex].vx < bounderyX)
//}