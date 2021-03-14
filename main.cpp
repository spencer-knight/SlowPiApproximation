#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <sstream>

struct vd2d {

	float x;
	float y;
};

//generates random points between -1 and 1 (not including 1)
vd2d genPoint() {

	float randoma = ((((float)std::rand() + 1) / (float)RAND_MAX) * 2.f) - 1.f; //random number -1 leq x lt 1
	float randomb = ((((float)std::rand() + 1)/ (float)RAND_MAX) * 2.f) - 1.f;

	return vd2d{ randoma, randomb };
}
//checks to see if distance is leq 1 from origin, meaning that it is within the unit circle
bool isInCircle(vd2d point) {

	return std::sqrt((point.x * point.x) + (point.y * point.y)) <= 1.f;
}
int coordToInt(double point) {

	return (int)((point * 199) + 300);
}
double circlePoints = 0;
int iterations = 0;
class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		sAppName = "Pi Approximator";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		FillRect(100, 100, 400, 400, olc::WHITE);
		FillRect(101, 101, 398, 398, olc::BLACK);
		DrawCircle(300, 300, 199, olc::WHITE);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame

		vd2d point = genPoint();
		bool isInCirc = isInCircle(point);
		//plot the point
		Draw(coordToInt(point.x), coordToInt(point.y), isInCirc? olc::BLUE : olc::RED);

		if (isInCirc) {

			circlePoints++;
		}
		iterations++;

		if(iterations % 1000 == 0) {
		
			FillRect(0, 0, 600, 99, olc::BLACK);
			std::stringstream ss;
			ss << (4 * (circlePoints / iterations));
			std::string num = ss.str();
			DrawString(0, 0, num, olc::DARK_GREY, 2);
		}
		//std::cout << 4 * (circlePoints / iterations) << std::endl;
		return true;
	}
};


int main()
{
	Example demo;
	if (demo.Construct(600, 600, 1, 1))
		demo.Start();

	return 0;
}