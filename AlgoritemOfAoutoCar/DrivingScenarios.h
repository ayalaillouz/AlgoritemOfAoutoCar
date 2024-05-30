#pragma once
#include <string>
#include <mutex>
#include <vector>
#include <array>
#include <iostream>
#include <bitset>
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
	 mutex mtxprint;
	 mutex mtxSpeed;
	 mutex mtxstate;
	 mutex mtxTrafficLightColor;
	 mutex mtxvelosityX;
	 mutex mtxvelosityY;
	 mutex mtxmaxspeed;
	 mutex mtxoldvelosityX;
	 mutex mtxoldvelosityY;
	 mutex mtxplay;
	 double accelerationSpeed;
	 double currentSpeed;
	 bool degel;
	 string str;
	 string directiontotravel;
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
	 bitset<6> arrState;
	 bool play;
	 int maxspeed;
	 int i;

public:
	 void (DrivingScenarios::*HashFunctionDrivingScenarios[6])() = {&DrivingScenarios::RedLightStraight,&DrivingScenarios::RedLightRight,
																    &DrivingScenarios::RedLightLeft,&DrivingScenarios::GreenLight,
																	&DrivingScenarios::Stop,&DrivingScenarios::SpeedLimitSignFor80};
	 void (DrivingScenarios::*HashFunctionDirection[3])(double) = { &DrivingScenarios::Left,&DrivingScenarios::Right,
																	&DrivingScenarios::Straight };

	 void PlayHashFunctionDirection( int placeinhash, double dist);
	 void PlayHashFunctionDrivingScenarios(int placeinhash);
	 DrivingScenarios();
	 double GetvelosityX();
	 void SetvelosityX(double newvelosityX);
	 double GetvelosityY();
	 void SetvelosityY(double newvelosityY);
	 double GetoldvelosityX();
	 void SetoldvelosityX(double newoldvelosityX);
	 double GetoldvelosityY();
	 void SetoldvelosityY(double newoldvelosityY);
	 bool Getplay();
     void Setplay(bool newplay);
	 string Getdirection();
	 void Setdirection(string newdirection);
	 string GetTrafficLightColor();
	 void SetTrafficLightColor(string newTrafficLightColor);
	 double Getdistance();
	 void Setdistance(double newdistance);
	 //string Getstate();
	 double Getdistancetoturn();
	 void SetaccelerationSpeed(double newaccelationspeed);
	 double GetaccelerationSpeed();
	 double GetcurrentSpeed();
	 void SetcurrentSpeed(double speed);
	 int GettimeCar();
	 void SettimeCar(int second);
	 string GetPathOfSpeed();
	 int MaxSpeed();
	 void Setmaxspeed(int newmaxspeed);
	// void Setstate(string s);
	 void RedLightStraight();
	 void RedLightRight();
	 void RedLightLeft();
	 void GreenLight();
	 void SpeedLimitSignFor80();
	 void Stop();
	 void SignalLight(std::string direction);
	 void SlowdownCar(int minSpeed=0);
	 void SpeedCar(int maxSpeed=120);
	// double DistanceFromCarToObject(std::string filename);
	 string ReadFromFile(std::string filepath);
	 void Right(double distancetoturnRight);
	 void Left(double distancetoturnLeft);
	 void Setdistancetoturn(double newdistancetoturn);
	 void Straight(double distancetoturnStraight=0);
	// void LaneChangeRight();
	// void LaneChangeLeft();
	// void  WaitingForGreenLight();
	// void calculateAcceleration(IMUSensor& imuSensorpoint);
	 string getLastCreatedFolder(const string& path);
	 void UpdateStateFromYolo();
	 string extractFirstWord(const string& input);
	 void ConnectKalmanFilter();
	 void processTxtFiles(const std::string& folderPath);
	 void processFile(const std::string& filePath);
	 void Offyolo();
	 void print(const std::string& message);
	 void runYolo();
};

