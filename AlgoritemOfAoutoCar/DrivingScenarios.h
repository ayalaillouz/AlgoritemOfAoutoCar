#pragma once
#include <string>
class DrivingScenarios
{
public:
	 double accelerationSpeed;
	 double currentSpeed;
	 bool degel;
	 std::string str;
	 std::string signal;
	 int temp;
	 int time;
	 DrivingScenarios();
	 void Settime(int second);
	 void SetcurrentSpeed(double speed);
	 void RedLightStraight();
	 void RedLightRight();
	 void RedLightLeft();
	 void GreenLight();
	 void SpeedLimitSignFor80();
	 void SlowdownCar(int minSpeed=0);
	 void SpeedCar(int maxSpeed=120);
	 int MaxSpeed();
	 int DistanceFromCarToObject();
	 std::string ReadFromFile(std::string filepath);
	 void Right(double distance);
	 void Left(double distance);
	 std::string TrafficLightColor();
	 void  WaitingForGreenLight();
	 void Stop();
	 void SignalLight(std::string direction);
	 void calculateAcceleration();

};

