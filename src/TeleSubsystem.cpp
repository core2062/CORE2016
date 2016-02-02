/*
 * TeleSubsystem.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: core2062
 */
#include "TeleSubsystem.h"


	void TeleSubsystem::robotInit(void){
		robot.outLog.appendLog("TeleAuto Robot Init");
	}
	void TeleSubsystem::teleopInit(void){
		robot.outLog.appendLog("TeleSubsystem: TeleopInit Success");
		robot.joystick.register_button(HYBRID_GOTO_SDXY, 2, 1, JoystickCache::RISING);

	}
	void TeleSubsystem::teleop(void){




		if (!robot.isHybrid && robot.joystick.button(HYBRID_GOTO_SDXY)){
			robot.isHybrid = true;
			while (robot.tQueue.size()>0){
				robot.tQueue.pop();
			}
			robot.tBackground.clear();





		}
	}





