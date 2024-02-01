#include "Game.h"

Game::Game()
{
}

Game::~Game()
{

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	delta_time = 0.01;
	int flag = 0;

	if (fullscreen)
	{
		flag = SDL_WINDOW_FULLSCREEN;

	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "subsystem initalised" << std::endl;
		window = SDL_CreateWindow("title", xpos, ypos, width, height, flag);
		if (window)
		{
			std::cout << "window creatred" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer creatred" << std::endl;
		}

		RandomSpawnBalls();
		isRuning = true;
	}
	else
	{
		isRuning = false;
	}
}

void Game::update()
{
	CheckForColitions();
	for (int i = 0; i < numOfBall; i++)
	{
		Move(i);
	}
	//std::cout << borderX << std::endl;
	//SDL_Delay(4);
}

void Game::handeleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT: isRuning = false;

	default:
		break;
	}
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "game quited" << std::endl;

}

void Game::render()
{
	

	for (int i = 0; i < numOfBall; i++)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
		DrawCircle(renderer, (int)ballsArrey[i].pos.x, (int)ballsArrey[i].pos.y, ballsArrey[i].radius);
		
	}
	SDL_RenderDrawLineF(renderer, borderX, 0, borderX, 900);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}

void Game::DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}

void Game::Move(int ballIxdex)
{
	int windowHight;
	int windowWidht;
	SDL_GetWindowSize(window, &windowWidht, &windowHight);

	//float vx = (rand() % 100) / 100.0 * 20.0 - 10;
	//float vy = (rand() % 100) / 100.0 * 20.0 - 10;
	////std::cout << vx << std::endl;
	//ballsArrey[ballIxdex].vy = vy;
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

void Game::RandomSpawnBalls()
{
	int windowHight;
	int windowWidht;
	SDL_GetWindowSize(window, &windowWidht, &windowHight);
	int colitionBalIndex;
	int maxradius = 30;
	for (int i = 0; i < NUMBEROFBALLS; i++)
	{
		do
		{
			double x = (rand() % 100) / 100.0 * windowWidht;
			double y = (rand() % 100) / 100.0 * windowHight;
			double vx = (rand() % 100) / 100.0 * 50 - 5;
			double vy = (rand() % 100) / 100.0 * 50 - 5;


			int radius = (rand() % 100) / 100.0 * maxradius + 5;
			std::cout << radius << std::endl;
			//ballsArrey[i] 
			Ball *ball = new Ball(10, Vector2(vx, vy), Vector2(x, y),10* radius / maxradius);

			ballsArrey[i] = *ball;
			

		} while (false);

		numOfBall++;
	}

	/*Ball ball1 = Ball(20, Vector2(4, 0), Vector2(50, 100), 10);
	Ball ball2 = Ball(20, Vector2(-4, 0), Vector2(500, 100), 10);
	ballsArrey[0] = ball1;
	ballsArrey[1] = ball2;
	numOfBall = 2;*/
}

float Game::Distance(Vector2 pos1, Vector2 pos2)
{
	return sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
}

bool Game::CheckForColitions()
{
	for (int i = 0; i < numOfBall; i++)
	{
		for (int j = i + 1; j < numOfBall; j++)
		{
			//std::cout << "colision" << std::endl;
			if (Distance(ballsArrey[i].pos, ballsArrey[j].pos) <= (ballsArrey[i].radius + ballsArrey[j].radius))
			{

				ProcessColition(ballsArrey[i], ballsArrey[j]);
				//perform colision
				
			}
		}
	}
	return false;
}

void Game::ProcessColition(Ball  &ball1, Ball &ball2)
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

	double distance = Distance(ball1.pos, ball2.pos) - (ball1.radius + ball2.radius);
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