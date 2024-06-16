#include "GraphicsSystem.h"
#include "Window.h"
#include "SDL_image.h"

GraphicsSystem::GraphicsSystem(const std::string& title, int width, int height,const std::string& image_path):
_window(title, width, height)
{

	//Should load all the texture for the project
	auto surface = IMG_Load(image_path.c_str());

	if (!surface)
	{
		std::cerr << "Failed to creat surface.\n";
	}

	_ballTexture = SDL_CreateTextureFromSurface(_window._renderer, surface);
	if (!_ballTexture)
	{
		std::cerr << "Failed to create ball texture.\n";
	}

	SDL_FreeSurface(surface);
}

void GraphicsSystem::DrawCircle(int32_t centreX, int32_t centreY, int32_t radius)
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
		SDL_RenderDrawPoint(_window._renderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(_window._renderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(_window._renderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(_window._renderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(_window._renderer, centreX + y, centreY - x);
		SDL_RenderDrawPoint(_window._renderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(_window._renderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(_window._renderer, centreX - y, centreY + x);

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

void GraphicsSystem::DrawImage(int w, int h, Vector2 pos)
{
	SDL_Rect rect = {pos.x- w, pos.y- h, 2*w, 2*h };
	SDL_RenderCopy(_window._renderer, _ballTexture, nullptr, &rect);
}

void GraphicsSystem::Update()
{
	_window.PollEvent();
}

void GraphicsSystem::Render(Ball arrayOfBalls[], int numberOfBalls, Spring arrayOfSprings[], int numberOfSprings)
{
	SDL_RenderClear(_window._renderer);
	//for (int i = 0; i < numberOfBalls; i++)
	//{
	//	//SDL_SetRenderDrawColor(_window._renderer, 255, 0, 255, 255);
	//	//DrawImage(arrayOfBalls[i]._radius, arrayOfBalls[i]._radius, arrayOfBalls[i]._physicsObject._pos);
	//	//DrawCircle(arrayOfBalls[i]._physicsObject._pos.x, arrayOfBalls[i]._physicsObject._pos.y, arrayOfBalls[i]._radius);
	//}

	//for (int i = 0; i < numberOfSprings; i++)
	//{
	//	SDL_SetRenderDrawColor(_window._renderer, 255, 0, 0, 255);
	//	DrawSpring(arrayOfSprings[i]._connectionPoint1->_pos, arrayOfSprings[i]._connectionPoint2->_pos);
	//}

	//SDL_SetRenderDrawColor(_window._renderer, 255, 255, 255, 255);
	SDL_RenderPresent(_window._renderer);
}

GraphicsSystem::~GraphicsSystem()
{
	SDL_DestroyTexture(_ballTexture); 
}

GraphicsSystem::GraphicsSystem()
{

}

void GraphicsSystem::DrawSpring(Vector2 point1, Vector2 point2)
{
	SDL_RenderDrawLineF(_window._renderer, point1.x, point1.y, point2.x, point2.y);
}