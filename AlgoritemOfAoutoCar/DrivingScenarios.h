#pragma once
#include <string>
#include <mutex>
#include "IMUSensor.h"
class DrivingScenarios
{
private:
   	 std::mutex mtxCurrentSpeed;
	 std::string line;
	 std::mutex mtxAccelerationSpeed;
	 std::mutex mtxTimeCar;
	 std::mutex mtxPathOfSpeed;
	 double accelerationSpeed;
	 double currentSpeed;
	 bool degel;
	 std::string str;
	 std::string signal;
	 std::string PathOfSpeed;
	 int temp;
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
	 int DistanceFromCarToObject();
	 std::string ReadFromFile(std::string filepath);
	 void Right(double distance);
	 void Left(double distance);
	 std::string TrafficLightColor();
	 void  WaitingForGreenLight();
	 void Stop();
	 void SignalLight(std::string direction);
	 void calculateAcceleration(IMUSensor& imuSensorpoint);
	
};

