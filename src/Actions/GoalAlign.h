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

	enum states{
		PULSING,
		WAITING,
		CHECKING,
		FINE
	};

	states state = CHECKING;

	VisionSubsystem &vision;

	int goalX = 0;
	int oldGoalX = -1;
	double oldGyroYaw = 0.0;
	double gyroSet = 0.0;
	double left = 0.0;
	double right = 0.0;
	double drive_rot = 0.0;
	double oldGyrorate = 0.0;
	double gyroIntegral = 0.0;
	int goalFlag = 0;
	double tempP = 0.0;
	Timer controlTimer;
	double pulseLength = 0;
	int good = 0;
	VisionSubsystem::Goals goal = VisionSubsystem::CENTER;
	double maxV = 11;
	double oldError = 0.0;
//	double oldTime = 0.0;
	Timer dTimer;

public:


	GoalAlign(CORERobot& robot, VisionSubsystem &vision, VisionSubsystem::Goals goal = VisionSubsystem::CENTER, double maxV = 10.5):
		OrderAction(robot),
		vision(vision),
		goal(goal),
		maxV(maxV)
	{

	};

	bool endCondition(int pos = -1){
		if(robot.pneumaticMap[SHOOTER_LEFT_CYLINDER]->Get() == DoubleSolenoid::kReverse){
			return true;
		}else{
			return false;
		}

	}

	void init(){
		gyroIntegral = 0.0;
		tempP = SmartDashboard::GetNumber(rotationPValue.n,rotationPValue.v);
		pulseLength = SmartDashboard::GetNumber(goalPulse.n,goalPulse.v);
//		std::cout << "WARNING: Goal Start" << std::endl;
		robot.motorMap[BACK_RIGHT]->SetControlMode(CANTalon::kVoltage);
		robot.motorMap[BACK_LEFT]->SetControlMode(CANTalon::kVoltage);
		robot.motorMap[FRONT_RIGHT]->SetControlMode(CANTalon::kVoltage);
		robot.motorMap[FRONT_LEFT]->SetControlMode(CANTalon::kVoltage);
		goalFlag = 0;
		robot.outLog.appendLog("Goal Align Action Start");
		controlTimer.Reset();
		controlTimer.Start();
	}
	void end(){
		controlTimer.Stop();
		robot.motorMap[BACK_RIGHT]->Set(0.0);
		robot.motorMap[BACK_LEFT]->Set(0.0);
		robot.motorMap[FRONT_RIGHT]->Set(0.0);
		robot.motorMap[FRONT_LEFT]->Set(0.0);
		robot.motorMap[BACK_RIGHT]->SetControlMode(CANTalon::kPercentVbus);
		robot.motorMap[BACK_LEFT]->SetControlMode(CANTalon::kPercentVbus);
		robot.motorMap[FRONT_RIGHT]->SetControlMode(CANTalon::kPercentVbus);
		robot.motorMap[FRONT_LEFT]->SetControlMode(CANTalon::kPercentVbus);
		std::cout << "WARNING: Goal Alignment End" << std::endl;
		robot.outLog.appendLog("Goal Align Action End");
	}
	ControlFlow autoCall(){
//		robot.motorMap[BACK_RIGHT]->Set(0.0);
//		robot.motorMap[BACK_LEFT]->Set(0.0);
//		robot.motorMap[FRONT_RIGHT]->Set(0.0);
//		robot.motorMap[FRONT_LEFT]->Set(0.0);
		goalX = vision.getGoalX(goal);
		SmartDashboard::PutNumber("Goal X", goalX);
		double error = goalX-SmartDashboard::GetNumber(goalCenter.n,goalCenter.v);
		switch(state){
		case PULSING:
			if (fabs(error) > 100){
				gyroIntegral = 0.0;
				if (error>0){
					goalFlag = 1;
					drive_rot = .55;
				}else{
					goalFlag = 2;
					drive_rot = -.55;
				}
			}else if (fabs(error) > 50)
			{
				gyroIntegral = 0.0;
				if (error > 0){

					if(goalFlag != 1 && goalFlag !=4){
						drive_rot = .55;
					}else{
						drive_rot = .45;
					}
					goalFlag = (goalFlag==4)?4:1;
				}else{
					if(goalFlag!=2 && goalFlag !=4){
						drive_rot = -.55;
					}else{
						drive_rot = -.45;
					}
					goalFlag = (goalFlag==4)?4:2;
				}
			}
			else if (fabs(error) > 48)
			{
				gyroIntegral = 0.0;
					if (error > 0){

					if(goalFlag != 1 && goalFlag !=4){
						drive_rot = .35;
					}else{
						drive_rot = .35;
					}
					goalFlag = (goalFlag==4)?4:1;
				}else{
					if(goalFlag!=2 && goalFlag !=4){
						drive_rot = -.35;
					}else{
						drive_rot = -.35;
					}
					goalFlag = (goalFlag==4)?4:2;
				}
			}else{
				/*
				if (error > 0){

					if(goalFlag != 1 && goalFlag !=4){
						drive_rot = .35;
					}else{
						drive_rot = .35;
					}
					goalFlag = (goalFlag==4)?4:1;
				}else{
					if(goalFlag!=2 && goalFlag !=4){
						drive_rot = -.35;
					}else{
						drive_rot = -.35;
					}
					goalFlag = (goalFlag==4)?4:2;
				}*/
				drive_rot = 0.0;
//				controlTimer.Reset();
//				state = WAITING;
			}
			if(controlTimer.Get()>pulseLength){
				drive_rot = 0.0;
				controlTimer.Reset();
				state = WAITING;
				return CONTINUE;
			}
			break;
		case WAITING:
			drive_rot = 0.0;
			if(controlTimer.Get()>.1){

				controlTimer.Reset();
				drive_rot = 0.0;
				state = CHECKING;
			}
			return CONTINUE;
			break;
		case CHECKING:
			drive_rot = 0.0;
			if(fabs(error) > 50){
				controlTimer.Reset();
				state = PULSING;
				goalFlag = 0;
				controlTimer.Reset();
				if(fabs(error)>25){
					pulseLength = 2.0*SmartDashboard::GetNumber(goalPulse.n,goalPulse.v);
				}else if(fabs(error)<15){
					pulseLength = SmartDashboard::GetNumber(goalPulse.n,goalPulse.v);
				}else{
					pulseLength = SmartDashboard::GetNumber(goalPulse.n,goalPulse.v);
				}
//			}else if (fabs(error)<=2){
//				return END;
			}else{
				std::cout<< "WARNING: Fine Tuning Start" << std::endl;
				controlTimer.Reset();
				dTimer.Reset();
				dTimer.Start();
				state = FINE;
				good = 0;
				gyroIntegral=0.0;
				return CONTINUE;
			}
			break;
		case FINE:
			if (fabs(error)<=2){
				if(controlTimer.Get()>.2)
					return BACKGROUND;
//				good++;
			}else{
				controlTimer.Reset();
//				good = 0;
			}
			if(oldGoalX!=goalX){
				oldGyroYaw = robot.ahrs->GetYaw();
			}
			gyroSet  = oldGyroYaw+((error)/(SmartDashboard::GetNumber(goalCenter.n,goalCenter.v)))*(VISION_H_FOV/2.0);
			double gyroError = gyroSet - robot.ahrs->GetYaw();
			gyroIntegral+=gyroError;
			double deriv = (gyroError-oldError)/(dTimer.Get());
			dTimer.Reset();
//			if((goalX>=SmartDashboard::GetNumber(goalCenter.n,goalCenter.v)+2  && gyroIntegral<0) || (goalX<=SmartDashboard::GetNumber(goalCenter.n,goalCenter.v)-2  && gyroIntegral>0)){
//				gyroIntegral = 0;
//				std::cout << "Integral Reset" << std::endl;
//			}
//			if(fabs(error)>10){
//				gyroIntegral = 0;
//			}
			double gyroOutput = ((tempP*gyroError) + (SmartDashboard::GetNumber( rotationIValue.n,  rotationIValue.v)*gyroIntegral) + (SmartDashboard::GetNumber( rotationDValue.n,  rotationDValue.v)*deriv));
			gyroOutput = gyroOutput > .35 ? .35 : (gyroOutput < -.35 ? -.35 : gyroOutput);
			drive_rot = gyroOutput;
			if(fabs(gyroOutput) == .35){
				gyroIntegral-=gyroError;
			}

			oldError = gyroError;
			break;
		}
		SmartDashboard::PutNumber("Drive Rot", drive_rot);
		SmartDashboard::PutNumber("Align State", state);
		left = drive_rot*maxV;
		right = -drive_rot*maxV;

		robot.motorMap[BACK_RIGHT]->Set(right);
		robot.motorMap[FRONT_RIGHT]->Set(right);
		robot.motorMap[FRONT_LEFT]->Set(left);
		robot.motorMap[BACK_LEFT]->Set(left);

		oldGoalX = goalX;

		return CONTINUE;
	}

	~GoalAlign(){
	}
};



#endif /* SRC_ACTIONS_GOALALIGN_H_ */
