#include "DrivingScenarios.h"
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <functional>
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>
void timerFunction()
{
	int seconds = 0;

	while (true)
	{
		// Print the current second
		std::cout << "Elapsed Time: " << seconds << " seconds" << std::endl;

		// Increment the second
		seconds++;

		// Sleep for 1 second
		std::this_thread::sleep_for(std::chrono::seconds(1));
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
	DrivingScenarios car;
	std::thread timerThread(timerFunction);
	car.StartDriving();
	timerThread.join();
}

