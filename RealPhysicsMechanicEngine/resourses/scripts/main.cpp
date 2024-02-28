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
	GraphicsSystem graphics = GraphicsSystem("test", 1600, 800, "C:/projects/physicsSimulator/RealPhysicsMechanicEngine/resourses/images/a.png");
	Ball arrayOfBalls[2000];
	Spring arrayOfSprings[1000];
	int numOfBall = 3;
	int numOfSpring = 2;
	int windowHight = 800;
	int windowWidht = 800;
	int colitionBalIndex;
	int maxradius = 10;
	arrayOfBalls[0] = Ball(30, Vector2(0,0), Vector2(700, 400), 100000000000, Vector2(0, 0));
	arrayOfBalls[1] = Ball(30, Vector2(0, 200), Vector2(900, 400), 0.1, Vector2(0, 0));
	arrayOfSprings[0] = Spring(arrayOfBalls[0]._physicsObject, arrayOfBalls[1]._physicsObject, 10000);
	double gravity = 10;
	arrayOfBalls[2] = Ball(30, Vector2(0, 200), Vector2(1100, 400), 0.1, Vector2(0, 0));
	//arrayOfBalls[3] = Ball(30, Vector2(0, 0), Vector2(1100, 200), 0.1, Vector2(0, 0));
	arrayOfSprings[1] = Spring(arrayOfBalls[1]._physicsObject, arrayOfBalls[2]._physicsObject, 10000);
	//arrayOfSprings[2] = Spring(arrayOfBalls[2]._physicsObject, arrayOfBalls[3]._physicsObject, 1000);



	while (!graphics.isRuning()) //Engine is Runnig
	{
		arrayOfBalls[1]._physicsObject.AddForce(Vector2(0, gravity));
		arrayOfBalls[2]._physicsObject.AddForce(Vector2(0, gravity));
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