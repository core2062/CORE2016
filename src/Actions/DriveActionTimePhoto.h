/*
 * DriveAction.h
 *
 *  Created on: Jan 25, 2016
 *      Author: Draven
 */

#ifndef SRC_ACTIONS_DRIVEACTIONTIMEPHOTO_H_
#define SRC_ACTIONS_DRIVEACTIONTIMEPHOTO_H_

#include "CoreLib/COREAuto.h"

using namespace CORE;

class DriveActionTimePhoto : public WaitAction{

	double avgDist = 0.0;
	double speed = 0;
	//variables

public:

	//			robot.motorMap[LIFT_MOTOR]->Set(FORWARD);



	DriveActionTimePhoto(CORERobot& robot, double duration, double speed):
		WaitAction(robot, duration),
		speed(speed)
		{

		};

	void init(){
		//getting sensor values
		robot.motorMap[FRONT_LEFT]->SetEncPosition(0);
		robot.motorMap[FRONT_RIGHT]->SetEncPosition(0);
		robot.outLog.appendLog("Drive Time Action Start");
		robot.motorMap[FRONT_LEFT]->Set(speed);
		robot.motorMap[FRONT_RIGHT]->Set(speed);
		robot.motorMap[BACK_LEFT]->Set(speed);
		robot.motorMap[BACK_RIGHT]->Set(speed);

	}
	void end(){
		robot.motorMap[FRONT_LEFT]->Set(0.0);
		robot.motorMap[FRONT_RIGHT]->Set(0.0);
		robot.motorMap[BACK_LEFT]->Set(0.0);
		robot.motorMap[BACK_RIGHT]->Set(0.0);
		robot.outLog.appendLog("Drive Action End");
	}

	ControlFlow autoCall(){

		if(!robot.digitalSensorMap[BACK_PHOTO]->Get()){
			return WaitAction::autoCall();
		}else{
			return CONTINUE;
		}

	}


	~DriveActionTimePhoto(){

	}
};




#endif /* SRC_ACTIONS_DRIVEACTION_H_ */
