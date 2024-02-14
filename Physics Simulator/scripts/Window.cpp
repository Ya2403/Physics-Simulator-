#include "Window.h"

Window::Window(const std::string& title, int width, int height) :
_title(title), _widht(width), _height(height)
{
	if (!init)
	{
		closed = true;
	}
}

Window::~Window()
{
	SDL_DestroyWindow();
	SDL_Quit();
}

bool Window::init()
{
	if (fullscreen)
	{
		flag = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "failed to initalise subsystem" << std::endl;
		return 0;
	}
	
	_window = SDL_CreateWindow(_title.c_str, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _widht, _height, flag);

	if (_window == nullptr)
	{
		std::cerr << "failed to create window" << std::endl;
		return 0;
	}
	
	return true;



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