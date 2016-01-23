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
	DrivePickupSubsystem* drive;
	CANTalon liftMotor;
	COREPID liftPID;

	LiftSubsystem(CORERobot& robot, DrivePickupSubsystem& drive):
		CORESubsystem(robot),
		drive(&drive),
		liftMotor(14),
		liftPID(0,0,0)

	{
		robot.motorMap.insert(std::pair<motors,CANSpeedController*>(motors::LIFT_MOTOR,&liftMotor));
//		robot.analogSensorMap.insert(std::pair<analogSensors,AnalogInput*>(analogSensors::liftEncoder,&liftEncoder));
//		robot.digitalSensorMap.insert(std::pair<digitalSensors,DigitalInput*>(digitalSensors::TOP_LIFT_LIMIT,&topLimit));
	}
	void robotInit(void);
	void teleopInit(void);
	void teleop(void);
	std::string name(){return "Lift";}
	void changeLiftHeight(liftHeights level);
};

#endif /* SRC_SUBSYSTEMS_LIFTSUBSYSTEM_H_ */