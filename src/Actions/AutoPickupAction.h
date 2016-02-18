/*
 * AutoPickupAction.h
 *
 *  Created on: Feb 17, 2016
 *      Author: Draven
 */

#ifndef SRC_ACTIONS_AUTOPICKUPACTION_H_
#define SRC_ACTIONS_AUTOPICKUPACTION_H_
/*
#include "CoreLIB/COREAuto.h"
#include "CORELIB/CORERobot.h"
#include "WPILib.h"
#include <cmath>
#include <iostream>
#include <math.h>


using namespace CORE;

class AutoPickupAction : public OrderAction{

	double leftPot = robot.analogSensorMap[LEFT_POT]->GetValue();
	double rightPot = robot.analogSensorMap[RIGHT_POT]->GetValue();
//	double rollerMotor = robot.motorMap[ROLLER];
//	double leftMotor = robot.motorMap[LEFT_PICKUP];
//	double rightMotor = robot.motorMap[RIGHT_PICKUP];
	bool flag = false;


public:

	AutoPickupAction(CORERobot& robot):
		OrderAction(robot)
	{

	};

	void init(){}
	void end(){
		robot.motorMap[ROLLER]->Set(0.0);
		robot.motorMap[LEFT_PICKUP]->Set(0.0);
		robot.motorMap[RIGHT_PICKUP]->Set(0.0);
	}
	ControlFlow autoCall(){



	}

	~AutoPickupAction(){

	}
};
*/
#endif /* SRC_ACTIONS_AUTOPICKUPACTION_H_ */
