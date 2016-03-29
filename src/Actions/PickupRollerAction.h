/*
 * PickupRollerAction.h
 *
 *  Created on: Feb 9, 2016
 *      Author: core2062
 */

#ifndef SRC_ACTIONS_PICKUPROLLERACTION_H_
#define SRC_ACTIONS_PICKUPROLLERACTION_H_
#include "CoreLIB/COREAuto.h"
#include "CORELIB/CORERobot.h"
#include "WPILib.h"
#include <cmath>
#include <iostream>
#include <math.h>


using namespace CORE;//Added to commit, can be deleted later

class PickupRollerAction : public OrderAction{

	Timer timer;

	int directions;
	bool backround;
	double duration;

public:


	PickupRollerAction(CORERobot& robot, direction dir, double duration, bool backround = false):
		OrderAction(robot),
		directions(dir),
		duration(duration),
		backround(backround)
	{

	};

	void init(){
	timer.Reset();
	timer.Start();

	robot.outLog.appendLog("Pickup Roller Action Start");

	}
	void end(){

		robot.outLog.appendLog("Pickup Roller Action End");
	}
	ControlFlow autoCall(){
		if(timer.Get() > duration){
			robot.motorMap[ROLLER]->Set(0.0);
			return END;
	}
		else{

			if(directions == IN){
				robot.motorMap[ROLLER]->Set(FORWARD);
			}

			else{
				robot.motorMap[ROLLER]->Set(REVERSE);
			}
			if(backround)
				return BACKGROUND;
			else
				return CONTINUE;

		}
	}
		~PickupRollerAction(){}
	};




#endif /* SRC_ACTIONS_PICKUPROLLERACTION_H_ */
