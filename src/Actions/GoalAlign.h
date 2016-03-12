/*
 * GoalAlign.h
 *
 *  Created on: Feb 20, 2016
 *      Author: Draven
 */

#ifndef SRC_ACTIONS_GOALALIGN_H_
#define SRC_ACTIONS_GOALALIGN_H_

#include "CoreLIB/COREAuto.h"
#include "CORELIB/CORERobot.h"
#include "WPILib.h"
#include <cmath>
#include <iostream>
#include <math.h>
#include <VisionSubsystem.h>


using namespace CORE;

class GoalAlign : public OrderAction{

	VisionSubsystem &vision;
	int ballX = 0;
	int goalX = 0;
	int oldBallX = -1;
	int oldGoalX = -1;
	int resetQ = 0;
	double gyroSet = 0.0;
	double left = 0.0;
	double right = 0.0;
	double drive_rot = 0.0;
	double oldGyrorate = 0.0;
	double gyroIntegral = 0.0;

public:


	GoalAlign(CORERobot& robot, VisionSubsystem &vision):
		OrderAction(robot),
		vision(vision)
	{

	};

	void init(){

	}
	void end(){
		robot.motorMap[BACK_RIGHT]->Set(0.0);
		robot.motorMap[BACK_LEFT]->Set(0.0);
		robot.motorMap[FRONT_RIGHT]->Set(0.0);
		robot.motorMap[FRONT_LEFT]->Set(0.0);
	}
	ControlFlow autoCall(){

#ifdef USE_NAVX
	//	double gyroRate = robot.ahrs->GetYaw();
#else
		double gyroRate = 0.0;
		return END;
#endif

		ballX = vision.getBallX();
		goalX = vision.getGoalX();

		gyroSet = 0.0;


		if(oldGoalX!=goalX){
			oldGyrorate = robot.ahrs->GetYaw();
			gyroIntegral = 0.0;

		}

		if (goalX == -1){
//				drive_rot = (oldGoalX == -1)?NORMAL_SPEED:0.0;
		}else if (std::fabs(goalX-VISION_WIDTH/2.0) > VISION_WIDTH/2.0){
			if (goalX>VISION_WIDTH/2.0){
				drive_rot = -NORMAL_SPEED;
			}else{
				drive_rot = NORMAL_SPEED;
			}
		}else{
			gyroSet  = oldGyrorate+((goalX-(VISION_WIDTH/2.0))/(VISION_WIDTH/2.0))*(VISION_H_FOV/2.0);
			SmartDashboard::PutNumber("Gyro Set", gyroSet);
		}
		double gyroRate = robot.ahrs->GetYaw();
			//Gyro PID
			if((drive_rot==0.0 && resetQ == 0 && !SmartDashboard::GetBoolean("disableGyro",false))){
				double gyroError =  gyroSet - gyroRate;
//					double time = gyroITimer.Get();

				gyroIntegral += gyroError;
	//			SmartDashboard::PutNumber("Gyro PID Error", gyroPID.mistake);
				double gyroOutput = 0.0;
				if(fabs(gyroError)>2){
					gyroOutput = ((SmartDashboard::GetNumber( rotationPValue.n,  rotationPValue.v)*gyroError) + (SmartDashboard::GetNumber( rotationIValue.n,  rotationIValue.v)*gyroIntegral));
				}else{
					gyroOutput = ((SmartDashboard::GetNumber( rotationClosePValue.n,  rotationClosePValue.v)*gyroError) + (SmartDashboard::GetNumber( rotationCloseIValue.n,  rotationCloseIValue.v)*gyroIntegral));
				}
//					double gyroOutput = ((SmartDashboard::GetNumber( rotationPValue.n,  rotationPValue.v)*gyroError) + (SmartDashboard::GetNumber( rotationIValue.n,  rotationIValue.v)*gyroIntegral));
	//			SmartDashboard::PutNumber("Gyro PID Out before", gyroOutput);
				gyroOutput = gyroOutput > 1.0 ? 1.0 : (gyroOutput < -1.0 ? -1.0 : gyroOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
				drive_rot = gyroOutput;
			}

			oldBallX = ballX;
			oldGoalX = goalX;
			//gyroITimer.Reset();



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

	~GoalAlign(){
	}
};



#endif /* SRC_ACTIONS_GOALALIGN_H_ */
