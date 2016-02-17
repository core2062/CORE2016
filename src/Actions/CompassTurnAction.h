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


public:

	CompassTurnAction(CORERobot& robot, double targetAngle = 0.0):
		OrderAction(robot),
		targetAngle(targetAngle)
	{

	};

	void init(){}
	void end(){
		robot.motorMap[BACK_RIGHT]->Set(0.0);
		robot.motorMap[BACK_LEFT]->Set(0.0);
		robot.motorMap[FRONT_RIGHT]->Set(0.0);
		robot.motorMap[FRONT_LEFT]->Set(0.0);
	}
	ControlFlow autoCall(){

#if defined(USE_NAVX)
		DriverStation::Alliance color;
		color = DriverStation::GetInstance().GetAlliance();
		if(color == DriverStation::Alliance::kBlue){
			double total = (robot.ahrs->GetCompassHeading()+SmartDashboard::GetNumber(blueTowerCompass.n,blueTowerCompass.v));
			compassVal = total>=360?total-360:total;
		}else{
			double total = (robot.ahrs->GetCompassHeading()+SmartDashboard::GetNumber(blueTowerCompass.n,blueTowerCompass.v) + 180);
			compassVal = total>=360?(total-360>=360?total-720:total-360):total;
		}
#endif

		double gyroError =  (fabs(compassVal - targetAngle) <= fabs(compassVal>180?compassVal-360:compassVal - targetAngle>180?targetAngle-360:targetAngle))?(compassVal - targetAngle):(compassVal>180?compassVal-360:compassVal - targetAngle>180?targetAngle-360:targetAngle);
//			SmartDashboard::PutNumber("Gyro PID Error", gyroPID.mistake);
		double gyroOutput = (SmartDashboard::GetNumber(rotationPValue.n, rotationPValue.v)*gyroError);
//			SmartDashboard::PutNumber("Gyro PID Out before", gyroOutput);
		gyroOutput = gyroOutput > 1.0 ? 1.0 : (gyroOutput < -1.0 ? -1.0 : gyroOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
		double drive_rot = gyroOutput;
		if (drive_rot < .05 && drive_rot > -.05){
			drive_rot = 0;
		}

		double left = drive_rot;
		double right = -drive_rot;

		robot.motorMap[BACK_RIGHT]->Set(right);
		robot.motorMap[FRONT_RIGHT]->Set(right);
		robot.motorMap[FRONT_LEFT]->Set(left);
		robot.motorMap[BACK_LEFT]->Set(left);
		if (drive_rot == 0){
			return END;
		}
			return CONTINUE;
	}

	~CompassTurnAction(){

	}
};



#endif /* SRC_ACTIONS_COMPASSTURNACTION_H_ */
