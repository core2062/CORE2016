/*
 * DriveAction.h
 *
 *  Created on: Jan 25, 2016
 *      Author: Draven
 */

#ifndef SRC_ACTIONS_DRIVEACTION_H_
#define SRC_ACTIONS_DRIVEACTION_H_

#include "CoreLib/COREAuto.h"

using namespace CORE;

class DriveAction : public ConditionAction{


	double targetDistance = 0;
	double speed = 0;
	//varriables

public:

	//			robot.motorMap[LIFT_MOTOR]->Set(FORWARD);

	virtual bool startCondition(){
		return false;
	}
	virtual bool endCondition(){
		return false;
	}
	DriveAction(CORERobot& robot, double targetDistance, double speed):
		ConditionAction(robot),
		targetDistance(targetDistance),
		speed(speed)
		{

		};

	void init(){
		//getting sensor values

	}
	void end(){}
	ControlFlow autoCall(){


		//main logic

		return CONTINUE;
	}

	~DriveAction(){

	}
};




#endif /* SRC_ACTIONS_DRIVEACTION_H_ */
