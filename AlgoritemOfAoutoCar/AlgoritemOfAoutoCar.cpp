﻿
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
using namespace std;
 mutex mtxprint;

void print(const std::string& message) 
{
	std::lock_guard<std::mutex> lock(mtxprint);
	std::cout << message << std::endl;
}

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
		string time = "the time now:"+ to_string(seconds);
		print(time);
		//cout << "the time now:" << seconds << endl;
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

	//play sensors
	thread timerThread(timerFunction,ref(car),ref(imuSensor));
	thread IMUsensor([&] {imuSensor.startIMUSensor(car); });
	//car.runYolo();
	this_thread::sleep_for(chrono::seconds(1));
    thread yoloThread(&DrivingScenarios::UpdateStateFromYolo,ref(car));
	thread Gpsthread([&]{gpsSenssor.UpdatePossion(car);});


	string Instruction,direction, instruction;
	double distance;
	int placeinarr;

	//navigation instructions

	for (const auto& pair : carInstructions)
	{
		instruction = "instruction now:" +pair.first+ ":" +pair.second;
		print(instruction);
		Instruction = pair.first;
		distance = stod(pair.second);
		car.Setmaxspeed(100);
		direction = files.GetWordAfterLastDash(Instruction);
		placeinarr = CHECK_DIRECTION(direction) + CHECK_STRAIGHT(direction);
		car.PlayHashFunctionDirection(placeinarr, distance);
	}

	//Switching off and disconnecting sensors

	timerThread.join();
	yoloThread.join();
	gpsSenssor.OffGPS();
	imuSensor.stopIMUSensor();
	IMUsensor.join();
	


}