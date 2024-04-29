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
	//double getdt();
	int GettimeSensor();
	void SettimeSensor(int second);
private:
	thread imuThread;
	mutex mtxtimeSensor;
	double currentSpeed;
	bool isRunning;
	int timeSensor;
	double speedX, speedY, time, speed, distanceInOneSecond, distance;
	//double dt;
	double Dataprocessing;
};

