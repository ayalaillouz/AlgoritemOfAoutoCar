#include "DrivingScenarios.h"
#include "IMUSensor.h"
#include "Gpssenssor.h"
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
#define CHECK_DIRECTION(direction) (direction == "right" ?1:0 )
#define CHECK_STRAIGHT(direction) (direction!= "right" && direction!= "left" ?2:0 ) 
int main()
{
	//create Hash Table for functin in class DrivingScenarios.

	void (DrivingScenarios:: * HashFunctionDrivingScenarios[6])();
	HashFunctionDrivingScenarios[0] = &DrivingScenarios::RedLightStraight;
	HashFunctionDrivingScenarios[1] = &DrivingScenarios::RedLightRight;
	HashFunctionDrivingScenarios[2] = &DrivingScenarios::RedLightLeft;
	HashFunctionDrivingScenarios[3] = &DrivingScenarios::GreenLight;//condition:After the traffic light turns green.
	HashFunctionDrivingScenarios[4] = &DrivingScenarios::Stop;//condition: Stop sign,crosswalk.
	HashFunctionDrivingScenarios[5] = &DrivingScenarios::SpeedLimitSignFor80;

	//HashFunctionDrivingScenarios[5] = &DrivingScenarios::LaneChange;

	void (DrivingScenarios:: * HashFunctionDirection[3])(double);
	HashFunctionDirection[0] = &DrivingScenarios::Left;
	HashFunctionDirection[1] = &DrivingScenarios::Right;
	HashFunctionDirection[2] = &DrivingScenarios::Straight;

	//build object

	IMUSensor imuSensor;
	DrivingScenarios car;
	Gpssenssor gpsSenssor;
	std::thread timerThread(timerFunction, std::ref(car), std::ref(imuSensor));
	imuSensor.startIMUSensor(car);
	std::thread yoloThread(&DrivingScenarios::UpdateStateFromYolo, &car);
	std::thread Gpsthread(&Gpssenssor::UpdatePossion,"src/GPS.txt",&car,&imuSensor);
	while (1)
	{

	}

	//join object

	yoloThread.join();
	imuSensor.stopIMUSensor();
	Gpsthread.join();
	timerThread.join();
}

