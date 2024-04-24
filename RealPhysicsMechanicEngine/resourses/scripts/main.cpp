#include "PhysicsEngine.h"
#include "Window.h"
#include "Ball.h"
#include "iostream"
#include <fstream>
#include <iomanip>

const double pi = 3.14159265358979323846;

double CalculateTeta(Ball arrayOfBalls[], double previousTeta)
{
	Vector2 vect12 = arrayOfBalls[2]._physicsObject._pos - arrayOfBalls[1]._physicsObject._pos;
	vect12.normalizeVector();
	double teta;
	int prevZone = int(abs(trunc(previousTeta/pi))) % 2;
	if (previousTeta < 0)
	{
		prevZone = (prevZone + 1) % 2;
	}
	int currZone;
	int currZone4;

	if (arrayOfBalls[1]._physicsObject._pos.x >= arrayOfBalls[2]._physicsObject._pos.x)
	{
		teta = -acos(-(vect12 * Vector2(0, 1)) / vect12.getMag());
		currZone = 1;
		if (teta < -pi / 2.0) currZone4 = 2;
		else currZone4 = 3;
	}
	else
	{
		teta = acos(-(vect12 * Vector2(0, 1)) / vect12.getMag());
		currZone = 0;
		if (teta > pi / 2.0) currZone4 = 1;
		else currZone4 = 0;
		
	}

	teta = teta;


	if (prevZone == currZone)
	{
		if (previousTeta < 0)
		{
			if(currZone==0) return (trunc(previousTeta / pi) -1) * pi + teta; //+
			else return (trunc(previousTeta / pi)) * pi + teta; //+
		}
		else
		{
			if (currZone == 0) return (trunc(previousTeta / pi)) * pi + teta; //+
			else return (trunc(previousTeta / pi)+1) * pi + teta; //+
		}
	}
	else
	{
		if (previousTeta < 0)
		{
			if (currZone4 == 0) return (trunc(previousTeta / pi)) * pi + teta; //+
			else if (currZone4 == 1) return (trunc(previousTeta / pi) - 2) * pi + teta; //+
			else if (currZone4 == 2) return (trunc(previousTeta / pi)+1) * pi + teta; //+
			else return (trunc(previousTeta / pi)-1) * pi + teta; //+
		}
		else
		{
			if (currZone4 == 0) return (trunc(previousTeta / pi)+1) * pi + teta; //+
			else if (currZone4 == 1) return (trunc(previousTeta / pi) - 1) * pi + teta; //+
			else if (currZone4 == 2) return (trunc(previousTeta / pi) + 2) * pi + teta; //+
			else return (trunc(previousTeta / pi)) * pi + teta; //+
		}
	}
}

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
	clock_t start, end;

	start = clock();
	PhysicsEngine physics = PhysicsEngine();
	Ball arrayOfBalls[20];
	Spring arrayOfSprings[10];
	int numOfBall = 3;
	int numOfSpring = 2;
	int windowHight = 800;
	int windowWidht = 800;


	arrayOfBalls[0] = Ball(45, Vector2(0, 0), Vector2(0, 0), 1, Vector2(0, 0), true);
	arrayOfBalls[1] = Ball(45, Vector2(0, 0), Vector2(100,0), 1, Vector2(0, 0), false);
	arrayOfBalls[2] = Ball(45, Vector2(0, 0), Vector2(200,0), 1, Vector2(0, 0), false);
	


	arrayOfSprings[0] = Spring(arrayOfBalls[0]._physicsObject, arrayOfBalls[1]._physicsObject, 1000000);
	arrayOfSprings[1] = Spring(arrayOfBalls[1]._physicsObject, arrayOfBalls[2]._physicsObject, 1000000);

	double deltaTime = 0.00001;
	double currentTime = 0;
	double writeinFileDeltaTime = 0.001;
	double currFileTime = 0;
	double energy2 = 0;
	double energy = 0;
	double gravity = -400;

	int ballIndex = 2;
	ofstream textFile;
	textFile.open("example.txt");

	double teta = 0;
	double prevteta = pi/2;
	Vector2 omegaVector;
	double velociyOmega;
	double velociyOmega1 = 0;
	bool flag;

	while (currentTime < 100)
	{
		energy = 0;
		energy2 = 0;
		for (int i = 1; i < numOfBall; i++)
		{
			energy += arrayOfBalls[i]._physicsObject._mass * pow(arrayOfBalls[i]._physicsObject._velocity.getMag(), 2);
			energy += -2 * arrayOfBalls[i]._physicsObject._mass * gravity * arrayOfBalls[i]._physicsObject._pos.y;
		}
		energy2 = energy;

		for (int i = 0; i < numOfSpring; i++)
		{
			energy += arrayOfSprings[i]._stiffness * pow(arrayOfSprings[i]._connectionPoint1->_pos.Distance(arrayOfSprings[i]._connectionPoint2->_pos) - arrayOfSprings[i]._initianLenght, 2);
		}
		
		teta = CalculateTeta(arrayOfBalls, prevteta);
		
		velociyOmega1 = (teta - prevteta) / deltaTime;
		
		physics.update(arrayOfBalls, numOfBall, arrayOfSprings, numOfSpring, deltaTime); // update engine should include graphics update and physics update

		if (currFileTime >= writeinFileDeltaTime)
		{
			
			textFile << currentTime << " " << arrayOfBalls[ballIndex]._physicsObject._pos.x << " " << arrayOfBalls[ballIndex]._physicsObject._pos.y << " " << arrayOfBalls[ballIndex]._physicsObject._velocity.x << " " << arrayOfBalls[ballIndex]._physicsObject._velocity.y << " " << teta <<" "<< velociyOmega1 <<" " << energy <<" "<<energy2 << "\n";
			currFileTime = 0;
		}

		currentTime += deltaTime;
		currFileTime += deltaTime;
		prevteta = teta;
	}

	end = clock();

	// Calculating total time taken by the program.
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout << "Time taken by program is : ";
	cout<<setprecision(3)<< time_taken << std::endl;

	return 0;
}