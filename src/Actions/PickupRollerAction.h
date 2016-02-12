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

		enum direction{
			IN,
			OUT

		};
		Timer timer;
		double duration;
public:




	PickupRollerAction(CORERobot& robot, enum direction, double duration = 0.1):
		OrderAction(robot),
		direction(direction),
		duration(duration)
	{

	};

	void init(){
	timer.Reset();
	timer.Start();

	}
	void end(){

	}
	ControlFlow autoCall(){
		if(timer.Get() > duration){
			robot.motormap[PICKUP]->Set(0.0);
			return END;
	}
		else{

			if(direction == IN){
				robot.motormap[PICKUP]->Set(FORWARD);
			}

			else{
				robot.motormap[PICKUP]->Set(REVERSE);
			}
			return CONTINUE;

		}
	}
		~PickupRollerAction(){}
	};




#endif /* SRC_ACTIONS_PICKUPROLLERACTION_H_ */
