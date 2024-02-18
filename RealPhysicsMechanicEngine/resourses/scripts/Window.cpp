#include "Window.h"
#include <iostream>



Window::Window(const std::string& title, int width, int height) :
_title(title), _widht(width), _height(height)
{
	if (!(init()))
	{
		_closed = true;
	}
}

Window::~Window()
{
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

bool Window::init()
{
	/*if (fullscreen)
	{
		flag = SDL_WINDOW_FULLSCREEN;
	}*/

	if ((SDL_Init(SDL_INIT_EVERYTHING)) != 0)
	{
		std::cerr << "failed to initalise subsystem" << std::endl;
		return 0;
	}
	
	_window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _widht, _height, 0);

	if (_window == nullptr)
	{
		std::cerr << "failed to create window" << std::endl;
		return 0;
	}

	_renderer = SDL_CreateRenderer(_window, -1, 0);
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

	if (_renderer == nullptr)
	{
		
		std::cout << "failed to create renderer" << std::endl;
	}
	
	return true;
}

void Window::PollEvent()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_closed = true;
			break;
		default:
			break;
		}
	}
}