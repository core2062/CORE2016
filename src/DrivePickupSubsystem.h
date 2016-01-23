#ifndef DRIVEPICKUPSUBSYSTEM_H
#define DRIVEPICKUPSUBSYSTEM_H

#include "CORELIB/CORERobot.h"
#include "WPILib.h"
#include <cmath>
#include <iostream>
#include <math.h>
#include <navx2.0/AHRS.h>
#include "VisionSubsystem.h"

using namespace CORE;


class DrivePickupSubsystem: public CORESubsystem{



public:

		CANSpeedController::ControlMode mode = CANSpeedController::kPercentVbus;
//		CANSpeedController::ControlMode mode = CANSpeedController::kVoltage;

		VisionSubsystem* vision;

		// Drive Motors
		Jaguar frontLeft;
		Jaguar backLeft;
		Jaguar frontRight;
		Jaguar backRight;


	std::string name(void);
	DrivePickupSubsystem(CORERobot& robot, VisionSubsystem& vision):
		CORESubsystem(robot),
		vision(&vision),
		frontLeft(13),
		backLeft(14),
		frontRight(20),
		backRight(16)

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
	void bolderAlign(int lError, int rError);
};








#endif

