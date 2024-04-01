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
	double GettimeSensor();
	void SettimeSensor(double second);
private:
	std::thread imuThread;
	double currentSpeed;
	bool isRunning;
	double timeSensor;
	double speedX, speedY, time, speed, distanceInOneSecond, distance,dt;
	double Dataprocessing;
};

