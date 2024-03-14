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
	int numOfBall = 12;
	int numOfSpring = 12;
	int windowHight = 800;
	int windowWidht = 800;
	int colitionBalIndex;
	int maxradius = 10;

	arrayOfBalls[0] = Ball(45, Vector2(0, 0), Vector2(500,100), 1, Vector2(0, 0), false);
	arrayOfBalls[1] = Ball(45, Vector2(0, 0), Vector2(600, 100), 1, Vector2(0, 0), false);
	arrayOfBalls[2] = Ball(45, Vector2(0, 0), Vector2(500, 200), 1, Vector2(0, 0), false);
	arrayOfBalls[3] = Ball(45, Vector2(0, 0), Vector2(600, 200), 1, Vector2(0, 0), false);

	arrayOfSprings[0] = Spring(arrayOfBalls[0]._physicsObject, arrayOfBalls[1]._physicsObject, 100000);
	arrayOfSprings[1] = Spring(arrayOfBalls[0]._physicsObject, arrayOfBalls[2]._physicsObject, 100000);
	arrayOfSprings[2] = Spring(arrayOfBalls[1]._physicsObject, arrayOfBalls[3]._physicsObject, 100000);
	arrayOfSprings[3] = Spring(arrayOfBalls[2]._physicsObject, arrayOfBalls[3]._physicsObject, 100000);
																							   
	arrayOfSprings[4] = Spring(arrayOfBalls[0]._physicsObject, arrayOfBalls[3]._physicsObject, 100000);
	arrayOfSprings[5] = Spring(arrayOfBalls[1]._physicsObject, arrayOfBalls[2]._physicsObject, 100000);

	
	arrayOfBalls[4] = Ball(45, Vector2(0, 0), Vector2(500, 300), 1, Vector2(0, 0), true);
	arrayOfBalls[5] = Ball(45, Vector2(0, 0), Vector2(600, 300), 1, Vector2(0, 0), false);
	arrayOfBalls[6] = Ball(45, Vector2(0, 0), Vector2(500, 400), 1, Vector2(0, 0), false);
	arrayOfBalls[7] = Ball(45, Vector2(0, 0), Vector2(600, 400), 1, Vector2(0, 0), false);

	arrayOfBalls[8] = Ball(45, Vector2(500, 0), Vector2(0, 400), 10, Vector2(0, 0), false);
	arrayOfBalls[9] = Ball(45, Vector2(-100, 100), Vector2(700, 400), 11, Vector2(0, 0), false);
	arrayOfBalls[10] = Ball(45, Vector2(300, 100), Vector2(0, 100), 11, Vector2(0, 0), false);
	arrayOfBalls[11] = Ball(45, Vector2(-300, 100), Vector2(700, 100), 11, Vector2(0, 0), false);

	arrayOfSprings[6] = Spring(arrayOfBalls[4]._physicsObject, arrayOfBalls[5]._physicsObject, 100000);
	arrayOfSprings[7] = Spring(arrayOfBalls[4]._physicsObject, arrayOfBalls[7]._physicsObject, 100000);
	arrayOfSprings[8] = Spring(arrayOfBalls[5]._physicsObject, arrayOfBalls[6]._physicsObject, 100000);
	arrayOfSprings[9] = Spring(arrayOfBalls[5]._physicsObject, arrayOfBalls[7]._physicsObject, 100000);

	arrayOfSprings[10] = Spring(arrayOfBalls[6]._physicsObject, arrayOfBalls[7]._physicsObject, 100000);
	arrayOfSprings[11] = Spring(arrayOfBalls[6]._physicsObject, arrayOfBalls[4]._physicsObject, 100000);

	//rope simulation
	/*double string_lenght = 800;
	int numberOfSegments = 4;
	int ballRadius = 5;
	double initialX = 700;
	double initialY = 100;

	arrayOfBalls[0] = Ball(ballRadius, Vector2(0, 0), Vector2(initialX, initialY), 10000000000000, Vector2(0, 0));
	for (int i = 1; i < numberOfSegments; i++)
	{
		arrayOfBalls[i] = Ball(ballRadius, Vector2(0, 0), Vector2(initialX+ i*string_lenght/numberOfSegments, initialY), 1, Vector2(0, 0));
	}

	numOfBall = numberOfSegments;
	numOfSpring = numberOfSegments - 1;

	for (int i = 0; i < numberOfSegments-1; i++)
	{
		arrayOfSprings[i] = Spring(arrayOfBalls[i]._physicsObject, arrayOfBalls[i+1]._physicsObject, 100000);
	}*/

	//double pendulume
	/*arrayOfBalls[0] = Ball(30, Vector2(0, 0), Vector2(500, 400), 10000000000000, Vector2(0, 0));
	arrayOfBalls[1] = Ball(30, Vector2(0, 0), Vector2(700, 400), 1, Vector2(0, 0));
	arrayOfBalls[2] = Ball(30, Vector2(0, 0), Vector2(900, 400), 1, Vector2(0, 0));
	arrayOfSprings[0] = Spring(arrayOfBalls[0]._physicsObject, arrayOfBalls[1]._physicsObject, 10000);
	arrayOfSprings[1] = Spring(arrayOfBalls[2]._physicsObject, arrayOfBalls[1]._physicsObject, 10000);*/


	////resonance
	/*arrayOfBalls[0] = Ball(30, Vector2(0,0), Vector2(100, 300), 1, Vector2(0, 0));
	arrayOfBalls[1] = Ball(30, Vector2(0, 0), Vector2(1300, 300), 1, Vector2(0, 0));
	arrayOfBalls[2] = Ball(30, Vector2(0, 0), Vector2(400, 300), 0.1, Vector2(0, 0));
	arrayOfBalls[3] = Ball(30, Vector2(700, 0), Vector2(1000, 300), 0.1, Vector2(0, 0));

	arrayOfSprings[0] = Spring(arrayOfBalls[0]._physicsObject, arrayOfBalls[2]._physicsObject, 10);
	arrayOfSprings[1] = Spring(arrayOfBalls[2]._physicsObject, arrayOfBalls[3]._physicsObject, 0.1);
	arrayOfSprings[2] = Spring(arrayOfBalls[3]._physicsObject, arrayOfBalls[1]._physicsObject, 10);

	numOfBall = 4;
	numOfSpring = 2;*/

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
		
		physics.update(arrayOfBalls, numOfBall, arrayOfSprings, numOfSpring, 0.001); // update engine should include graphics update and physics update
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