#pragma once
#include "DrivingScenarios.h"
#include <thread>
#include <mutex>
using namespace std;

class IMUSensor
{
	thread imuThread;
	mutex mtxtimeSensor;
	mutex mtxprint;
	bool isRunning;
	int timeSensor;
	double speedX,speedY,time,speed,distanceInOneSecond,distance,Dataprocessing,currentSpeed,dt;
public:
	IMUSensor();
	void calculateSpeed(DrivingScenarios& carpoint);
	void startIMUSensor(DrivingScenarios& carpoint);
	void stopIMUSensor();
	double getCurrentSpeed();
	int GettimeSensor();
	void SettimeSensor(int second);
	void print(const string& message);


};

