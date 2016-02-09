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

	double avgDist = 0.0;
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
		robot.motorMap[FRONT_LEFT]->SetEncPosition(0);
		robot.motorMap[FRONT_RIGHT]->SetEncPosition(0);
		robot.motorMap[BACK_LEFT]->SetEncPosition(0);
		robot.motorMap[BACK_RIGHT]->SetEncPosition(0);


	}
	void end(){}
	ControlFlow autoCall(){
		avgDist = (robot.motorMap[FRONT_LEFT]->GetEncPosition()+robot.motorMap[FRONT_RIGHT]->GetEncPosition()+
		robot.motorMap[BACK_LEFT]->GetEncPosition()+robot.motorMap[BACK_RIGHT]->GetEncPosition())/4;
		if(avgDist < targetDistance)
			return CONTINUE;
		else
			return END;
		//main logic
	}

	~DriveAction(){

	}
};




#endif /* SRC_ACTIONS_DRIVEACTION_H_ */
