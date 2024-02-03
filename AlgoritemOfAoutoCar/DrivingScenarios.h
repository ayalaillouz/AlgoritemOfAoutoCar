#pragma once
#include <iostream>
#include <chrono>
#include <string>
class DrivingScenarios
{
public:
	static float accelerationSpeed;
	static float currentSpeed;
	static int secondTimer;
	static bool degel;
	static std::string str;
	static std::string signal;
	static int temp;
	DrivingScenarios();
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
	void Right(float distance);
	void Left(float distance);
	std::string TrafficLightColor();
	void  WaitingForGreenLight();
	void Stop();
	void SignalLight(std::string direction);
};

