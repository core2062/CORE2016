#ifndef DRIVEPICKUPSUBSYSTEM_H
#define DRIVEPICKUPSUBSYSTEM_H

#include "CORELIB/CORERobot.h"
#include "WPILib.h"
#include <cmath>
#include <iostream>
#include <math.h>
#include "VisionSubsystem.h"


//NavX stuff
#include <navx2.0/AHRS.h>

/* NOTE:  Comment in only ONE of the following definitions. */

//#define ENABLE_IMU
//#define ENABLE_IMU_ADVANCED
#define ENABLE_AHRS





using namespace CORE;


class DrivePickupSubsystem: public CORESubsystem{


//        SerialPort *serial_port;




    	bool oldRot = 0.0;
    	int resetQ = 0;
    	double gyroSet = 0.0;

    	int oldBallX = -1;
    	int oldGoalX = -1;

public:

#if defined(ENABLE_AHRS)
        AHRS *ahrs;
#elif defined(ENABLE_IMU_ADVANCED)
        IMUAdvanced *ahrs;
#else // ENABLE_IMU
        IMU *ahrs;
#endif

		CANSpeedController::ControlMode mode = CANSpeedController::kPercentVbus;
//		CANSpeedController::ControlMode mode = CANSpeedController::kVoltage;

		VisionSubsystem* vision;

		// Drive Motors
		CANTalon frontLeft;
		CANTalon backLeft;
		CANTalon frontRight;
		CANTalon backRight;
		CANTalon pickupMotor;


	std::string name(void);
	DrivePickupSubsystem(CORERobot& robot, VisionSubsystem& vision):
		CORESubsystem(robot),
		vision(&vision),
		frontLeft(13),
		backLeft(14),
		frontRight(20),
		backRight(16),
		pickupMotor(-1)

		{

		robot.link(BACK_RIGHT, &backRight);
		robot.link(BACK_LEFT, &backLeft);
		robot.link(FRONT_RIGHT, &frontRight);
		robot.link(FRONT_LEFT, &frontLeft);
		robot.link(PICKUP, &pickupMotor);

			//start false to avoid error
			frontLeft.SetSafetyEnabled(false);
			frontRight.SetSafetyEnabled(false);
			backLeft.SetSafetyEnabled(false);
			backRight.SetSafetyEnabled(false);
			pickupMotor.SetSafetyEnabled(false);
			frontLeft.Set(0.0);
			frontRight.Set(0.0);
			backLeft.Set(0.0);
			backRight.Set(0.0);
			pickupMotor.Set(0.0);
		}

	void robotInit(void);
	void teleopInit(void);
	void teleop(void);
	void teleopEnd(void);
	void bolderAlign(double lError, double rError, double distAway);
	void setPickupSpeed(double speed);
};








#endif

