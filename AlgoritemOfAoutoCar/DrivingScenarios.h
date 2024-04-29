#pragma once
#include <string>
#include <mutex>
#include <vector>
#include <array>
#include <iostream>
#include <stdbool.h>
#include "File.h"

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
	 double dt;
	 double distancetoturn;
	 array<bool,8> arrState;


public:
	 void (DrivingScenarios::*HashFunctionDrivingScenarios[6])() = {&DrivingScenarios::RedLightStraight,&DrivingScenarios::RedLightRight,&DrivingScenarios::RedLightLeft,&DrivingScenarios::GreenLight,&DrivingScenarios::Stop,&DrivingScenarios::SpeedLimitSignFor80};
	 void (DrivingScenarios::*HashFunctionDirection[3])(double) = { &DrivingScenarios::Left,&DrivingScenarios::Right,&DrivingScenarios::Straight };
	 void PlayHashFunctionDirection( int placeinhash, double distance);
	 void PlayHashFunctionDrivingScenarios(int placeinhash);
	 DrivingScenarios();
	 double GetvelosityX();
	 double GetvelosityY();
	 double GetoldvelosityX();
	 double GetoldvelosityY();
	 string Getdirection();
	 string GetTrafficLightColor();
	 double Getdistance();
	 string Getstate();
	 double Getdistancetoturn();

	 double GetaccelerationSpeed();
	 double GetcurrentSpeed();
	 int GettimeCar();
	 string GetPathOfSpeed();
	 void SetoldvelosityX(double newoldvelosityX);
	 void SetoldvelosityY(double newoldvelosityY);
	 void SetvelosityX(double newvelosityX);
	 void SetvelosityY(double newvelosityY);
	 void SetTrafficLightColor(string newTrafficLightColor);
	 void Setdirection(string newdirection);
	 void Setdistance(double newdistance);
	 void Setstate(string s);
	 void SettimeCar(int second);
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
	 void Right(double distancetoturnRight);
	 void Left(double distancetoturnLeft);
	 void Setdistancetoturn(double newdistancetoturn);
	 void Straight(double distancetoturnStraight=0);
	 void LaneChangeRight();
	 void LaneChangeLeft();
	 void  WaitingForGreenLight();
	 void Stop();
	 void SignalLight(std::string direction);
	// void calculateAcceleration(IMUSensor& imuSensorpoint);
	 string getLastCreatedFolder(const string& path);
	 void UpdateStateFromYolo();
	 string extractFirstWord(const string& input);
	 void ConnectKalmanFilter();
	 void processFile(const std::string& filePath);
	 void Offyolo();
};

