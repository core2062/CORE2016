/*
 * liftSubsystem.cpp
 *
 *  Created on: Dec 8, 2015
 *      Author: core
 */
#include <LiftSubsystem.h>


	void LiftSubsystem::robotInit(void){
		robot.outLog.appendLog("Lift Robot Init");
	}
	void LiftSubsystem::teleopInit(void){
		liftMotor.SetSafetyEnabled(true);
		liftMotor.Set(0);
		liftMotor.SetExpiration(0.25);
		robot.outLog.appendLog("LiftSubsystem: TeleopInit Success");
		robot.joystick.register_axis(LIFT_AXIS, 2, 1);
		robot.joystick.register_button(LIFT_LEVEL1, 2, 1);

	}
	void LiftSubsystem::teleop(void){




		if (!robot.isHybrid){
			double liftAxis = robot.joystick.axis(LIFT_AXIS);
			if(liftAxis < .05 && liftAxis > -.05)
				liftAxis = 0;
			if(liftAxis != 0) {
				liftMotor.Set(robot.joystick.axis(LIFT_AXIS));
			} else if(robot.joystick.button(LIFT_LEVEL1)) {
				setLiftHeight(liftLevel1);
			} else if(robot.joystick.button(LIFT_LEVEL2)) {
				setLiftHeight(liftLevel2);
			}
		}
	}

	void LiftSubsystem::setLiftHeight(smartDB liftLevel){
		liftPID.calculate();
		liftPID.setPoint(SmartDashboard::GetNumber(liftLevel.n,liftLevel.v));
		liftMotor.Set(liftPID.getOutput());
	}
