#ifndef DRIVEPICKUPSUBSYSTEM_H
#define DRIVEPICKUPSUBSYSTEM_H


#include "CORELIB/CORERobot.h"
#include "WPILib.h"
#include <cmath>
#include <iostream>
#include <math.h>
#include "VisionSubsystem.h"
#include "CORELIB/COREAuto.h"
#include "Actions/DriveAction.h"
#include "CORELIB/COREPID.h"



using namespace CORE;


class DrivePickupSubsystem: public CORESubsystem{


    	bool oldRot = 0.0;
    	int resetQ = 0;
    	double gyroSet = 0.0;

    	int oldBallX = -1;
    	int oldGoalX = -1;

		SendableChooser driveChooser;

public:


		CANSpeedController::ControlMode mode = CANSpeedController::kPercentVbus;
//		CANSpeedController::ControlMode mode = CANSpeedController::kVoltage;

		VisionSubsystem* vision;

		// Drive Motors
		CANTalon frontLeft;
		CANTalon backLeft;
		CANTalon frontRight;
		CANTalon backRight;
		CANTalon leftPickupMotor;
		CANTalon rightPickupMotor;
		CANTalon rollerMotor;

		COREPID leftPickupPID;
		COREPID rightPickupPID;


	std::string name(void);
	DrivePickupSubsystem(CORERobot& robot, VisionSubsystem& vision):
		CORESubsystem(robot),
		driveChooser(),
		vision(&vision),
		frontLeft(13),
		backLeft(12),
		frontRight(10),
		backRight(11),
		leftPickupMotor(-1),
		rightPickupMotor(-1),
		rollerMotor(-1),
		leftPickupPID(0,0,0),
		rightPickupPID(0,0,0)

		{

		robot.link(BACK_RIGHT, &backRight);
		robot.link(BACK_LEFT, &backLeft);
		robot.link(FRONT_RIGHT, &frontRight);
		robot.link(FRONT_LEFT, &frontLeft);
		robot.link(RIGHT_PICKUP, &rightPickupMotor);
		robot.link(LEFT_PICKUP, &leftPickupMotor);
		robot.link(ROLLER, &rollerMotor);

			//start false to avoid error
			rightPickupMotor.SetSafetyEnabled(false);
			leftPickupMotor.SetSafetyEnabled(false);
			rollerMotor.SetSafetyEnabled(false);
			frontLeft.SetSafetyEnabled(false);
			frontRight.SetSafetyEnabled(false);
			backLeft.SetSafetyEnabled(false);
			backRight.SetSafetyEnabled(false);
			frontRight.SetInverted(true);
			backRight.SetInverted(true);

			rightPickupMotor.Set(0.0);
			leftPickupMotor.Set(0.0);
			rollerMotor.Set(0.0);
			frontLeft.Set(0.0);
			frontRight.Set(0.0);
			backLeft.Set(0.0);
			backRight.Set(0.0);
			frontLeft.SetFeedbackDevice(CANTalon::QuadEncoder);
			backLeft.SetFeedbackDevice(CANTalon::QuadEncoder);
			frontRight.SetFeedbackDevice(CANTalon::QuadEncoder);
			backRight.SetFeedbackDevice(CANTalon::QuadEncoder);
			frontLeft.ConfigEncoderCodesPerRev(1024);
			backLeft.ConfigEncoderCodesPerRev(1024);
			frontRight.ConfigEncoderCodesPerRev(1024);
			backRight.ConfigEncoderCodesPerRev(1024);
		}

	void robotInit(void);
	void teleopInit(void);
	void teleop(void);
	void teleopEnd(void);
	void bolderAlign(double lError, double rError, double distAway);
	void setFrontLeftMotor(double speed);
	void setFrontRightMotor(double speed);
	void setBackLeftMotor(double speed);
	void setBackRightMotor(double speed);
	void setPickupMotor(double speed);
	void setPickupSpeed(double speed);
	void setPickupHeight(smartDB height);
};








#endif

