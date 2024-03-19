#include "DrivingScenarios.h"
#include "IMUSensor.h"
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <functional>
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>
void timerFunction(DrivingScenarios& carpoint, IMUSensor& imuSensorpoint)
{
	double seconds = 0;
	while (true)
	{
		// Increment the second
		seconds+=0.5;
		//update time in DrivingScenarios
		carpoint.SettimeCar(seconds);
		imuSensorpoint.SettimeSensor(seconds);
		// Sleep for 0.5 second
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

int main()
{
	//create Hash Table for functin in class DrivingScenarios.

	void (DrivingScenarios:: * HashFunctionDrivingScenarios[9])();
	HashFunctionDrivingScenarios[0] = &DrivingScenarios::RedLightStraight;
	HashFunctionDrivingScenarios[1] = &DrivingScenarios::RedLightRight;
	HashFunctionDrivingScenarios[2] = &DrivingScenarios::RedLightLeft;
	HashFunctionDrivingScenarios[3] = &DrivingScenarios::GreenLight;//condition:After the traffic light turns green.
	HashFunctionDrivingScenarios[4] = &DrivingScenarios::Stop;//condition: Stop sign,crosswalk.
	HashFunctionDrivingScenarios[5] = &DrivingScenarios::SpeedLimitSignFor80;
	//HashFunctionDrivingScenarios[5] = &DrivingScenarios::LaneChange;

	//build object

	IMUSensor imuSensor;
	DrivingScenarios car;
	std::thread timerThread(timerFunction, std::ref(car), std::ref(imuSensor));
	imuSensor.startIMUSensor(car);

	//join object


	imuSensor.stopIMUSensor();
	timerThread.join();
}

