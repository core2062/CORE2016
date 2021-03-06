#ifndef DRIVEPICKUPSUBSYSTEM_H
#define DRIVEPICKUPSUBSYSTEM_H

#include "CORELIB/CORERobot.h"
#include "WPILib.h"
#include <cmath>
#include <iostream>
#include <math.h>
#include "VisionSubsystem.h"
#include "CORELIB/COREAuto.h"
#include "Actions/Actions.h"
#include "CORELIB/COREPID.h"

using namespace CORE;

class DrivePickupSubsystem: public CORESubsystem{
		AutoControl* teleSeq;
    	bool oldRot = 0.0;
    	int resetQ = 0;
    	double gyroSet = 0.0;
    	int oldBallX = -1;
    	int oldGoalX = -1;
    	double oldGyroError = 0.0;
    	bool autoPickupFlag = false;
    	Timer autoPickupTimer;
    	int driveDirection = 1;
		SendableChooser driveChooser;
		double oldGyroYaw = 0.0;
		//Timer gyroITimer;
		double gyroIntegral = 0.0;
		double tempP = 0.0;
		bool oldGoalButton = false;
		int goalFlag = 0;
		double oldPickupVal = 0.0;
		double oldHeight = 0.0;
		bool intaking = false;
		bool seenSmall = false;
public:
		double drive_mag = 0.0;
		double drive_rot = 0.0;
		CANSpeedController::ControlMode mode = CANSpeedController::kPercentVbus;
		VisionSubsystem* vision;
		// Drive Motors
		CANTalon frontLeft;
		CANTalon backLeft;
		CANTalon frontRight;
		CANTalon backRight;
		CANTalon leftPickupMotor;
		CANTalon rightPickupMotor;
		CANTalon rollerMotor;
		AnalogInput leftPot;
		AnalogInput rightPot;
		AnalogInput jumper;
		DigitalInput backPhotoeye;
		DigitalInput frontPhotoeye;
	std::string name(void);
	DrivePickupSubsystem(CORERobot& robot, VisionSubsystem& vision, AutoControl& tele):
		CORESubsystem(robot),
		teleSeq(&tele),
		driveChooser(),
		vision(&vision),

		frontLeft(13),
		backLeft(12),
		frontRight(10),
		backRight(11),
		leftPickupMotor(14),
		rightPickupMotor(15),
		rollerMotor(16),
		leftPot(0),
		rightPot(1),
		jumper(2),
		backPhotoeye(0),
		frontPhotoeye(1)
		//gyroITimer()
		{
			robot.link(BACK_RIGHT, &backRight);
			robot.link(BACK_LEFT, &backLeft);
			robot.link(FRONT_RIGHT, &frontRight);
			robot.link(FRONT_LEFT, &frontLeft);
			robot.link(RIGHT_PICKUP, &rightPickupMotor);
			robot.link(LEFT_PICKUP, &leftPickupMotor);
			robot.link(ROLLER, &rollerMotor);
			robot.link(LEFT_POT, &leftPot);
			robot.link(RIGHT_POT, &rightPot);
			robot.link(BACK_PHOTO, &backPhotoeye);
			robot.link(FRONT_PHOTO, &frontPhotoeye);
			rightPickupMotor.SetSafetyEnabled(false);
			leftPickupMotor.SetSafetyEnabled(false);
			rollerMotor.SetSafetyEnabled(false);
			frontLeft.SetSafetyEnabled(false);
			frontRight.SetSafetyEnabled(false);
			backLeft.SetSafetyEnabled(false);
			backRight.SetSafetyEnabled(false);
			frontRight.SetInverted(true);
			backRight.SetInverted(true);
			leftPickupMotor.SetInverted(true);
			rightPickupMotor.Set(0.0);
			leftPickupMotor.Set(0.0);
			rollerMotor.Set(0.0);
			frontLeft.Set(0.0);
			frontRight.Set(0.0);
			backLeft.Set(0.0);
			backRight.Set(0.0);
			frontLeft.SetFeedbackDevice(CANTalon::QuadEncoder);
			frontRight.SetFeedbackDevice(CANTalon::QuadEncoder);
//			rightPickupMotor.SetFeedbackDevice(CANTalon::AnalogPot);
//			rightPickupMotor.SetControlMode(CANSpeedController::kPosition);
//			rightPickupMotor.SetP(SmartDashboard::GetNumber(pickupP.n,pickupP.v));
//			leftPickupMotor.SetFeedbackDevice(CANTalon::AnalogPot);
//			leftPickupMotor.SetControlMode(CANSpeedController::kPosition);
//			leftPickupMotor.SetP(SmartDashboard::GetNumber(pickupP.n,pickupP.v));
			frontLeft.ConfigEncoderCodesPerRev(ENCODER_RES);
			frontRight.ConfigEncoderCodesPerRev(ENCODER_RES);
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
	void setPickupHeight(smartDB height, smartDB heightL);
	void setPickupHeight(double height);
	bool autoPickup(void);
	double leftPotValue();
	double rightPotValue();
};

#endif
