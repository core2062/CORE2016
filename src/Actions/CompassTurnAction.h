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

	double drive_rot = robot.joystick.axis(DRIVE_ROT);
	double drive_mag = robot.joystick.axis(DRIVE_MAG);

//	bool oldRot = 0.0;
	double gyroRate = 0.0;
	double unmodifiedMag = 0.0;
	int resetQ = 0;
	double gyroSet = 0.0;
	double left = 0.0;
	double right = 0.0;
	double a = SmartDashboard::GetNumber(etherA.n, etherA.v);
	double b = SmartDashboard::GetNumber(etherB.n, etherB.v);


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
			unmodifiedMag = robot.ahrs->GetCompassHeading();
			if(unmodifiedMag >180){
				unmodifiedMag = -(180-(unmodifiedMag-180));
				gyroRate = unmodifiedMag;
			} else {
				gyroRate = gyroSet;
				robot.outLog.appendLog("[ERROR] Magnetometer Not Calibrated!!");
			}
		}


				//Gyro PID
		if((drive_rot==0.0 && resetQ == 0 && !SmartDashboard::GetBoolean("disableGyro",false))){
			double gyroError =  gyroSet - gyroRate;
//			SmartDashboard::PutNumber("Gyro PID Error", gyroPID.mistake);

			double gyroOutput = (SmartDashboard::GetNumber(rotationPValue.n, rotationPValue.v)*gyroError);
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
