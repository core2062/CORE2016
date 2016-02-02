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


		SendableChooser driveChooser;

public:

		CANSpeedController::ControlMode mode = CANSpeedController::kPercentVbus;
//		CANSpeedController::ControlMode mode = CANSpeedController::kVoltage;

		VisionSubsystem* vision;

		// Drive Motors
//		CANTalon frontLeft;
//		CANTalon backLeft;
//		CANTalon frontRight;
//		CANTalon backRight;
//		CANTalon pickupMotor;

		Jaguar frontLeft;
		Jaguar backLeft;
		Jaguar frontRight;
		Jaguar backRight;
		Jaguar pickupMotor;
		DoubleSolenoid leftShooter;
		DoubleSolenoid rightShooter;
		Timer shooterTimer;

	std::string name(void);
	DrivePickupSubsystem(CORERobot& robot/*, VisionSubsystem& vision*/):
		CORESubsystem(robot),
		driveChooser(),
//		vision(&vision),
		frontLeft(2),
		backLeft(1),
		frontRight(3),
		backRight(0),
		pickupMotor(5),
		leftShooter(0,1),
		rightShooter(2,3),
		shooterTimer()
		{

//		robot.link(BACK_RIGHT, &backRight);
//		robot.link(BACK_LEFT, &backLeft);
//		robot.link(FRONT_RIGHT, &frontRight);
//		robot.link(FRONT_LEFT, &frontLeft);
//		robot.link(PICKUP, &pickupMotor);

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
			frontRight.SetInverted(true);
			backRight.SetInverted(true);
		}

	void robotInit(void);
	void teleopInit(void);
	void teleop(void);
	void teleopEnd(void);
	void bolderAlign(double lError, double rError, double distAway);
	void setPickupSpeed(double speed);
};

#endif
