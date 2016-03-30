/*
 * PickupArmAction.h
 *
 *  Created on: Feb 9, 2016
 *      Author: core2062
 */

#ifndef GESTUREROLLERACTION_H_
#define GESTUREROLLERACTION_H_

#include "CoreLIB/COREAuto.h"
#include "CORELIB/CORERobot.h"
#include "WPILib.h"
#include <cmath>
#include <iostream>
#include <math.h>
#include "CORELIB/Constants.h"
#include "CORELIB/COREPID.h"


using namespace CORE;//Added for commit reasons, can be deleted later

class GestureRollerAction : public OrderAction{

public:

	bool bkrd;



	GestureRollerAction(CORERobot& robot, bool background = true):
		OrderAction(robot),
		bkrd(background)
	{
	};



	void init(){

		robot.motorMap[ROLLER]->Set(0.0);

		robot.outLog.appendLog("Gesture Roller Action Start");

	}
	void end(){
		robot.motorMap[ROLLER]->Set(0.0);
		robot.outLog.appendLog("Gesture Roller Action End");
	}

	ControlFlow autoCall(){
		double roller;
		if(robot.gestureSensor.valueReady() && (robot.gestureSensor.getXValue() <130 && robot.gestureSensor.getXValue() > 110)){
			double gesError = robot.gestureSensor.getXValue() - SmartDashboard::GetNumber(gestureCenter.n,gestureCenter.v);
			roller = gesError*SmartDashboard::GetNumber(gestureP.n,gestureP.v);
	//		roller = (roller<0)?0:roller;
		}else{
			roller = .75;
		}
		if(roller == 0){
			return END;
		}
		robot.motorMap[ROLLER]->Set(roller);
		if(bkrd)
			return BACKGROUND;
		else
			return CONTINUE;
	}
		~GestureRollerAction(){}
	};





#endif /* PICKUPARMACTION_H_ */
