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
	bool flag = false;
	bool flag2 = false;
	double loadTime;



	ShootAction(CORERobot& robot, double loadTime = 1.5):
		OrderAction(robot),
		loadTime(loadTime)
	{

	};

	void init(){
		timer.Reset();
		timer.Start();

	}
	void end(){}
	ControlFlow autoCall(){
		if(flag == false && robot.pneumaticMap[SHOOTER_LEFT_CYLINDER]->Get() == DoubleSolenoid::kForward) {
			robot.pneumaticMap[SHOOTER_LEFT_CYLINDER]->Set(DoubleSolenoid::kReverse);
			robot.pneumaticMap[SHOOTER_RIGHT_CYLINDER]->Set(DoubleSolenoid::kReverse);
			flag2 = true;
			timer.Reset();
		}
		if(flag2 == true){
			if(timer.Get() >= loadTime){
				if(!flag2 == false)
					flag2 = false;
				return CONTINUE;
			}
		}else if(flag == false && flag2 == false){
			timer.Reset();
			robot.pneumaticMap[SHOOTER_LEFT_CYLINDER]->Set(DoubleSolenoid::kForward);
			robot.pneumaticMap[SHOOTER_RIGHT_CYLINDER]->Set(DoubleSolenoid::kForward);
			flag = true;
			return BACKGROUND;
		}

		if(timer.Get() >= loadTime && flag == true){
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
