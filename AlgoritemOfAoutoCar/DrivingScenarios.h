#pragma once
#include <string>
#include <mutex>
#include <iostream>
#include <stdbool.h>
#include "IMUSensor.h"
using namespace std;
class DrivingScenarios
{
private:
   	 mutex mtxCurrentSpeed;
	 string line;
	 mutex mtxAccelerationSpeed;
   	 mutex mtxTimeCar;
	 mutex mtxdistance;
	 mutex mtxPathOfSpeed;
	 mutex mtxstate;
	 mutex mtxTrafficLightColor;
	 mutex mtxvelosityX;
	 mutex mtxvelosityY;
	 mutex mtxoldvelosityX;
	 mutex mtxoldvelosityY;
	 double accelerationSpeed;
	 double currentSpeed;
	 bool degel;
	 string str;
	 string signal;
	 string PathOfSpeed;
	 string direction;
	 int temp;
	 double distance;
	 int timeCar;
	 bool onyolo;
	 string state;
	 string TrafficLightColor;
	 char buffer[128];
	 FILE* pipe;
	 vector<double> filtered_positions;
	 double velosityX ;
	 double velosityY;
	 double oldvelosityX ;
	 double oldvelosityY;
	 double distance;
	 array<bool,8> arrState;
public:
	double GetvelosityX();
	double GetvelosityY();
	double GetoldvelosityX();
	double GetoldvelosityY();
	void SetoldvelosityX(double newoldvelosityX);
	void SetoldvelosityY(double newoldvelosityY);
	void SetvelosityX(double newvelosityX);
	void SetvelosityY(double newvelosityY);
	string Getdirection();
	string GetTrafficLightColor();
	void SetTrafficLightColor(string newTrafficLightColor);
	void Setdirection(string newdirection);
	double Getdistance();
	void Setdistance(double newdistance);
	double Getdistance();
	void Setdistance(double newdistance);
	string Getstate();
	void Setstate(string s);
	 DrivingScenarios();
	 void SettimeCar(int second);
	 int GettimeCar();
	 string GetPathOfSpeed();
	 double GetaccelerationSpeed();
	 double GetcurrentSpeed();
	 void SetcurrentSpeed(double speed);
	 void SetaccelerationSpeed(double newaccelationspeed);
	 void RedLightStraight();
	 void RedLightRight();
	 void RedLightLeft();
	 void GreenLight();
	 void SpeedLimitSignFor80();
	 void SlowdownCar(int minSpeed=0);
	 void SpeedCar(int maxSpeed=120);
	 int MaxSpeed();
	 double DistanceFromCarToObject(std::string filename);
	 string ReadFromFile(std::string filepath);
	 void Right(double distance);
	 void Left(double distance);
	 void Straight(double distance=0);
	 void LaneChangeRight();
	 void LaneChangeLeft();
	 void  WaitingForGreenLight();
	 void Stop();
	 void SignalLight(std::string direction);
	 void calculateAcceleration(IMUSensor& imuSensorpoint);
	 string getLastCreatedFolder(const string& path);
	 void UpdateStateFromYolo();
	 string extractFirstWord(const string& input);
	 void ConnectKalmanFilter(IMUSensor& imuSensorpoint);
	 void processFile(const std::string& filePath);
};

