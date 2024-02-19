#include "SDL.h"
#include "PhysicsEngine.h"
#include "GraphicsSystem.h"
#include "Window.h"
#include "Ball.h"
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
	Ball ball1 = Ball(100, Vector2(1, 5), Vector2(100, 100), 1, Vector2(0, 0));
	Ball arrayOfBalls[1];
	arrayOfBalls[0] = ball1;

	while (!graphics.isRuning()) //Engine is Runnig
	{
		graphics.Update(); // the same but called from engine it self
		physics.update(arrayOfBalls, 1); // update engine should include graphics update and physics update
		graphics.Render(arrayOfBalls, 1); // should be here but rather in t
	}

	return 0;
}