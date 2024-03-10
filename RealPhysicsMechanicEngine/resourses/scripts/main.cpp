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

	arrayOfBalls[0] = Ball(30, Vector2(0, 0), Vector2(500, 400), 10000000000000, Vector2(0, 0));
	arrayOfBalls[1] = Ball(30, Vector2(0, 0), Vector2(700, 400), 1, Vector2(0, 0));
	arrayOfBalls[2] = Ball(30, Vector2(0, 200), Vector2(900, 400), 1, Vector2(0, 0));
	arrayOfSprings[0] = Spring(arrayOfBalls[0]._physicsObject, arrayOfBalls[1]._physicsObject, 10000);
	arrayOfSprings[1] = Spring(arrayOfBalls[2]._physicsObject, arrayOfBalls[1]._physicsObject, 10000);


	////resonance
	//arrayOfBalls[0] = Ball(30, Vector2(0,0), Vector2(100, 300), 10000000000000, Vector2(0, 0));
	//arrayOfBalls[1] = Ball(30, Vector2(0, 0), Vector2(1300, 300), 10000000000000, Vector2(0, 0));
	//arrayOfBalls[2] = Ball(30, Vector2(0, 0), Vector2(400, 300), 0.1, Vector2(0, 0));
	//arrayOfBalls[3] = Ball(30, Vector2(700, 0), Vector2(1000, 300), 0.1, Vector2(0, 0));

	//arrayOfSprings[0] = Spring(arrayOfBalls[0]._physicsObject, arrayOfBalls[2]._physicsObject, 10);
	//arrayOfSprings[1] = Spring(arrayOfBalls[2]._physicsObject, arrayOfBalls[3]._physicsObject, 0.1);
	//arrayOfSprings[2] = Spring(arrayOfBalls[3]._physicsObject, arrayOfBalls[1]._physicsObject, 10);

	clock_t start, end;
	double time_takenforFrame=0;

	double total_time = 0;
	double total_time1= 0;
	int fps_cnt = 0;

	while (!graphics.isRuning()) //Engine is Runnig
	{
		start = std::clock();
		if (total_time >= 1 / 60)
		{
			graphics.Update(); // the same but called from engine it self
			graphics.Render(arrayOfBalls, numOfBall, arrayOfSprings, numOfSpring); // should be here but rather in t
			total_time = 0;
		}
		
		physics.update(arrayOfBalls, numOfBall, arrayOfSprings, numOfSpring, time_takenforFrame); // update engine should include graphics update and physics update
		//Uint64 start = SDL_GetPerformanceCounter();
		end = std::clock();

		time_takenforFrame = double(end - start) / double(CLOCKS_PER_SEC);

		total_time += time_takenforFrame; 
		//total_time1 += time_takenforFrame;
		//cout << total_time1 <<std::endl;

		//fps_cnt += 1;
	}

	return 0;
}