#pragma once
#include <thread>
#include "DrivingScenarios.h"

 class IMUSensor
{
public:
	IMUSensor();
	void calculateSpeed(DrivingScenarios& carpoint);
	void startIMUSensor(DrivingScenarios& carpoint);
	void stopIMUSensor();
	double getCurrentSpeed();
	double getdt();
	int GettimeSensor();
	void SettimeSensor(int second);
private:
	std::thread imuThread;
	double currentSpeed;
	bool isRunning;
	int timeSensor;
	double speedX, speedY, time, speed, distanceInOneSecond, distance,dt;
	double Dataprocessing;
};

