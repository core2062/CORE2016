/*
 * DriveUntillSettleAction.h
 *
 *  Created on: Feb 1, 2016
 *      Author: Draven
 */

#ifndef SRC_ACTIONS_DRIVEUNTILLSETTLEACTION_H_
#define SRC_ACTIONS_DRIVEUNTILLSETTLEACTION_H_

#include "CoreLIB/COREAuto.h"
#include "CORELIB/CORERobot.h"
#include "WPILib.h"
#include <cmath>
#include <iostream>
#include <math.h>


using namespace CORE;

class DriveUntillSettleAction : public OrderAction{

public:
	Timer itrTimer;
	double speed;
	double oldPitch = 0.0;
	double pitch = 0.0;
	double pitchRate = 0.0;
	bool toRamp = false;
	double rampThreshold = 0.0; // Threshold for gyro to determine it's on the ramp
	double rateThreshold = 0.0; //Threshold to determine rate is small enough to consider it's stable



	DriveUntillSettleAction(CORERobot& robot, double speed):
		OrderAction(robot),
		speed(speed)
	{

	};

	void init(){
		itrTimer.Reset();
		itrTimer.Start();

	}
	void end(){
		itrTimer.Stop();
	}
	ControlFlow autoCall(){
		pitch = robot.ahrs->GetPitch();
		// Calc pitch rate
		if(itrTimer.Get() > 1){
			pitchRate = oldPitch-pitch;
			oldPitch = pitch;
			itrTimer.Reset();
		}
		if(pitch > rampThreshold)
			toRamp=true;
		if(toRamp == true && pitchRate < rateThreshold && pitch < rampThreshold /*&& pitch > -rampThreshold*/){ //may need this if it stops before fully off the ramp, but if added it may go to far
			return END;
		} else{
			robot.motorMap[BACK_RIGHT]->Set(speed);
			robot.motorMap[BACK_LEFT]->Set(speed);
			robot.motorMap[FRONT_RIGHT]->Set(speed);
			robot.motorMap[FRONT_LEFT]->Set(speed);
			return CONTINUE;
		}

	}

	~DriveUntillSettleAction(){
	}
};



#endif /* SRC_ACTIONS_DRIVEUNTILLSETTLEACTION_H_ */
