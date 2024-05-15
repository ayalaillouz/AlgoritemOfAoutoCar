
#include "File.h"
#include "DrivingScenarios.h"
#include "IMUSensor.h"
#include "Gpssenssor.h"
#include "Server.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <sstream>
#include <iomanip>
#include <regex>
#include <vector>
#include <list>
#include <functional>
#include <thread> 
#include <chrono>
#include <fstream>
#include <cerrno>



void timerFunction(DrivingScenarios& carpoint, IMUSensor& imuSensorpoint)
{
	int seconds = 0;
	while (true)
	{
		// Increment the second
		seconds++;
		//update time in DrivingScenarios
		carpoint.SettimeCar(seconds);
		imuSensorpoint.SettimeSensor(seconds);
		// Sleep for 0.5 second
		cout << "the time now:" << seconds << endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}


#define CHECK_STRAIGHT(direction) ((direction!= "right" && direction!= "left")?2:0 )
#define CHECK_DIRECTION(direction) (direction == "right" ?1:0)
int main()
{
	Server server;
	vector<pair<string,string>> carInstructions = server.Receivinginformation();
	//build object

	IMUSensor imuSensor;
	DrivingScenarios car;
	Gpssenssor gpsSenssor;
	File files;
	thread timerThread(timerFunction,ref(car),ref(imuSensor));
	thread IMUsensor([&] {imuSensor.startIMUSensor(car); });
	thread yoloThread(&DrivingScenarios::UpdateStateFromYolo,ref(car));
	//std::thread yoloThread(&DrivingScenarios::UpdateStateFromYolo);
	thread Gpsthread([&]{gpsSenssor.UpdatePossion(car);});
	string Instruction,direction;
	double distance;
	int placeinarr;
	// Output the contents of the vector of pairs
	for (const auto& pair : carInstructions)
	{

		std::cout << pair.first << ": " << pair.second << std::endl;
		Instruction = pair.first;
		distance = stod(pair.second);
		cout << Instruction << distance << endl;
		car.Setmaxspeed(100);
		direction = files.GetWordAfterLastDash(Instruction);
		placeinarr = CHECK_DIRECTION(direction) + CHECK_STRAIGHT(direction);
		car.PlayHashFunctionDirection(placeinarr, distance);
		cout << "distance: " << distance << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}


	timerThread.join();
	yoloThread.join();
	gpsSenssor.OffGPS();
	imuSensor.stopIMUSensor();
	IMUsensor.join();
	


}