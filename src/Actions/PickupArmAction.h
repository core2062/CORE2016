/*
 * PickupArmAction.h
 *
 *  Created on: Feb 9, 2016
 *      Author: core2062
 */

#ifndef PICKUPARMACTION_H_
#define PICKUPARMACTION_H_
#include "CoreLIB/COREAuto.h"
#include "CORELIB/CORERobot.h"
#include "WPILib.h"
#include <cmath>
#include <iostream>
#include <math.h>


using namespace CORE;

class PickupArmAction : public OrderAction{

public:




	PickupArmAction(CORERobot& robot, double speed):
		OrderAction(robot)

	{

	};

	void init(){


	}
	void end(){

	}
	ControlFlow autoCall(){

	}
		~PickupArmAction(){}
	};





#endif /* PICKUPARMACTION_H_ */
