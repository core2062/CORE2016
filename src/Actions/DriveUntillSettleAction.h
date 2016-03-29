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
	Timer maxDur;
	double speed;
	double oldPitch = 0.0;
	double pitch = 0.0;
	double pitchRate = 0.0;
	bool toRamp = false;
	bool downRamp = false;
	double rampThreshold = 7.0; // Threshold for gyro to determine it's on the ramp
	double rateThreshold = 8.0; //Threshold to determine rate is small enough to consider it's stable
	bool useMean;
	std::vector<double> pitches = {0};



	DriveUntillSettleAction(CORERobot& robot, double speed, bool average = false):
		OrderAction(robot),
		speed(speed),
		useMean(average)
	{

	};

	void init(){
		itrTimer.Reset();
		itrTimer.Start();
		maxDur.Reset();
		maxDur.Start();
		robot.outLog.appendLog("Drive Settle Action Start");
		rampThreshold = (useMean)?12:rampThreshold;
		robot.motorMap[FRONT_LEFT]->SetEncPosition(0);
		robot.motorMap[FRONT_RIGHT]->SetEncPosition(0);
		if(useMean){
			std::cout<<"WARNING: Going over moat" << std::endl;
		}

	}
	void end(){
		itrTimer.Stop();
		maxDur.Stop();
		robot.motorMap[BACK_RIGHT]->Set(0.0);
		robot.motorMap[BACK_LEFT]->Set(0.0);
		robot.motorMap[FRONT_RIGHT]->Set(0.0);
		robot.motorMap[FRONT_LEFT]->Set(0.0);
		robot.motorMap[FRONT_LEFT]->SetEncPosition(0);
		robot.motorMap[FRONT_RIGHT]->SetEncPosition(0);
		robot.outLog.appendLog("Drive Settle Action End");
	}

	bool getPositive(){
		for(auto i:pitches){
			if(i < -.25){
				return false;
			}
		}
		return true;
	}


	ControlFlow autoCall(){
#ifdef USE_NAVX
		pitch = robot.ahrs->GetPitch();
#else
		return END;
#endif
		// Calc pitch rate
		SmartDashboard::PutNumber("Gyro Yaw",robot.ahrs->GetYaw());
		if(maxDur.Get() > SmartDashboard::GetNumber(autoDefenseTime.n,autoDefenseTime.v)){
			return END;
		}
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
		if(toRamp && downRamp){
			pitches.push_back(pitch);
			if(pitches.size()>5){
				pitches.erase(pitches.begin());
			}
		}
		if(((robot.digitalSensorMap[BACK_PHOTO]->Get() == true && robot.digitalSensorMap[FRONT_PHOTO]->Get() == true) &&(toRamp && downRamp)) && ((useMean)?getPositive():pitch >-1.0) /*rateThreshold*/ /*&& pitch > -rampThreshold*/){ //may need this if it stops before fully off the ramp, but if added it may go to far
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
