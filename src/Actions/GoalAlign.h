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
	double oldGyroYaw = 0.0;
	int resetQ = 0;
	double gyroSet = 0.0;
	double left = 0.0;
	double right = 0.0;
	double drive_rot = 0.0;
	double oldGyrorate = 0.0;
	double gyroIntegral = 0.0;
	int goalFlag = 0;
	double tempP = 0.0;

public:


	GoalAlign(CORERobot& robot, VisionSubsystem &vision):
		OrderAction(robot),
		vision(vision)
	{

	};

	void init(){
		gyroIntegral = 0.0;
		tempP = SmartDashboard::GetNumber(rotationPValue.n,rotationPValue.v);
		std::cout << "WARNING: Goal Start" << std::endl;
		goalFlag = 0;
		robot.outLog.appendLog("Goal Align Action Start");
	}
	void end(){
		robot.motorMap[BACK_RIGHT]->Set(0.0);
		robot.motorMap[BACK_LEFT]->Set(0.0);
		robot.motorMap[FRONT_RIGHT]->Set(0.0);
		robot.motorMap[FRONT_LEFT]->Set(0.0);
		robot.outLog.appendLog("Goal Align Action End");
	}
	ControlFlow autoCall(){

#ifdef USE_NAVX
	//	double gyroRate = robot.ahrs->GetYaw();
#else
		double gyroRate = 0.0;
		return END;
#endif

		goalX = vision.getGoalX();





		if(oldGoalX!=goalX){
			oldGyroYaw = robot.ahrs->GetYaw();

		}

		if (goalX == -1){
			gyroIntegral = 0.0;
			drive_rot = 0.0;
			goalFlag = 0;
			return CONTINUE;
		}else if (std::fabs(goalX-(SmartDashboard::GetNumber(goalCenter.n,goalCenter.v))) > 300){
			gyroIntegral = 0.0;
			if (goalX>SmartDashboard::GetNumber(goalCenter.n,goalCenter.v)){
				goalFlag = (goalFlag==4)?4:1;
				drive_rot = .7;
			}else{
				goalFlag = (goalFlag==4)?4:2;
				drive_rot = -.7;
			}
		}else if (std::fabs(goalX-(SmartDashboard::GetNumber(goalCenter.n,goalCenter.v))) > 90){
			gyroIntegral = 0.0;
			if (goalX>SmartDashboard::GetNumber(goalCenter.n,goalCenter.v)){

				if(goalFlag != 1 && goalFlag !=4){
					drive_rot = .65;
				}else{
					drive_rot = .55;
				}
				goalFlag = (goalFlag==4)?4:1;
			}else{
				if(goalFlag!=2 && goalFlag !=4){
					drive_rot = -.65;
				}else{
					drive_rot = -.55;
				}
				goalFlag = (goalFlag==4)?4:2;
			}
		}else{
			gyroSet  = oldGyroYaw+((goalX-(SmartDashboard::GetNumber(goalCenter.n,goalCenter.v)))/(SmartDashboard::GetNumber(goalCenter.n,goalCenter.v)))*(VISION_H_FOV/2.0);
			SmartDashboard::PutNumber("Gyro Set", gyroSet);

		double gyroRate = robot.ahrs->GetYaw();
			//Gyro PID
			goalFlag = 4;
			if((drive_rot==0.0 && resetQ == 0 && !SmartDashboard::GetBoolean("disableGyro",false))){
				double gyroError =  gyroSet - gyroRate;
//					double time = gyroITimer.Get();

//					if((gyroError >0 && oldGyroError <0) || (gyroError < 0 && oldGyroError > 0)){
//						gyroIntegral = {0.0};
////						gyroError*=-1;
//						std::cout << "WARNING: integral reset" << std::endl;
//						tempP*=.5;
////						gyroError*=-1;
//
//					}
				if(fabs(gyroError) <=3){
					return END;
				}

//					if(fabs(gyroError) < 4.5)
//						gyroIntegral.push_back(gyroError);
//
////					if(gyroIntegral.size()>25){
////						gyroIntegral.erase(gyroIntegral.begin());
////					}
//					if(fabs(gyroError) <= 3.5 && fabs(oldGyroError) > 3.5){
//						gyroIntegral.clear();
//						gyroIntegral.push_back(0.0);
//						std::cout << "WARNING: integral reset" << std::endl;
//					}

				gyroIntegral+=gyroError;
				if((goalX>=182  && gyroIntegral<0/*&& oldGoalX <182*/) || (goalX<=178  && gyroIntegral>0/*&& oldGoalX >178*/)){
					gyroIntegral = 0;
					std::cout << "WARNGING: Integral Reset" << std::endl;
				}
	//			SmartDashboard::PutNumber("Gyro PID Error", gyroPID.mistake);
				double gyroOutput = 0.0;
//					if(fabs(gyroError)>1.5){
//						gyroOutput = ((SmartDashboard::GetNumber( rotationPValue.n,  rotationPValue.v)*gyroError) + (SmartDashboard::GetNumber( rotationIValue.n,  rotationIValue.v)*sumIntegral));
//					}else{
//						gyroOutput = ((SmartDashboard::GetNumber( rotationClosePValue.n,  rotationClosePValue.v)*gyroError) + (SmartDashboard::GetNumber( rotationCloseIValue.n,  rotationCloseIValue.v)*sumIntegral));
//					}
				gyroOutput = ((tempP*gyroError) + (SmartDashboard::GetNumber( rotationIValue.n,  rotationIValue.v)*gyroIntegral));
				//
//					double gyroOutput = ((SmartDashboard::GetNumber( rotationPValue.n,  rotationPValue.v)*gyroError) + (SmartDashboard::GetNumber( rotationIValue.n,  rotationIValue.v)*gyroIntegral));
	//			SmartDashboard::PutNumber("Gyro PID Out before", gyroOutput);
				gyroOutput = gyroOutput > .55 ? .55 : (gyroOutput < -.55 ? -.55 : gyroOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
				drive_rot = gyroOutput;

//					if(((gyroError >0 && oldGyroError <0) || (gyroError < 0 && oldGyroError > 0)) || (goalX >= 478 && goalX <=482)){
//						gyroIntegral = {0.0};
////						gyroError*=-1;
////						gyroError*=-1;
//						drive_rot = 0.0;
//					}



			}
		}

			oldGoalX = goalX;
			if (drive_rot < .05 && drive_rot > -.05){
				drive_rot = 0;
			}

			left = drive_rot;
			right = -drive_rot;

			robot.motorMap[BACK_RIGHT]->Set(right);
			robot.motorMap[FRONT_RIGHT]->Set(right);
			robot.motorMap[FRONT_LEFT]->Set(left);
			robot.motorMap[BACK_LEFT]->Set(left);

			return CONTINUE;


	}

	~GoalAlign(){
	}
};



#endif /* SRC_ACTIONS_GOALALIGN_H_ */
