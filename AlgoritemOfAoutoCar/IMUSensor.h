#pragma once
#include <thread>
class IMUSensor
{
public:
	void calculateSpeed(DrivingScenarios& carpoint);
	void startIMUSensor();
	void stopIMUSensor();
	double getCurrentSpeed();
	void Settime(int second);
private:
	std::thread imuThread;
	double currentSpeed = 0.0;
	bool isRunning = false;
	double time = 1.0; 
	double accelerometerX = 1.2; 
	double accelerometerY = 3.5; 
	double accelerometerZ = 9.8; 
	double gyroscopeX = 0.1;  
	double gyroscopeY = 0.3;   
	double gyroscopeZ = 0.2;
	double acceleration;
};

