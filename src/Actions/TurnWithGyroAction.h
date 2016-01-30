/*
 * TurnWithGyroAction.h
 *
 *  Created on: Jan 28, 2016
 *      Author: Draven
 */

#ifndef SRC_ACTIONS_TURNWITHGYROACTION_H_
#define SRC_ACTIONS_TURNWITHGYROACTION_H_

#include "CoreLIB/COREAuto.h"
#include "CORELIB/CORERobot.h"
#include "WPILib.h"
#include <cmath>
#include <iostream>
#include <math.h>
// #include "DrivePickupSubsystem.h"


using namespace CORE;

class TurnWithGyroAction : public OrderAction{

public:

//	bool oldRot = 0.0;
	int resetQ = 0;
	double gyroSet = 0.0;
	double left = 0.0;
	double right = 0.0;
	double a = SmartDashboard::GetNumber(etherA.n, etherA.v);
	double b = SmartDashboard::GetNumber(etherB.n, etherB.v);

	virtual bool startCondition(){
		return false;
	}
	virtual bool endCondition(){
		return false;
	}
	TurnWithGyroAction(CORERobot& robot, double gyroSet):
		ConditionAction(robot),
		gyroSet(gyroSet){
	};

	void init(){}
	void end(){}
	ControlFlow autoCall(){

			double gyroRate = robot.ahrs->GetYaw();
		//Gyro PID
			double gyroError =  gyroSet - gyroRate;
//			SmartDashboard::PutNumber("Gyro PID Error", gyroPID.mistake);

			double drive_rot = (SmartDashboard::GetNumber(rotationPValue.n, rotationPValue.v)*gyroError);
			drive_rot = drive_rot > 1.0 ? 1.0 : (drive_rot < -1.0 ? -1.0 : drive_rot); //Conditional (Tenerary) Operator limiting values to between 1 and -1
			if (drive_rot < .05 && drive_rot > -.05){
				drive_rot = 0;
			}


			left = drive_rot;
			right = -drive_rot;

			robot.motorMap[BACK_RIGHT]->Set(right);
			robot.motorMap[FRONT_RIGHT]->Set(right);
			robot.motorMap[FRONT_LEFT]->Set(left);
			robot.motorMap[BACK_LEFT]->Set(left);

			if(drive_rot == 0)
				return END;
			else
				return CONTINUE;
	}

	~TurnWithGyroAction(){

	}
};







#endif /* SRC_ACTIONS_TURNWITHGYROACTION_H_ */
