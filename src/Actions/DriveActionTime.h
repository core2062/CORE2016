/*
 * DriveAction.h
 *
 *  Created on: Jan 25, 2016
 *      Author: Draven
 */

#ifndef SRC_ACTIONS_DRIVEACTIONTIME_H_
#define SRC_ACTIONS_DRIVEACTIONTIME_H_

#include "CoreLib/COREAuto.h"

using namespace CORE;

class DriveActionTime : public WaitAction{

	double avgDist = 0.0;
	double speed = 0;
	int direction = 1;
	//variables

public:

	//			robot.motorMap[LIFT_MOTOR]->Set(FORWARD);



	DriveActionTime(CORERobot& robot, double duration, double speed, int direction = 1):
		WaitAction(robot, duration),
		speed(speed)
		{

		};

	void init(){
		//getting sensor values
		robot.motorMap[FRONT_LEFT]->SetEncPosition(0);
		robot.motorMap[FRONT_RIGHT]->SetEncPosition(0);
		robot.outLog.appendLog("Drive Time Action Start");
		robot.motorMap[FRONT_LEFT]->Set(speed*direction);
		robot.motorMap[FRONT_RIGHT]->Set(speed*direction);
		robot.motorMap[BACK_LEFT]->Set(speed*direction);
		robot.motorMap[BACK_RIGHT]->Set(speed*direction);

	}
	void end(){
		robot.motorMap[FRONT_LEFT]->Set(0.0);
		robot.motorMap[FRONT_RIGHT]->Set(0.0);
		robot.motorMap[BACK_LEFT]->Set(0.0);
		robot.motorMap[BACK_RIGHT]->Set(0.0);
		robot.outLog.appendLog("Drive Action End");
	}


	~DriveActionTime(){

	}
};




#endif /* SRC_ACTIONS_DRIVEACTION_H_ */
