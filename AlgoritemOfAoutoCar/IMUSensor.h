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
	double Gettime();
	void Settime(double second);
private:
	std::thread imuThread;
	double currentSpeed;
	bool isRunning;
	double time;
	double accelerometerX; 
	double accelerometerY ; 
	double accelerometerZ; 
	double gyroscopeX ;  
	double gyroscopeY ;   
	double gyroscopeZ ;
	double acceleration;
	double g;  // Acceleration due to gravity (approx. 9.81 m/s^2)
	double dt;
	double dv;
	double Dataprocessing;
};

