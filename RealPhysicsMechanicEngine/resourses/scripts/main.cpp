#include "SDL.h"
#include "PhysicsEngine.h"
#include "Window.h"

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


	PhysicsEngine engine = PhysicsEngine();
	Window window("simulation engine", 800, 800);
	engine.init(window._renderer);
	while (!window.isClosed()) //Engine is Runnig
	{
		window.PollEvent(); // the same but called from engine it self
		engine.update(); // update engine should include graphics update and physics update
		//engine.render(); // should be here but rather in t

	}

	return 0;
}