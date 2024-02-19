#pragma once

#include <string>
#include <SDL_image.h>
#include "SDL.h"

class Window
{
public:
	Window(const std::string& title, int width, int height);
	Window();
	~Window();
	inline bool isClosed() const { return _closed; };
	void PollEvent();


	
private:
	bool init();
	
public:
	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;

private:
	std::string _title;
	int _widht = 800;
	int _height=600;

	bool _closed = false;
};