#pragma once

#include <string>
#include "SDL.h"

class Window
{
public:
	Window(const std::string& title, int width, int height);
	~Window();
	inline bool isClosed() const { return _closed; };
	
private:
	bool init();

private:
	std::string _title;
	int _widht = 800;
	int _hieght=600;

	bool _closed = false;

	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;
};