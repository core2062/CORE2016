/*
 * ShootAction.h
 *
 *  Created on: Jan 30, 2016
 *      Author: Draven
 */

#ifndef SRC_ACTIONS_RESETYAWACTION_H_
#define SRC_ACTIONS_RESETYAWACTION_H_

#include "CoreLIB/COREAuto.h"
#include "CORELIB/CORERobot.h"
#include "WPILib.h"
#include <cmath>
#include <iostream>
#include <math.h>
// #include "DrivePickupSubsystem.h"


using namespace CORE;

class ResetYawAction : public OrderAction{

public:




	ResetYawAction(CORERobot& robot):
		OrderAction(robot)
	{

	};

	void init(){

		robot.outLog.appendLog("Reset Yaw Action Start");

	}
	void end(){

		robot.outLog.appendLog("Reset Yaw Action End");
	}
	ControlFlow autoCall(){
		robot.ahrs->ZeroYaw();
		return END;






	}

	~ResetYawAction(){

	}
};



#endif /* SRC_ACTIONS_SHOOTACTION_H_ */
