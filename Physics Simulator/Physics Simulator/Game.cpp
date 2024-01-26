#include "Game.h"

Game::Game()
{
}

Game::~Game()
{

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
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
	for (int i = 0; i < numOfBall; i++)
	{
		Move(i);
	}

	curBorderTime += 1 / 60.0;
	borderX = amplitude*cos(2 * 3.14 * curBorderTime / period)+ amplitude;

	if (curBorderTime > period) curBorderTime = 0;
	//std::cout << borderX << std::endl;
	SDL_Delay(18);
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
		DrawCircle(renderer, (int)ballsArrey[i].x, (int)ballsArrey[i].y, ballsArrey[i].radius);
		
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
	if (abs(ballsArrey[ballIxdex].vx) > 15)
	{
		ballsArrey[ballIxdex].vx = abs(ballsArrey[ballIxdex].vx) / ballsArrey[ballIxdex].vx * 15.0;
	}

	if (abs(ballsArrey[ballIxdex].vy) > 15)
	{
		ballsArrey[ballIxdex].vy = abs(ballsArrey[ballIxdex].vy) / ballsArrey[ballIxdex].vy * 15.0;
	}
	int windowHight;
	int windowWidht;
	SDL_GetWindowSize(window, &windowWidht, &windowHight);

	//float vx = (rand() % 100) / 100.0 * 20.0 - 10;
	//float vy = (rand() % 100) / 100.0 * 20.0 - 10;
	////std::cout << vx << std::endl;
	//ballsArrey[ballIxdex].vy = vy;
	ballsArrey[ballIxdex].x += ballsArrey[ballIxdex].vx;
	ballsArrey[ballIxdex].y += ballsArrey[ballIxdex].vy;

	if (ballsArrey[ballIxdex].x - ballsArrey[ballIxdex].radius < borderX)
	{
		ballsArrey[ballIxdex].x = borderX + ballsArrey[ballIxdex].radius;
		if (ballsArrey[ballIxdex].vx < 0)
		{
			
			ballsArrey[ballIxdex].vx *= -1.0;
			ballsArrey[ballIxdex].vx += abs(amplitude * (cos(2 * 3.14 * curBorderTime / period)- cos(2 * 3.14 * curBorderTime-1/60.0 / period))*30.0);
		}
	}
	else if (ballsArrey[ballIxdex].x + ballsArrey[ballIxdex].radius > windowWidht)
	{
		float x = (rand() % 100) / 100.0 * windowWidht + borderX;
		float y = (rand() % 100) / 100.0 * windowHight;
		float vx;
		if ((rand() % 100) / 100.0 > 0.5)
		{
			vx = 10;
		}
		else vx = -10;
		float vy = (rand() % 100) / 100.0 * 15.0 - 5;
		ballsArrey[ballIxdex].x = x;
		ballsArrey[ballIxdex].y = y;
		ballsArrey[ballIxdex].vx = vx;
		ballsArrey[ballIxdex].vy = vy;
	}

	if (ballsArrey[ballIxdex].y - ballsArrey[ballIxdex].radius < 0)
	{
		ballsArrey[ballIxdex].y -= ballsArrey[ballIxdex].vy;
		ballsArrey[ballIxdex].vy *= -1.0;
	}
	else if (ballsArrey[ballIxdex].y + ballsArrey[ballIxdex].radius > windowHight)
	{
		ballsArrey[ballIxdex].y -= ballsArrey[ballIxdex].vy;
		ballsArrey[ballIxdex].vy *= -1.0;
	}
}

void Game::RandomSpawnBalls()
{
	int windowHight;
	int windowWidht;
	SDL_GetWindowSize(window, &windowWidht, &windowHight);
	int colitionBalIndex;
	int maxradius = 7;
	for (int i = 0; i < NUMBEROFBALLS; i++)
	{
		do
		{
			float x = (rand() % 100) / 100.0 * windowWidht;
			float y = (rand() % 100) / 100.0 * windowHight;
			float vx;
			if ((rand() % 100) / 100.0 > 0.5)
			{
				vx = 15;
			}
			else vx = -15;
			float vy = (rand() % 100) / 100.0 * 15.0 - 5;

			int radius = (rand() % 100) / 100.0 * maxradius + 2;
			std::cout << radius << std::endl;
			//ballsArrey[i] 
			Ball *ball = new Ball(2, vx,vy, x, y);

			ballsArrey[i] = *ball;
			

		} while (CheckForColitions(i, &colitionBalIndex));

		numOfBall++;
	}
}

bool Game::CheckForColitions(int ballIndex, int* colitionBallIndex)
{
	return false;
}

//void Game::lenearInterpolation(int ballIndex, int bounderyX)
//{
//	if(ballsArrey[ballIndex].x + ballsArrey[ballIndex].vx < bounderyX)
//}