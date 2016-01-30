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

class ShootAction : public ConditionAction{

public:
	Timer timer;
	bool flag = false;


	virtual bool startCondition(){
		return false;
	}
	virtual bool endCondition(){
		return false;
	}
	ShootAction(CORERobot& robot):
		ConditionAction(robot)
	{

	};

	void init(){
		timer.Reset();
		timer.Start();

	}
	void end(){}
	ControlFlow autoCall(){
		if(flag == false && robot.pneumaticMap[SHOOTER_LEFT_CYLINDER]->Get() == DoubleSolenoid::kReverse){
			timer.Reset();
			robot.pneumaticMap[SHOOTER_LEFT_CYLINDER]->Set(DoubleSolenoid::kForward);
			robot.pneumaticMap[SHOOTER_RIGHT_CYLINDER]->Set(DoubleSolenoid::kForward);
			flag = true;
			return BACKGROUND;
		} else if(flag == false && robot.pneumaticMap[SHOOTER_LEFT_CYLINDER]->Get() == DoubleSolenoid::kForward) {
			robot.pneumaticMap[SHOOTER_LEFT_CYLINDER]->Set(DoubleSolenoid::kReverse);
			robot.pneumaticMap[SHOOTER_RIGHT_CYLINDER]->Set(DoubleSolenoid::kReverse);
		}
		if(timer.Get() >= 1.5 && flag == true){
			robot.pneumaticMap[SHOOTER_LEFT_CYLINDER]->Set(DoubleSolenoid::kReverse);
			robot.pneumaticMap[SHOOTER_RIGHT_CYLINDER]->Set(DoubleSolenoid::kReverse);
			flag = false;
			return END;
		}

	}

	~ShootAction(){

	}
};



#endif /* SRC_ACTIONS_SHOOTACTION_H_ */
