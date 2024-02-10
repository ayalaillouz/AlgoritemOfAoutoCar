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
	double getdv();
	double getacceleration();
	double GettimeSensor();
	void SettimeSensor(double second);
private:
	std::thread imuThread;
	double currentSpeed;
	bool isRunning;
	double timeSensor;
	double accelerometerX; 
	double accelerometerY ; 
	double accelerometerZ; 
	double acceleration;
	double g;  // Acceleration due to gravity (approx. 9.81 m/s^2)
	double dt;
	double dv;
	double Dataprocessing;
};

