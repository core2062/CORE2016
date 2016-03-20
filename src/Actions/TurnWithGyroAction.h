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
	double gyroRate = 0.0;
	double left = 0.0;
	double right = 0.0;
	double direction = 1;
	double a = SmartDashboard::GetNumber(etherA.n, etherA.v);
	double b = SmartDashboard::GetNumber(etherB.n, etherB.v);
	double maxSpeed = .6;

	TurnWithGyroAction(CORERobot& robot, double gyroSet, double max = .6):
		OrderAction(robot),
		gyroSet(gyroSet),
		maxSpeed(max){
	};

	void init(){

		robot.outLog.appendLog("Gyro Turn Action Start");
		std::cout<<"WARNING: Gyro Turn Start" << std::endl;
		gyroRate = robot.ahrs->GetYaw();
		if (gyroRate < gyroSet){
			direction = 1;
			std::cout<<"WARNING: Gyro Turn Dir +" << std::endl;
		}else{
			direction = -1;
			std::cout<<"WARNING: Gyro Turn Dir -" << std::endl;
		}


	}
	void end(){
		robot.motorMap[BACK_RIGHT]->Set(0.0);
		robot.motorMap[BACK_LEFT]->Set(0.0);
		robot.motorMap[FRONT_RIGHT]->Set(0.0);
		robot.motorMap[FRONT_LEFT]->Set(0.0);

		robot.outLog.appendLog("Gyro Turn Action End");
	}
	ControlFlow autoCall(){
#ifdef USE_NAVX
			gyroRate = robot.ahrs->GetYaw();
#else
			return END;
#endif
		//Gyro PID
			double gyroError =  gyroSet - gyroRate;
//			SmartDashboard::PutNumber("Gyro PID Error", gyroPID.mistake);

			double drive_rot = (SmartDashboard::GetNumber(rotationPValue.n, rotationPValue.v)*gyroError);
			drive_rot = drive_rot > maxSpeed ? maxSpeed : (drive_rot < -maxSpeed ? -maxSpeed : drive_rot); //Conditional (Tenerary) Operator limiting values to between 1 and -1
			if (drive_rot < .05 && drive_rot > -.05){
				drive_rot = 0;
			}


			left = drive_rot;
			right = -drive_rot;

			robot.motorMap[BACK_RIGHT]->Set(right);
			robot.motorMap[FRONT_RIGHT]->Set(right);
			robot.motorMap[FRONT_LEFT]->Set(left);
			robot.motorMap[BACK_LEFT]->Set(left);

			if(direction == 1){
				if (gyroRate > gyroSet){
					std::cout<<"WARNING: Gyro Turn End Dir+" << std::endl;
					return END;
				}
			}else{
				if (gyroRate < gyroSet){
					std::cout<<"WARNING: Gyro Turn End Dir-" << std::endl;
					return END;
				}
			}


			if(drive_rot == 0){
				std::cout<<"WARNING: Gyro Turn End Norm" << std::endl;
				return END;
			}else{
				return CONTINUE;
			}
	}

	~TurnWithGyroAction(){

	}
};







#endif /* SRC_ACTIONS_TURNWITHGYROACTION_H_ */
