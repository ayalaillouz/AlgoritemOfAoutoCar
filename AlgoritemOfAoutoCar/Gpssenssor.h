#pragma once

#include "DrivingScenarios.h"


class Gpssenssor
{
	bool onGps;
	mutex mtxGps;
	mutex mtxprint;
public:
	Gpssenssor();
	void UpdatePossion(DrivingScenarios& carpoint);
	void OffGPS();
	void print(const std::string& message);
};





