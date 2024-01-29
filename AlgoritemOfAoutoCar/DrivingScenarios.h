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
	string str;
	int temp;
	DrivingScenarios();
   	void StartDriving();
	void timer(int& seconds);
	void SlowdownCar(int minSpeed);
	void SpeedCar(int maxSpeed);
	int DistanceFromCarToObject();
	std::string ReadFromFile(string filepath);
	bool Right(float distance);
	bool Left(float distance);
	void WaitingForGreenLight(string direction);
	std::string SignalLight(string direction);
};

