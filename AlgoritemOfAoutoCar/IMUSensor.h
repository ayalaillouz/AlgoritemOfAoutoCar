#pragma once
#include "DrivingScenarios.h"
#include <thread>
using namespace std;

class IMUSensor
{
public:
	IMUSensor();
	void calculateSpeed(DrivingScenarios& carpoint);
	void startIMUSensor(DrivingScenarios& carpoint);
	void stopIMUSensor();
	double getCurrentSpeed();
	int GettimeSensor();
	void SettimeSensor(int second);
private:
	thread imuThread;
	mutex mtxtimeSensor;
	bool isRunning;
	int timeSensor;
	double speedX, speedY, time, speed, distanceInOneSecond, distance, Dataprocessing, currentSpeed;
};

