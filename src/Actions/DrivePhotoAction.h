/*
 * DriveAction.h
 *
 *  Created on: Jan 25, 2016
 *      Author: Draven
 */

#ifndef SRC_ACTIONS_DRIVEPHOTOACTION_H_
#define SRC_ACTIONS_DRIVEPHOTOACTION_H_

#include "CoreLib/COREAuto.h"

using namespace CORE;

class DrivePhotoAction : public OrderAction{

	double avgDist = 0.0;
	double targetDistance = 0;
	double speed = 0;
	digitalSensors eye;
	//variables

public:

	//			robot.motorMap[LIFT_MOTOR]->Set(FORWARD);


	virtual bool endCondition(){
		return false;
	}
	virtual bool backgroundCondition(){
		return false;
	}
	DrivePhotoAction(CORERobot& robot, double targetDistance, double speed, digitalSensors eye):
		OrderAction(robot),
		targetDistance(targetDistance),
		speed(speed),
		eye(eye)
		{

		};

	void init(){
		//getting sensor values
		robot.motorMap[FRONT_LEFT]->SetEncPosition(0);
		robot.motorMap[FRONT_RIGHT]->SetEncPosition(0);
		robot.outLog.appendLog("Drive Photo Action Start");

	}
	void end(){
		robot.motorMap[FRONT_LEFT]->Set(0.0);
		robot.motorMap[FRONT_RIGHT]->Set(0.0);
		robot.motorMap[BACK_LEFT]->Set(0.0);
		robot.motorMap[BACK_RIGHT]->Set(0.0);
		robot.motorMap[FRONT_LEFT]->SetEncPosition(0);
		robot.motorMap[FRONT_RIGHT]->SetEncPosition(0);
		robot.outLog.appendLog("Drive Photo Action End");
	}
	ControlFlow autoCall(){
		robot.motorMap[FRONT_LEFT]->Set(speed);
		robot.motorMap[FRONT_RIGHT]->Set(speed);
		robot.motorMap[BACK_LEFT]->Set(speed);
		robot.motorMap[BACK_RIGHT]->Set(speed);
		if(robot.digitalSensorMap[eye]->Get()){
			return END;
		}
		return CONTINUE;
		//main logic
	}

	~DrivePhotoAction(){

	}
};




#endif /* SRC_ACTIONS_DRIVEACTION_H_ */
