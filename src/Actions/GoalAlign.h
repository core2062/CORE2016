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
	Timer pulseTimer;
	double pulseLength = 0;
	int good = 0;

public:


	GoalAlign(CORERobot& robot, VisionSubsystem &vision):
		OrderAction(robot),
		vision(vision)
	{

	};

	void init(){
		gyroIntegral = 0.0;
		tempP = SmartDashboard::GetNumber(rotationPValue.n,rotationPValue.v);
		pulseLength = SmartDashboard::GetNumber(goalPulse.n,goalPulse.v);
		std::cout << "WARNING: Goal Start" << std::endl;
		goalFlag = 0;
		robot.outLog.appendLog("Goal Align Action Start");
		pulseTimer.Reset();
		pulseTimer.Start();
	}
	void end(){
		pulseTimer.Stop();
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

if(pulseTimer.Get()<pulseLength){



		if(oldGoalX!=goalX){
			oldGyroYaw = robot.ahrs->GetYaw();

		}

		if (goalX == -1){
			gyroIntegral = 0.0;
			drive_rot = 0.0;
			goalFlag = 0;
			return CONTINUE;
//		}else if (std::fabs(goalX-(SmartDashboard::GetNumber(goalCenter.n,goalCenter.v))) > 300){
//			gyroIntegral = 0.0;
//			if (goalX>SmartDashboard::GetNumber(goalCenter.n,goalCenter.v)){
//				goalFlag = (goalFlag==4)?4:1;
//				drive_rot = .7;
//			}else{
//				goalFlag = (goalFlag==4)?4:2;
//				drive_rot = -.7;
//			}
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
				if(fabs(goalX-SmartDashboard::GetNumber(goalCenter.n,goalCenter.v)) <=5){
					good++;
					if(good>=6 && fabs(goalX-SmartDashboard::GetNumber(goalCenter.n,goalCenter.v)) <=3){
						std::cout << "WARNING: Aligned" << std::endl;
						return END;
					}

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
				if((goalX>=SmartDashboard::GetNumber(goalCenter.n,goalCenter.v)+2  && gyroIntegral<0/*&& oldGoalX <182*/) || (goalX<=SmartDashboard::GetNumber(goalCenter.n,goalCenter.v)-2  && gyroIntegral>0/*&& oldGoalX >178*/)){
					gyroIntegral *= -.05;
					std::cout << "WARNGING: Integral Reset" << std::endl;
				}
	//			SmartDashboard::PutNumber("Gyro PID Error", gyroPID.mistake);
				double gyroOutput = 0.0;
//					if(fabs(gyroError)>1.5){
//						gyroOutput = ((SmartDashboard::GetNumber( rotationPValue.n,  rotationPValue.v)*gyroError) + (SmartDashboard::GetNumber( rotationIValue.n,  rotationIValue.v)*sumIntegral));
//					}else{
//						gyroOutput = ((SmartDashboard::GetNumber( rotationClosePValue.n,  rotationClosePValue.v)*gyroError) + (SmartDashboard::GetNumber( rotationCloseIValue.n,  rotationCloseIValue.v)*sumIntegral));
//					}
				gyroOutput = ((tempP*gyroError) + (SmartDashboard::GetNumber( rotationIValue.n,  rotationIValue.v)*gyroIntegral*1.5));
				//
//					double gyroOutput = ((SmartDashboard::GetNumber( rotationPValue.n,  rotationPValue.v)*gyroError) + (SmartDashboard::GetNumber( rotationIValue.n,  rotationIValue.v)*gyroIntegral));
	//			SmartDashboard::PutNumber("Gyro PID Out before", gyroOutput);
				gyroOutput = gyroOutput > .5 ? .5 : (gyroOutput < -.5 ? -.5 : gyroOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
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
}else{
	if(pulseLength<SmartDashboard::GetNumber(goalPulse.n,goalPulse.v)*1.25)
		gyroIntegral = 0.0;
	drive_rot = 0.0;

	left = drive_rot;
	right = -drive_rot;

	robot.motorMap[BACK_RIGHT]->Set(right);
	robot.motorMap[FRONT_RIGHT]->Set(right);
	robot.motorMap[FRONT_LEFT]->Set(left);
	robot.motorMap[BACK_LEFT]->Set(left);

	if(pulseTimer.Get()>SmartDashboard::GetNumber(goalPulse.n,goalPulse.v)/*pulseLength*/*2.0){
		pulseTimer.Reset();
//		pulseLength*=1;
		if(fabs(goalX-SmartDashboard::GetNumber(goalCenter.n,goalCenter.v)) <=15){
			std::cout << "WARNING: Increase Pulse" << std::endl;
			pulseLength+=.05;
		}
	}
	return CONTINUE;
}


	}

	~GoalAlign(){
	}
};



#endif /* SRC_ACTIONS_GOALALIGN_H_ */
