#pragma once

#include "DrivingScenarios.h"


class Gpssenssor
{
	bool onGps;
	mutex mtxGps;
public:
	Gpssenssor();
	void UpdatePossion(DrivingScenarios& carpoint);
	void OffGPS();
};





