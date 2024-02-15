#pragma once
#include "Window.h"
#include <string>


class GraphicsSystem {
public:
	GraphicsSystem(const std::string& title, int width, int height);
	~GraphicsSystem();
	inline bool isRuning() const {return _window.isClosed();};
	void DrawCircle(int32_t centreX, int32_t centreY, int32_t radius);



private:
	Window _window;
	SDL_Renderer* _renderer = nullptr;
};