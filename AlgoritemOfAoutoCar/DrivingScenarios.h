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
	std::string str;
	int temp;
	DrivingScenarios();
   	void StartDriving();
	void timer(int& seconds);
	void SlowdownCar(int minSpeed);
	void SpeedCar(int maxSpeed);
	int DistanceFromCarToObject();
	std::string ReadFromFile(std::string filepath);
	bool Right(float distance);
	bool Left(float distance);
	std::string TrafficLightColor();
	std::string  WaitingForGreenLight(std::string direction);
	std::string SignalLight(std::string direction);
};

