#include "DrivingScenarios.h"
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <functional>
struct func {	
	std::string event;
	std::list<std::string> myList;
};
int main()
{
	DrivingScenarios car;
	func PlayFunction[6];
	PlayFunction[0].event = "Red light Straight";
	PlayFunction[0].myList = {"SlowdownCar(0)","WaitingForGreenLight(Straight)"};
	PlayFunction[1].event = "Red light Right";
	PlayFunction[1].myList = { "SlowdownCar(0)","WaitingForGreenLight(Right)","SignalLight(Right)","Right()"};
	PlayFunction[2].event = "Red light Left";
	PlayFunction[2].myList = { "SlowdownCar(0)","WaitingForGreenLight(Left)","SignalLight(Left)","Left()" };
	PlayFunction[3].event = "Green light";
	PlayFunction[3].myList = { "SpeedCar(int max)"};
	PlayFunction[4].event = "Stop sign";
	PlayFunction[4].myList = { "SlowdownCar(0)" };
	PlayFunction[5].event = "Speed limit sign for 80";
	PlayFunction[5].myList = { "SlowdownCar(80)","SpeedCar(80)"};
	PlayFunction[5].event = "crosswalk";
	PlayFunction[5].myList = { "SlowdownCar(0)"};

	car.StartDriving();

}
