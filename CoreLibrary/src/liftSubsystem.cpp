/*
 * liftSubsystem.cpp
 *
 *  Created on: Dec 8, 2015
 *      Author: core
 */
#include "liftSubsystem.h"


	void LiftSubsystem::robotInit(void){
		robot.outLog.appendLog("Lift Robot Init");
	}
	void LiftSubsystem::teleopInit(void){
		liftMotor.SetSafetyEnabled(true);
		liftMotor.Set(0);
		liftMotor.SetExpiration(0.25);
		robot.outLog.appendLog("LiftSubsystem: TeleopInit Success");

	}
	void LiftSubsystem::teleop(void){


	}






