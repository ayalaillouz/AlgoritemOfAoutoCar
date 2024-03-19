#pragma once
#include <string>
#include <mutex>
#include <iostream>
#include "IMUSensor.h"
using namespace std;
class DrivingScenarios
{
private:
   	 mutex mtxCurrentSpeed;
	 string line;
	 mutex mtxAccelerationSpeed;
   	 mutex mtxTimeCar;
	 mutex mtxPathOfSpeed;
	 double accelerationSpeed;
	 double currentSpeed;
	 bool degel;
	 string str;
	 string signal;
	 string PathOfSpeed;
	 string direction;
	 int temp;
	 double distance;
	 double timeCar;
public:
	 DrivingScenarios();
	 void SettimeCar(double second);
	 double GettimeCar();
	 string GetPathOfSpeed();
	 double GetaccelerationSpeed();
	 double GetcurrentSpeed();
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
	 double DistanceFromCarToObject(std::string filename);
	 string ReadFromFile(std::string filepath);
	 void Right(double distance);
	 void Left(double distance);
	 string TrafficLightColor();
	 void LaneChangeRight();
	 void LaneChangeLeft();
	 void  WaitingForGreenLight();
	 void Stop();
	 void SignalLight(std::string direction);
	 void calculateAcceleration(IMUSensor& imuSensorpoint);
	
};

