/*
 * liftSubsystem.h
 *
 *  Created on: Dec 8, 2015
 *      Author: core
 */

#ifndef SRC_SUBSYSTEMS_LIFTSUBSYSTEM_H_
#define SRC_SUBSYSTEMS_LIFTSUBSYSTEM_H_

#include "CORELIB/CORERobot.h"
#include "CORELIB/COREPID.h"
#include "WPILib.h"
#include <string>
#include "DrivePickupSubsystem.h"

using namespace CORE;

class LiftSubsystem : public CORESubsystem {
public:
//	DrivePickupSubsystem* drive;
	CANTalon liftMotor;
	COREPID liftPID;

	LiftSubsystem(CORERobot& robot/*, DrivePickupSubsystem& drive*/):
		CORESubsystem(robot),
//		drive(&drive),
		liftMotor(14),
		liftPID(0,0,0)

	{
		robot.link(LIFT_MOTOR, &liftMotor);
	}
	void robotInit(void);
	void teleopInit(void);
	void teleop(void);
	std::string name(){return "Lift";}
	void setLiftHeight(smartDB liftLevel);
};

#endif /* SRC_SUBSYSTEMS_LIFTSUBSYSTEM_H_ */
