#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{

}

void PhysicsEngine::update(Ball arrayOfBalls[], int numberOfBalls)
{
	CheckForColitions(arrayOfBalls, numberOfBalls);
	for (int i = 0; i < numberOfBalls; i++)
	{
		Move(arrayOfBalls,i);
	}
	//std::cout << borderX << std::endl;
	//SDL_Delay(4);
}

void PhysicsEngine::Move(Ball arrayOfBalls[], int ballIxdex)
{
	int windowHight = 500;
	int windowWidht = 500;

	arrayOfBalls[ballIxdex]._physicsObject._pos = arrayOfBalls[ballIxdex]._physicsObject._pos+arrayOfBalls[ballIxdex]._physicsObject._velocity* delta_time;

	if (arrayOfBalls[ballIxdex]._physicsObject._pos.x - arrayOfBalls[ballIxdex]._radius < 0)
	{
		arrayOfBalls[ballIxdex]._physicsObject._pos.x = 0 + arrayOfBalls[ballIxdex]._radius;
		if (arrayOfBalls[ballIxdex]._physicsObject._velocity.x < 0)
		{
			
			arrayOfBalls[ballIxdex]._physicsObject._velocity.x *= -1.0;
			//arrayOfBalls[ballIxdex].vx += abs(amplitude * (cos(2 * 3.14 * curBorderTime / period)- cos(2 * 3.14 * curBorderTime-1/60.0 / period))*30.0);
		}
	}
	else if (arrayOfBalls[ballIxdex]._physicsObject._pos.x + arrayOfBalls[ballIxdex]._radius > windowWidht)
	{

		arrayOfBalls[ballIxdex]._physicsObject._pos.x = windowWidht - arrayOfBalls[ballIxdex]._radius;
		if (arrayOfBalls[ballIxdex]._physicsObject._velocity.x > 0)
		{

			arrayOfBalls[ballIxdex]._physicsObject._velocity.x *= -1.0;
			//arrayOfBalls[ballIxdex].vx += abs(amplitude * (cos(2 * 3.14 * curBorderTime / period) - cos(2 * 3.14 * curBorderTime - 1 / 60.0 / period)) * 30.0);
		}
		
	}

	if (arrayOfBalls[ballIxdex]._physicsObject._pos.y - arrayOfBalls[ballIxdex]._radius < 0)
	{
		arrayOfBalls[ballIxdex]._physicsObject._pos.y = 0+ arrayOfBalls[ballIxdex]._radius;
		if (arrayOfBalls[ballIxdex]._physicsObject._velocity.y < 0)
		{
			arrayOfBalls[ballIxdex]._physicsObject._velocity.y *= -1.0;
		}
	}
	else if (arrayOfBalls[ballIxdex]._physicsObject._pos.y + arrayOfBalls[ballIxdex]._radius > windowHight)
	{
		arrayOfBalls[ballIxdex]._physicsObject._pos.y = windowHight - arrayOfBalls[ballIxdex]._radius;
		if (arrayOfBalls[ballIxdex]._physicsObject._velocity.y > 0)
		{
			arrayOfBalls[ballIxdex]._physicsObject._velocity.y *= -1.0;
		}
		
	}
}


bool PhysicsEngine::CheckForColitions(Ball arrayOfBalls[], int numberOfBalls )
{
	for (int i = 0; i < numberOfBalls; i++)
	{
		for (int j = i + 1; j < numberOfBalls; j++)
		{
			//std::cout << "colision" << std::endl;
			if (arrayOfBalls[i]._physicsObject._pos.Distance(arrayOfBalls[j]._physicsObject._pos) <= (arrayOfBalls[i]._radius + arrayOfBalls[j]._radius))
			{

				ProcessColition(arrayOfBalls[i], arrayOfBalls[j]);
				//perform colision
				
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