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



public:

		CANSpeedController::ControlMode mode = CANSpeedController::kPercentVbus;
//		CANSpeedController::ControlMode mode = CANSpeedController::kVoltage;


	std::string name(void);
	ShooterSubsystem(CORERobot& robot):
		CORESubsystem(robot)

		{

		}

	void robotInit(void);
	void teleopInit(void);
	void teleop(void);
	void teleopEnd(void);
};

#endif /* SRC_SHOOTERSUBSYSTEM_H_ */
