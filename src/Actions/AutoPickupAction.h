/*
 * AutoPickupAction.h
 *
 *  Created on: Feb 17, 2016
 *      Author: Draven
 */

#ifndef SRC_ACTIONS_AUTOPICKUPACTION_H_
#define SRC_ACTIONS_AUTOPICKUPACTION_H_
/*
#include "CoreLIB/COREAuto.h"
#include "CORELIB/CORERobot.h"
#include "WPILib.h"
#include <cmath>
#include <iostream>
#include <math.h>


using namespace CORE;

class AutoPickupAction : public OrderAction{

	Timer timer;

	double leftPot = robot.analogSensorMap[LEFT_POT]->GetValue();
	double rightPot = robot.analogSensorMap[RIGHT_POT]->GetValue();
//	double rollerMotor = robot.motorMap[ROLLER];
//	double leftMotor = robot.motorMap[LEFT_PICKUP];
//	double rightMotor = robot.motorMap[RIGHT_PICKUP];
	bool flag = false;


public:

	AutoPickupAction(CORERobot& robot):
		OrderAction(robot)
	{

	};

	void init(){}
	void end(){
		robot.motorMap[ROLLER]->Set(0.0);
		robot.motorMap[LEFT_PICKUP]->Set(0.0);
		robot.motorMap[RIGHT_PICKUP]->Set(0.0);
		timer.Stop();
	}
	ControlFlow autoCall(){
		if(robot.motorMap[ROLLER]->GetOutputVoltage() > SmartDashboard::GetNumber(pickupVoltThresh.n, pickupVoltThresh.v) || flag == true){
			if(!flag){
				flag = true;
				timer.Reset();
				timer.Start();
			}
			if(timer.Get() > 1.0){
				if(((leftPot + rightPot) / 2) >= SmartDashboard::GetNumber(pickupHeight5.n, pickupHeight5.v)){ //pickup height & direction will have to be tuned
					robot.motorMap[LEFT_PICKUP]->Set(0.0);
					robot.motorMap[RIGHT_PICKUP]->Set(0.0);
					return END;
				} else {
					robot.motorMap[ROLLER]->Set(0.0);
					double rightPickupError =  robot.analogSensorMap[RIGHT_POT]->GetValue() - robot.analogSensorMap[LEFT_POT]->GetValue() ;
					double rightPickupOutput = (SmartDashboard::GetNumber(pickupPValue.n, pickupPValue.v)*rightPickupError);
					rightPickupOutput = rightPickupOutput > 0.3 ? 0.3 : (rightPickupOutput < -0.3 ? -0.3 : rightPickupOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
					if (rightPickupOutput < .05 && rightPickupOutput > -.05){
						rightPickupOutput = 0;
					}


					double leftPickupError =  robot.analogSensorMap[LEFT_POT]->GetValue() - robot.analogSensorMap[RIGHT_POT]->GetValue() ;
					double leftPickupOutput = (SmartDashboard::GetNumber(pickupPValue.n, pickupPValue.v)*leftPickupError);
					leftPickupOutput = leftPickupOutput > 0.3 ? 0.3 : (leftPickupOutput < -0.3 ? -0.3 : leftPickupOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
					if (leftPickupOutput < .05 && leftPickupOutput > -.05){
						leftPickupOutput = 0;
					}



					double otherPickupError =  ((robot.analogSensorMap[LEFT_POT]->GetValue() + robot.analogSensorMap[RIGHT_POT]->GetValue()) / 2) - pickupHeight5.v;// This might need to be changed
					double otherPickupOutput = (SmartDashboard::GetNumber(otherPickupP.n, otherPickupP.v)*otherPickupError);
					otherPickupOutput = otherPickupOutput > 0.8 ? 0.8 : (otherPickupOutput < -0.8 ? -0.8 : otherPickupOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
					if (otherPickupOutput < .05 && otherPickupOutput > -.05){
						otherPickupOutput = 0;
					}
					robot.motorMap[LEFT_PICKUP]->Set(otherPickupOutput + leftPickupOutput);
					robot.motorMap[RIGHT_PICKUP]->Set(otherPickupOutput + rightPickupOutput);
				}
			} else {
				return BACKGROUND;
			}
		} else {
			robot.motorMap[ROLLER]->Set(FORWARD);
			return BACKGROUND;
		}
	}

	~AutoPickupAction(){

	}
};
*/
#endif /* SRC_ACTIONS_AUTOPICKUPACTION_H_ */
