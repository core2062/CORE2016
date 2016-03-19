/*
 * PickupArmAction.h
 *
 *  Created on: Feb 9, 2016
 *      Author: core2062
 */

#ifndef PICKUPARMACTION_H_
#define PICKUPARMACTION_H_

#include "CoreLIB/COREAuto.h"
#include "CORELIB/CORERobot.h"
#include "WPILib.h"
#include <cmath>
#include <iostream>
#include <math.h>
#include "CORELIB/Constants.h"
#include "CORELIB/COREPID.h"


using namespace CORE;//Added for commit reasons, can be deleted later

class PickupArmAction : public OrderAction{

public:
	Timer timer;

	double speed = 0.0;
	double duration = 0.0;
	smartDB* height = (new smartDB (std::string("null"), 0.0));
	bool bkrd;



	PickupArmAction(CORERobot& robot, double speed, double duration, bool backround = true):
		OrderAction(robot),
		speed(speed),
		bkrd(backround)
	{
	};
	PickupArmAction(CORERobot& robot, smartDB height, bool backround = false):
		OrderAction(robot),
		height(&height),
		bkrd(backround)
	{
	};


	void init(){
		timer.Reset();
		robot.motorMap[LEFT_PICKUP]->Set(0.0);
		robot.motorMap[RIGHT_PICKUP]->Set(0.0);
		timer.Start();
		robot.outLog.appendLog("Pickup Arm Action Start");

	}
	void end(){
		timer.Stop();
		robot.motorMap[LEFT_PICKUP]->Set(0.0);
		robot.motorMap[RIGHT_PICKUP]->Set(0.0);
		robot.outLog.appendLog("Pickup Arm Action End");
	}

	ControlFlow autoCall(){
		if(height->n == std::string("null")){
			if(timer.Get() < duration){
				robot.motorMap[LEFT_PICKUP]->Set(speed);
				robot.motorMap[RIGHT_PICKUP]->Set(speed);
				if(bkrd)
					return BACKGROUND;
				else
					return CONTINUE;
			}else{
				robot.motorMap[LEFT_PICKUP]->Set(0.0);
				robot.motorMap[RIGHT_PICKUP]->Set(0.0);
				return END;
			}
		}else{
//			double rightPickupError =  robot.analogSensorMap[RIGHT_POT]->GetValue() - robot.analogSensorMap[LEFT_POT]->GetValue() ;
//				double rightPickupOutput = (SmartDashboard::GetNumber(pickupPValue.n, pickupPValue.v)*rightPickupError);
//				rightPickupOutput = rightPickupOutput > 0.3 ? 0.3 : (rightPickupOutput < -0.3 ? -0.3 : rightPickupOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
//				if (rightPickupOutput < .05 && rightPickupOutput > -.05){
//					rightPickupOutput = 0;
//				}
//
//
//				double leftPickupError =  robot.analogSensorMap[LEFT_POT]->GetValue() - robot.analogSensorMap[RIGHT_POT]->GetValue() ;
//				double leftPickupOutput = (SmartDashboard::GetNumber(pickupPValue.n, pickupPValue.v)*leftPickupError);
//				leftPickupOutput = leftPickupOutput > 0.3 ? 0.3 : (leftPickupOutput < -0.3 ? -0.3 : leftPickupOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
//				if (leftPickupOutput < .05 && leftPickupOutput > -.05){
//					leftPickupOutput = 0;
//				}

				double base = SmartDashboard::GetNumber(rightMagPotBase.n,rightMagPotBase.v);
				double max = SmartDashboard::GetNumber(magneticPotMax.n,magneticPotMax.v);
				double raw = base<0?max-robot.analogSensorMap[RIGHT_POT]->GetVoltage():robot.analogSensorMap[RIGHT_POT]->GetVoltage();
				base = fabs(base);

				double val = raw<base?max+raw-base:raw-base;

				double otherPickupError =  (val - SmartDashboard::GetNumber(height->n, height->v));
				double otherPickupOutput = (SmartDashboard::GetNumber(otherPickupP.n, otherPickupP.v)*otherPickupError);
				otherPickupOutput = otherPickupOutput > 0.8 ? 0.8 : (otherPickupOutput < -0.8 ? -0.8 : otherPickupOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
				if (otherPickupOutput < .05 && otherPickupOutput > -.05){
					otherPickupOutput = 0;
				}

				if(fabs(otherPickupError) <.1){
					return END;
				}

				robot.motorMap[LEFT_PICKUP]->Set(otherPickupOutput);
				robot.motorMap[RIGHT_PICKUP]->Set(otherPickupOutput);
				if(bkrd)
					return BACKGROUND;
				else
					return CONTINUE;
		}
	}
		~PickupArmAction(){}
	};





#endif /* PICKUPARMACTION_H_ */
