/*
 * CompassTurnAction.h
 *
 *  Created on: Jan 30, 2016
 *      Author: Draven
 */

#ifndef SRC_ACTIONS_COMPASSTURNACTION_H_
#define SRC_ACTIONS_COMPASSTURNACTION_H_

#include "CoreLIB/COREAuto.h"
#include "CORELIB/CORERobot.h"
#include "WPILib.h"
#include <cmath>
#include <iostream>
#include <math.h>


using namespace CORE;

class CompassTurnAction : public OrderAction{

	double targetAngle;

	double drive_rot = 0;

	double compassVal = 0.0;
	double gyroSet = 0.0;
	double left = 0.0;
	double right = 0.0;


public:

	CompassTurnAction(CORERobot& robot, double targetAngle = 0.0):
		OrderAction(robot),
		targetAngle(targetAngle)
	{

	};

	void init(){}
	void end(){}
	ControlFlow autoCall(){
		if(!robot.ahrs->IsMagneticDisturbance() && robot.ahrs->IsMagnetometerCalibrated()){
			compassVal = robot.ahrs->GetCompassHeading();
		}else{
			return CONTINUE;
		}


			double gyroError =  compassVal - targetAngle;
//			SmartDashboard::PutNumber("Gyro PID Error", gyroPID.mistake);

			double gyroOutput = (SmartDashboard::GetNumber(rotationPValue.n, rotationPValue.v)*gyroError);
//			SmartDashboard::PutNumber("Gyro PID Out before", gyroOutput);
			gyroOutput = gyroOutput > 1.0 ? 1.0 : (gyroOutput < -1.0 ? -1.0 : gyroOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
			drive_rot = gyroOutput;
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
			return CONTINUE;
	}

	~CompassTurnAction(){

	}
};



#endif /* SRC_ACTIONS_COMPASSTURNACTION_H_ */
