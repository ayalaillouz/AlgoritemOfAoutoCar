#pragma once
#include <string>
#include "IMUSensor.h"
class DrivingScenarios
{
private:
	 double accelerationSpeed;
	 double currentSpeed;
	 bool degel;
	 std::string str;
	 std::string signal;
	 int temp;
	 double time;
public:
	 DrivingScenarios();
	 void Settime(double second);
	 double Gettime();
	 void SetcurrentSpeed(double speed);
	 void SetaccelerationSpeed(double newaccelationspeed);
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
	 void calculateAcceleration(IMUSensor& imuSensorpoint);
	 void UpdateCurrentSpeed(IMUSensor& imuSensorpoint);
};

