#ifndef SRC_SHOOTERSUBSYSTEM_H_
#define SRC_SHOOTERSUBSYSTEM_H_

#include "CORELIB/CORERobot.h"
#include "WPILib.h"
#include <cmath>
#include <iostream>
#include <math.h>

using namespace CORE;

class ShooterSubsystem: public CORESubsystem{
	DoubleSolenoid rightShooter;
	DoubleSolenoid leftShooter;
//	Solenoid leftShooter;
//	Solenoid rightShooter;
//	Solenoid backShooter;
//	Solenoid exhaustShooter;
	Timer shooterTimer;
	bool shooterFlag = false;
public:
	CANSpeedController::ControlMode mode = CANSpeedController::kPercentVbus;
//	CANSpeedController::ControlMode mode = CANSpeedController::kVoltage;
	std::string name(void);
	ShooterSubsystem(CORERobot& robot):
		CORESubsystem(robot),
		rightShooter(0,1),
		leftShooter(2,3),
//		leftShooter(0),
//		rightShooter(1),
//		backShooter(2),
//		exhaustShooter(3),
		shooterTimer()
		{
//			leftShooter.Set(false);
//			rightShooter.Set(false);
//			backShooter.Set(false);
//			exhaustShooter.Set(false);
			leftShooter.Set(DoubleSolenoid::kOff);
			rightShooter.Set(DoubleSolenoid::kOff);
			robot.link(SHOOTER_LEFT_CYLINDER, &leftShooter);
			robot.link(SHOOTER_RIGHT_CYLINDER, &rightShooter);
		}
	void robotInit(void);
	void teleopInit(void);
	void teleop(void);
	void teleopEnd(void);
	void shoot(void);
};

#endif
