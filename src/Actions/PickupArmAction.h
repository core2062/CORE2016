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
#include "CORELIB/Constants.h"
#include "CORELIB/COREPID.h"


using namespace CORE;//Added for commit reasons, can be deleted later

class PickupArmAction : public OrderAction{

public:
	Timer timer;

	double speed = 0.0;
	double duration = 0.0;
	smartDB* height = (new smartDB (std::string("null"), 0.0));
	COREPID leftPickupPID;
	COREPID rightPickupPID;



	PickupArmAction(CORERobot& robot, double speed, double duration):
		OrderAction(robot),
		speed(speed),
		leftPickupPID(0,0,0),
		rightPickupPID(0,0,0)
	{
	};
	PickupArmAction(CORERobot& robot, smartDB height):
		OrderAction(robot),
		height(&height),
		leftPickupPID(0,0,0),
		rightPickupPID(0,0,0)
	{
	};


	void init(){
		timer.Reset();
		timer.Start();

	}
	void end(){
		timer.Stop();
	}

	ControlFlow autoCall(){
		if(height->n == std::string("null")){
			if(timer.Get() < duration){
				robot.motorMap[LEFT_PICKUP]->Set(speed);
				robot.motorMap[RIGHT_PICKUP]->Set(speed);
				return CONTINUE;
			}else{
				robot.motorMap[LEFT_PICKUP]->Set(0.0);
				robot.motorMap[RIGHT_PICKUP]->Set(0.0);
				return END;
			}
		}else{
			//Encoder must be added to finish this
			leftPickupPID.calculate();
			rightPickupPID.calculate();
			leftPickupPID.setPoint(SmartDashboard::GetNumber(height->n,height->v));
			rightPickupPID.setPoint(SmartDashboard::GetNumber(height->n,height->v));
			robot.motorMap[LEFT_PICKUP]->Set(leftPickupPID.getOutput());
			robot.motorMap[RIGHT_PICKUP]->Set(rightPickupPID.getOutput());
		}
	}
		~PickupArmAction(){}
	};





#endif /* PICKUPARMACTION_H_ */
