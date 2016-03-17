/*
 * ShootAction.h
 *
 *  Created on: Jan 30, 2016
 *      Author: Draven
 */

#ifndef SRC_ACTIONS_SHOOTACTION_H_
#define SRC_ACTIONS_SHOOTACTION_H_

#include "CoreLIB/COREAuto.h"
#include "CORELIB/CORERobot.h"
#include "WPILib.h"
#include <cmath>
#include <iostream>
#include <math.h>
// #include "DrivePickupSubsystem.h"


using namespace CORE;

class ShootAction : public OrderAction{

public:
	Timer timer;
	Timer timer2;
	bool flag = false;
	bool flag2 = false;
	bool flag3 = false;
	double loadTime;



	ShootAction(CORERobot& robot, double loadTime = 1.5):
		OrderAction(robot),
		loadTime(loadTime)
	{

	};

	void init(){
		timer.Reset();
		timer.Start();

		robot.outLog.appendLog("Shooter Action Start");

	}
	void end(){
		timer.Stop();

		robot.outLog.appendLog("Shooter Action End");
	}
	ControlFlow autoCall(){
		if(!flag && robot.pneumaticMap[SHOOTER_LEFT_CYLINDER]->Get() == DoubleSolenoid::kForward) {
			robot.pneumaticMap[SHOOTER_LEFT_CYLINDER]->Set(DoubleSolenoid::kReverse);
			robot.pneumaticMap[SHOOTER_RIGHT_CYLINDER]->Set(DoubleSolenoid::kReverse);
			flag2 = true;
			timer.Reset();
		}
		if(flag2){
			if(timer.Get() >= loadTime){
				if(flag2)
					flag2 = false;
				return CONTINUE;
			}
		}else if(!flag && !flag2){
			timer.Reset();
			robot.pneumaticMap[SHOOTER_LEFT_CYLINDER]->Set(DoubleSolenoid::kForward);
			robot.pneumaticMap[SHOOTER_RIGHT_CYLINDER]->Set(DoubleSolenoid::kForward);
			flag = true;
			return BACKGROUND;
		}

		if(timer.Get() >= loadTime && flag){
			if(flag3 == false){
				timer2.Reset();
				timer2.Start();
				flag3 = true;
			}
			if(timer2.Get() > 2.0){// wait time after  reverse for off
				robot.pneumaticMap[SHOOTER_LEFT_CYLINDER]->Set(DoubleSolenoid::kOff);
				robot.pneumaticMap[SHOOTER_RIGHT_CYLINDER]->Set(DoubleSolenoid::kOff);
				return END;
			} else {
				robot.pneumaticMap[SHOOTER_LEFT_CYLINDER]->Set(DoubleSolenoid::kReverse);
				robot.pneumaticMap[SHOOTER_RIGHT_CYLINDER]->Set(DoubleSolenoid::kReverse);
				return BACKGROUND;
			}

		} else {
			return BACKGROUND;
		}
	}

	~ShootAction(){

	}
};



#endif /* SRC_ACTIONS_SHOOTACTION_H_ */
