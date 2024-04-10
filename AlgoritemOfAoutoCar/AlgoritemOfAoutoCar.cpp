#include "DrivingScenarios.h"
#include "IMUSensor.h"
#include "Gpssenssor.h"
#include "File.h"
#include <iostream>
#include <list>
#include <vector>
#include <string.h>
#include <functional>
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

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
		
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
#define CHECK_STRAIGHT(direction) ((direction!= "right" && direction!= "left")?2:0 )
#define CHECK_DIRECTION(direction) (direction == "right" ?1:0)
int main()
{

	//build object

	IMUSensor imuSensor;
	DrivingScenarios car;
	Gpssenssor gpsSenssor;
	File files;
	thread timerThread(timerFunction, std::ref(car), std::ref(imuSensor));
	imuSensor.startIMUSensor(car);
	thread yoloThread(&DrivingScenarios::UpdateStateFromYolo, &car);
	thread Gpsthread(&Gpssenssor::UpdatePossion,"src/GPS.txt",&car,&imuSensor);
	//start
	//read Filestring direction;

	string direction;
	int placeinarr;
	double distance;
	string filename = "src/Instructions.txt";
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "לא ניתן לפתוח את הקובץ." << endl;
		return 1;
	}
	string line;
	while (getline(file, line))
	{
		direction = files.GetWordAfterLastDash(line);
		distance = files.ExtractLastWordToDouble(line);
		placeinarr = CHECK_DIRECTION(direction) + CHECK_STRAIGHT(direction);
		car.PlayHashFunctionDirection(placeinarr,distance);
		cout << "distance: " << distance << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}
	file.close();

	//join object

	yoloThread.join();
	imuSensor.stopIMUSensor();
	Gpsthread.join();
	timerThread.join();
}

