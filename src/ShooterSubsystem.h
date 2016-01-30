/*
 * ShooterSubsystem.h
 *
 *  Created on: Jan 15, 2016
 *      Author: core
 */

#ifndef SRC_SHOOTERSUBSYSTEM_H_
#define SRC_SHOOTERSUBSYSTEM_H_

#include "CORELIB/CORERobot.h"
#include "WPILib.h"
#include <cmath>
#include <iostream>
#include <math.h>

using namespace CORE;


class ShooterSubsystem: public CORESubsystem{

	DoubleSolenoid leftShooter;
	DoubleSolenoid rightShooter;
	Timer shooterTimer;

public:

		CANSpeedController::ControlMode mode = CANSpeedController::kPercentVbus;
//		CANSpeedController::ControlMode mode = CANSpeedController::kVoltage;


	std::string name(void);
	ShooterSubsystem(CORERobot& robot):
		CORESubsystem(robot),
		leftShooter(0,1),
		rightShooter(2,3),
		shooterTimer()

		{
			leftShooter.Set(DoubleSolenoid::kReverse);
			rightShooter.Set(DoubleSolenoid::kReverse);
			robot.link(SHOOTER_LEFT_CYLINDER, &leftShooter);
			robot.link(SHOOTER_RIGHT_CYLINDER, &rightShooter);
		}

	void robotInit(void);
	void teleopInit(void);
	void teleop(void);
	void teleopEnd(void);
	void shoot(void);
};

#endif /* SRC_SHOOTERSUBSYSTEM_H_ */
