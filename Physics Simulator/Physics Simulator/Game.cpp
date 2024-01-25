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
		isRuning = true;
	}
	else
	{
		isRuning = false;
	}
}

void Game::update()
{
	Move();
	cnt++;
	std::cout << cnt << std::endl;
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
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	DrawCircle(renderer, x, y, 20);
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

void Game::Move()
{
	int radius = 20;
	int windowHight;
	int windowWidht;
	SDL_GetWindowSize(window, &windowWidht, &windowHight);
	x += velocityX;
	y += velocityY;

	if (x - radius < 0)
	{
		x -= velocityX;
		velocityX *= -1;
	}else if(x + radius > windowWidht)
	{
		x -= velocityX;
		velocityX *= -1;
	}

	if (y - radius < 0)
	{
		y -= velocityY;
		velocityY *= -1;
	}
	else if (y + radius > windowHight)
	{
		y -= velocityY;
		velocityY *= -1;
	}
		
		
	
}