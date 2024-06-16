#include "SDL.h"
#include "PhysicsEngine.h"
#include "GraphicsSystem.h"
#include "Window.h"
#include "Ball.h"
#include "SDL.h"
#include "iostream"


#include <SDL.h>

int main(int argc, char** argv)
{
    // variables

    bool quit = false;
    SDL_Event event;

    // init SDL

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("SDL2 line drawing",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // handle events

    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    bool drawing = false;
    while (!quit)
    {
        
        //SDL_Delay(10);
        SDL_PollEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                x1 = event.motion.x;
                y1 = event.motion.y;
                x2 = event.motion.x;
                y2 = event.motion.y;
                drawing = true;
                cout << "leftdown"<<'\n';
                cout << drawing << '\n';
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                drawing = false;
                cout << "leftup";
                break;
                
            }
            break;
        case SDL_MOUSEMOTION:
            if (drawing)
            {
                x2 = event.motion.x;
                y2 = event.motion.y;
                cout << "move";
            }
            break;
            // TODO input handling code goes here
        }

        

        // clear window

        SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        if (drawing)
        {
            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        }
        // TODO rendering code goes here

        // render window

        SDL_RenderPresent(renderer);
    }

    // cleanup SDL

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

//int main(int argc, char* argv[])
//{
//	/*
//	* it should be like two in one engine
//	*cause physics shouldn't be able to drawit should be like two in one engine
//	* I guess it might be like physics has all the coords in it and maybe cause physics shouldn't be able to draw
//	*object it self should have physiscs component and graphics one and so the
//	* I guess it might be like physics has all the coords in it and maybe
//	*object it self should have physiscs component and graphics one and so
//	* it will be like even without graphics I should be	able to get some like x(t) graphs or something
//	*/
//	clock_t start, end;
//
//	start = clock();
//	PhysicsEngine physics = PhysicsEngine();
//	GraphicsSystem graphics = GraphicsSystem("test", 1600, 800, "C:/projects/physicsSimulator/RealPhysicsMechanicEngine/resourses/images/a.png");
//
//
//	Ball arrayOfBalls[20];
//	Spring arrayOfSprings[10];
//	LinearConstraint arrayOfConstraints[10];
//	int numberOfConstraints = 0;
//	int numOfBall = 3;
//	int numOfSpring = 0;
//	int windowHight = 800;
//	int windowWidht = 800;
//
//
//	arrayOfBalls[0] = Ball(10, Vector2(0, 0), Vector2(500, 200), 1, Vector2(0, 0), true);
//	arrayOfBalls[1] = Ball(10, Vector2(0, 0), Vector2(600, 200), 1, Vector2(0, 0), false);
//	arrayOfBalls[2] = Ball(10, Vector2(0, 0), Vector2(700, 200), 1, Vector2(0, 0), false);
//
//	arrayOfConstraints[0] = LinearConstraint(arrayOfBalls[0]._physicsObject, arrayOfBalls[1]._physicsObject, 0, 1, 100);
//	arrayOfConstraints[1] = LinearConstraint(arrayOfBalls[1]._physicsObject, arrayOfBalls[2]._physicsObject, 1, 2, 100);
//
//	double deltaTime = 0.0001;
//
//	while (!graphics.isRuning())
//	{
//
//		graphics.Update(); // the same but called from engine it self
//		graphics.Render(arrayOfBalls, numOfBall, arrayOfSprings, numOfSpring);
//		//physics.Update(arrayOfBalls, numOfBall, arrayOfSprings, numOfSpring, deltaTime, arrayOfConstraints, numberOfConstraints); // update engine should include graphics update and physics update
//	}
//
//	return 0;
//}