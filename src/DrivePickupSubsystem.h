#ifndef DRIVEPICKUPSUBSYSTEM_H
#define DRIVEPICKUPSUBSYSTEM_H

#include "CORELIB/CORERobot.h"
#include "WPILib.h"
#include <cmath>
#include <iostream>
#include <math.h>

using namespace CORE;


class DrivePickupSubsystem: public CORESubsystem{



public:

		CANSpeedController::ControlMode mode = CANSpeedController::kPercentVbus;
//		CANSpeedController::ControlMode mode = CANSpeedController::kVoltage;

		// Drive Motors
		CANTalon frontLeft;
		CANTalon backLeft;
		CANTalon frontRight;
		CANTalon backRight;


	std::string name(void);
	DrivePickupSubsystem(CORERobot& robot):
		CORESubsystem(robot),
		frontLeft(13),
		backLeft(12),
		frontRight(10),
		backRight(11)

		{
			//start false to avoid error
			frontLeft.SetSafetyEnabled(false);
			frontRight.SetSafetyEnabled(false);
			backLeft.SetSafetyEnabled(false);
			backRight.SetSafetyEnabled(false);
			frontLeft.Set(0.0);
			frontRight.Set(0.0);
			backLeft.Set(0.0);
			backRight.Set(0.0);
		}

	void robotInit(void);
	void teleopInit(void);
	void teleop(void);

void teleopEnd(void);
};








#endif

