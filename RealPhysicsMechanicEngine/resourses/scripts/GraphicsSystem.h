#pragma once
#include "Window.h"
#include <string>
#include "Ball.h"
//#include <SDL_image.h>
#include "Spring.h"
class GraphicsSystem {
public:
	GraphicsSystem(const std::string& title, int width, int height, const std::string& image_path);
	GraphicsSystem();
	~GraphicsSystem();
	inline bool isRuning() const {return _window.isClosed();};
	void DrawCircle(int32_t centreX, int32_t centreY, int32_t radius);
	void DrawImage(int w, int h, Vector2 pos);
	void DrawSpring(Vector2 point1, Vector2 point2);
	void Clean();
	void Render(Ball arrayOfBalls[], int numberOfBalls, Spring arrayOfSprings[], int numberOfSprings);
	void Update();



private:
	Window _window;
//	SDL_Texture *_ballTexture = nullptr;

};