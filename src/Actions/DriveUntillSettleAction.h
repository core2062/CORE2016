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
	bool downRamp = false;
	double rampThreshold = 7.0; // Threshold for gyro to determine it's on the ramp
	double rateThreshold = 8.0; //Threshold to determine rate is small enough to consider it's stable



	DriveUntillSettleAction(CORERobot& robot, double speed):
		OrderAction(robot),
		speed(speed)
	{

	};

	void init(){
		itrTimer.Reset();
		itrTimer.Start();
		robot.outLog.appendLog("Drive Settle Action Start");

	}
	void end(){
		itrTimer.Stop();
		robot.motorMap[BACK_RIGHT]->Set(0.0);
		robot.motorMap[BACK_LEFT]->Set(0.0);
		robot.motorMap[FRONT_RIGHT]->Set(0.0);
		robot.motorMap[FRONT_LEFT]->Set(0.0);
		robot.motorMap[FRONT_LEFT]->SetEncPosition(0);
		robot.motorMap[FRONT_RIGHT]->SetEncPosition(0);
		robot.outLog.appendLog("Drive Settle Action End");
	}
	ControlFlow autoCall(){
#ifdef USE_NAVX
		pitch = robot.ahrs->GetPitch();
#else
		return END;
#endif
		// Calc pitch rate
		SmartDashboard::PutNumber("Gyro Yaw",robot.ahrs->GetYaw());
		if(itrTimer.Get() > 1){
			pitchRate = oldPitch-pitch;
			oldPitch = pitch;
			itrTimer.Reset();
		}
		if(pitch > rampThreshold){
			robot.outLog.appendLog("Drive Settle Action Pitch High");
			toRamp=true;
		}
		if(pitch < -rampThreshold){
			robot.outLog.appendLog("Drive Settle Action Pitch Low");
			downRamp = true;
		}
		if((toRamp && downRamp) && pitchRate >-1.0 /*rateThreshold*/ /*&& pitch > -rampThreshold*/){ //may need this if it stops before fully off the ramp, but if added it may go to far
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
