/*
 * ShootAction.h
 *
 *  Created on: Jan 30, 2016
 *      Author: Draven
 */

#ifndef SRC_ACTIONS_STOPHYBRIDACTION_H_
#define SRC_ACTIONS_STOPHYBRIDACTION_H_

#include "CoreLIB/COREAuto.h"
#include "CORELIB/CORERobot.h"
#include "WPILib.h"
#include <cmath>
#include <iostream>
#include <math.h>
// #include "DrivePickupSubsystem.h"


using namespace CORE;

class StopHybridAction : public OrderAction{

public:




	StopHybridAction(CORERobot& robot):
		OrderAction(robot)
	{

	};

	void init(){

		robot.outLog.appendLog("Stop Hybrid Action Start");

	}
	void end(){

		robot.outLog.appendLog("Stop Hybrid Action End");
	}
	ControlFlow autoCall(){
		robot.isHybrid = false;
		return END;






	}

	~StopHybridAction(){

	}
};



#endif /* SRC_ACTIONS_SHOOTACTION_H_ */
