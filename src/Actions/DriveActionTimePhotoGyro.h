/*
 * DriveAction.h
 *
 *  Created on: Jan 25, 2016
 *      Author: Draven
 */

#ifndef SRC_ACTIONS_DRIVEACTIONTIMEPHOTOGYRO_H_
#define SRC_ACTIONS_DRIVEACTIONTIMEPHOTOGYRO_H_

#include "CoreLib/COREAuto.h"

using namespace CORE;

class DriveActionTimePhotoGyro : public WaitAction{

	double avgDist = 0.0;
	double speed = 0;
	bool trip = false;
	//variables

public:

	//			robot.motorMap[LIFT_MOTOR]->Set(FORWARD);



	DriveActionTimePhotoGyro(CORERobot& robot, double duration, double speed, bool trip = true):
		WaitAction(robot, duration),
		speed(speed),
		trip(trip)
		{

		};

	void init(){
		//getting sensor values
		robot.motorMap[FRONT_LEFT]->SetEncPosition(0);
		robot.motorMap[FRONT_RIGHT]->SetEncPosition(0);
		robot.outLog.appendLog("Drive Time Action Start");
		robot.motorMap[FRONT_LEFT]->Set(speed);
		robot.motorMap[FRONT_RIGHT]->Set(speed);
		robot.motorMap[BACK_LEFT]->Set(speed);
		robot.motorMap[BACK_RIGHT]->Set(speed);
		robot.motorMap[BACK_RIGHT]->SetControlMode(CANTalon::kPercentVbus);
		robot.motorMap[BACK_LEFT]->SetControlMode(CANTalon::kPercentVbus);
		robot.motorMap[FRONT_RIGHT]->SetControlMode(CANTalon::kPercentVbus);
		robot.motorMap[FRONT_LEFT]->SetControlMode(CANTalon::kPercentVbus);

	}
	void end(){
		robot.motorMap[FRONT_LEFT]->Set(0.0);
		robot.motorMap[FRONT_RIGHT]->Set(0.0);
		robot.motorMap[BACK_LEFT]->Set(0.0);
		robot.motorMap[BACK_RIGHT]->Set(0.0);
		robot.outLog.appendLog("Drive Action End");
	}

	ControlFlow autoCall(){
		robot.motorMap[FRONT_LEFT]->Set(speed);
		robot.motorMap[FRONT_RIGHT]->Set(speed);
		robot.motorMap[BACK_LEFT]->Set(speed);
		robot.motorMap[BACK_RIGHT]->Set(speed);
		if((robot.digitalSensorMap[BACK_PHOTO]->Get() == trip && robot.digitalSensorMap[FRONT_PHOTO]->Get() == trip) && fabs(robot.ahrs->GetPitch()) <8){
			return WaitAction::autoCall();
		}else{
			return CONTINUE;
		}

	}


	~DriveActionTimePhotoGyro(){

	}
};




#endif /* SRC_ACTIONS_DRIVEACTION_H_ */
