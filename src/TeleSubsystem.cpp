/*
 * TeleSubsystem.cpp
 *
 *  Created on: Feb 12, 2016
 *      Author: Joshua
 */
#include "TeleSubsystem.h"


	void TeleSubsystem::robotInit(void){
		robot.outLog.appendLog("TeleAuto Robot Init");
	}
	void TeleSubsystem::teleopInit(void){
		robot.outLog.appendLog("TeleSubsystem: TeleopInit Success");
		robot.joystick.register_combo(HYBRID_GOTO_SDXY, 2, 7);
		oldGyro = getHeading();

	}
	void TeleSubsystem::teleop(){


		if (!robot.isHybrid){

		}


		if (!robot.isHybrid && robot.joystick.combo(HYBRID_GOTO_SDXY)){
			robot.isHybrid = true;
			seq.reset();





		}





	}




