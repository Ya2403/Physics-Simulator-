#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{

}

void PhysicsEngine::update()
{
	CheckForColitions();
	for (int i = 0; i < numOfBall; i++)
	{
		Move(i);
	}
	//std::cout << borderX << std::endl;
	//SDL_Delay(4);
}

void PhysicsEngine::Move(int ballIxdex)
{
	int windowHight=500;
	int windowWidht= 500;

	ballsArrey[ballIxdex].pos = ballsArrey[ballIxdex].pos+ballsArrey[ballIxdex].velocity* delta_time;

	if (ballsArrey[ballIxdex].pos.x - ballsArrey[ballIxdex].radius < 0)
	{
		ballsArrey[ballIxdex].pos.x = 0 + ballsArrey[ballIxdex].radius;
		if (ballsArrey[ballIxdex].velocity.x < 0)
		{
			
			ballsArrey[ballIxdex].velocity.x *= -1.0;
			//ballsArrey[ballIxdex].vx += abs(amplitude * (cos(2 * 3.14 * curBorderTime / period)- cos(2 * 3.14 * curBorderTime-1/60.0 / period))*30.0);
		}
	}
	else if (ballsArrey[ballIxdex].pos.x + ballsArrey[ballIxdex].radius > windowWidht)
	{

		ballsArrey[ballIxdex].pos.x = windowWidht - ballsArrey[ballIxdex].radius;
		if (ballsArrey[ballIxdex].velocity.x > 0)
		{

			ballsArrey[ballIxdex].velocity.x *= -1.0;
			//ballsArrey[ballIxdex].vx += abs(amplitude * (cos(2 * 3.14 * curBorderTime / period) - cos(2 * 3.14 * curBorderTime - 1 / 60.0 / period)) * 30.0);
		}
		
	}

	if (ballsArrey[ballIxdex].pos.y - ballsArrey[ballIxdex].radius < 0)
	{
		ballsArrey[ballIxdex].pos.y = 0+ ballsArrey[ballIxdex].radius;
		if (ballsArrey[ballIxdex].velocity.y < 0)
		{
			ballsArrey[ballIxdex].velocity.y *= -1.0;
		}
	}
	else if (ballsArrey[ballIxdex].pos.y + ballsArrey[ballIxdex].radius > windowHight)
	{
		ballsArrey[ballIxdex].pos.y = windowHight - ballsArrey[ballIxdex].radius;
		if (ballsArrey[ballIxdex].velocity.y > 0)
		{
			ballsArrey[ballIxdex].velocity.y *= -1.0;
		}
		
	}
}


bool PhysicsEngine::CheckForColitions()
{
	for (int i = 0; i < numOfBall; i++)
	{
		for (int j = i + 1; j < numOfBall; j++)
		{
			//std::cout << "colision" << std::endl;
			if (ballsArrey[i].pos.Distance(ballsArrey[j].pos) <= (ballsArrey[i].radius + ballsArrey[j].radius))
			{

				ProcessColition(ballsArrey[i], ballsArrey[j]);
				//perform colision
				
			}
		}
	}
	return false;
}

void PhysicsEngine::ProcessColition(Ball  &ball1, Ball &ball2)
{
	Vector2 centerOfgravityVelocity = Vector2(-(ball1.mass * ball1.velocity.x + ball2.mass * ball2.velocity.x) / (ball1.mass + ball2.mass), -(ball1.mass * ball1.velocity.y + ball2.mass * ball2.velocity.y) / (ball1.mass + ball2.mass));
	Vector2 centersDirVec = ((ball1.pos - ball2.pos));
	centersDirVec.normalizeVector();
	Vector2 CopycentersDirVec = centersDirVec;
	centersDirVec.normalizeVector();
	Vector2 ball1VelInMref = ball1.velocity + centerOfgravityVelocity;
	Vector2 ball2VelInMref = ball2.velocity + centerOfgravityVelocity;

	ball1VelInMref = ball1VelInMref - (centersDirVec*(centersDirVec * ball1VelInMref))*2.0;
	ball2VelInMref = ball2VelInMref - (centersDirVec * (centersDirVec * ball2VelInMref))*2.0;

	ball1.velocity = ball1VelInMref - centerOfgravityVelocity;
	
	ball2.velocity = ball2VelInMref - centerOfgravityVelocity;

	double distance = ball1.pos.Distance(ball2.pos) - (ball1.radius + ball2.radius);
	if (distance<0)// && abs(distance)>(ball1.radius + ball2.radius)/30.0)
	{
		ball1.pos = ball1.pos - CopycentersDirVec * (distance * ball2.mass / (ball1.mass + ball2.mass));
		ball2.pos = ball2.pos + CopycentersDirVec * (distance * ball1.mass / (ball1.mass + ball2.mass));
	}
}

//void Game::lenearInterpolation(int ballIndex, int bounderyX)
//{
//	if(ballsArrey[ballIndex].x + ballsArrey[ballIndex].vx < bounderyX)
//}