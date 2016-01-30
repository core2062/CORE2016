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

class TurnWithGyroAction : public ConditionAction{

public:

	double drive_rot = robot.joystick.axis(DRIVE_ROT);
	double drive_mag = robot.joystick.axis(DRIVE_MAG);

//	bool oldRot = 0.0;
	int resetQ = 0;
	double gyroSet = 0.0;
	double left = 0.0;
	double right = 0.0;
	double a = SmartDashboard::GetNumber(robot.sd.etherA.n, robot.sd.etherA.v);
	double b = SmartDashboard::GetNumber(robot.sd.etherB.n, robot.sd.etherB.v);

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
		if((drive_rot==0.0 && resetQ == 0 && !SmartDashboard::GetBoolean("disableGyro",false))){
			double gyroError =  gyroSet - gyroRate;
//			SmartDashboard::PutNumber("Gyro PID Error", gyroPID.mistake);

			double gyroOutput = (SmartDashboard::GetNumber(robot.sd.rotationPValue.n, robot.sd.rotationPValue.v)*gyroError);
//			SmartDashboard::PutNumber("Gyro PID Out before", gyroOutput);
			gyroOutput = gyroOutput > 1.0 ? 1.0 : (gyroOutput < -1.0 ? -1.0 : gyroOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
			drive_rot = gyroOutput;
		}
			if (drive_rot < .05 && drive_rot > -.05){
				drive_rot = 0;
			}


			if (drive_mag>=0){
				if (drive_rot>=0){
					left = etherL(0, drive_rot, a, b);
					right = etherR(0, drive_rot, a, b);
				} else{
					left = etherR(0, -drive_rot, a, b);
					right = etherL(0, -drive_rot, a, b);
				}
			} else{
				if (drive_rot>=0){

					left = -etherR(-0, drive_rot, a, b);
					right = -etherL(0, drive_rot, a, b);
				} else{
					left = -etherL(0, -drive_rot, a, b);
					right = -etherR(0, -drive_rot, a, b);
				}
			}
			robot.motorMap[BACK_RIGHT]->Set(right);
			robot.motorMap[FRONT_RIGHT]->Set(right);
			robot.motorMap[FRONT_LEFT]->Set(left);
			robot.motorMap[BACK_LEFT]->Set(left);

		return CONTINUE;
	}

	~TurnWithGyroAction(){

	}
};







#endif /* SRC_ACTIONS_TURNWITHGYROACTION_H_ */
