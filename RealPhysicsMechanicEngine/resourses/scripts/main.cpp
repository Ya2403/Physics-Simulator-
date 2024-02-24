#include "SDL.h"
#include "PhysicsEngine.h"
#include "GraphicsSystem.h"
#include "Window.h"
#include "Ball.h"
#include "SDL.h"
#include "iostream"
int main(int argc, char* argv[])
{
	/*
	* it should be like two in one engine
	*cause physics shouldn't be able to drawit should be like two in one engine
	* I guess it might be like physics has all the coords in it and maybe cause physics shouldn't be able to draw
	*object it self should have physiscs component and graphics one and so the
	* I guess it might be like physics has all the coords in it and maybe
	*object it self should have physiscs component and graphics one and so 
	* it will be like even without graphics I should be	able to get some like x(t) graphs or something
	*/ 


	PhysicsEngine physics = PhysicsEngine();
	GraphicsSystem graphics = GraphicsSystem("test", 800, 800, "C:/projects/physicsSimulator/RealPhysicsMechanicEngine/resourses/images/a.png");
	Ball arrayOfBalls[2000];
	Spring arrayOfSprings[1000];
	int numOfBall = 2;
	int numOfSpring = 1;
	int windowHight = 800;
	int windowWidht = 800;
	int colitionBalIndex;
	int maxradius = 10;
	arrayOfBalls[0] = Ball(30, Vector2(-20,0), Vector2(200, 300), 0.1, Vector2(0, 0));
	arrayOfBalls[1] = Ball(30, Vector2(20, 0), Vector2(600, 300), 0.1, Vector2(0, 0));
	arrayOfSprings[0] = Spring(arrayOfBalls[0]._physicsObject, arrayOfBalls[1]._physicsObject, 0.006);



	while (!graphics.isRuning()) //Engine is Runnig
	{
		graphics.Update(); // the same but called from engine it self
		physics.update(arrayOfBalls, numOfBall, arrayOfSprings, numOfSpring); // update engine should include graphics update and physics update
		graphics.Render(arrayOfBalls, numOfBall, arrayOfSprings, numOfSpring); // should be here but rather in t
		Uint64 start = SDL_GetPerformanceCounter();


		// Do event loop

		// Do physics loop

		// Do rendering loop
	}

	return 0;
}