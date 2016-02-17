/*
 * VisionSubsystem.h
 *
 *  Created on: Jan 15, 2016
 *      Author: core
 */

#ifndef SRC_VISIONSUBSYSTEM_H_
#define SRC_VISIONSUBSYSTEM_H_

#include "CORELIB/CORERobot.h"
#include "WPILib.h"
#include <cmath>
#include <iostream>
#include <math.h>

using namespace CORE;


class VisionSubsystem: public CORESubsystem{

	std::shared_ptr<NetworkTable> visionTable;

	bool run = true;

	int ballX = -1;
	int goalX = -1;
	int ballArea = -1;

	bool errorStated = false;

/*	//Camera Error Calc Values //
	const double cameraFOV = 68.5;
	const double cameraMountAngle = 10; // Angle center of camera makes with the chassis //
	const double distBetweenCameras = 10; //In inches //

	int leftCameraXPoint = 0; //need to be supplied this with vision //
	int rightCameraXPoint = 0; // need to be supplied this with vision //
	double relativeLeftAngle = 0;
	double relativeRightAngle = 0;
	double precentLeftAngle = 0;
	double precentRightAngle = 0;
	double rightAngleError = 0;
	double leftAngleError = 0;*/
	bool flag = false;
	Timer checkTimer;

public:

		CANSpeedController::ControlMode mode = CANSpeedController::kPercentVbus;
//		CANSpeedController::ControlMode mode = CANSpeedController::kVoltage;





	std::string name(void);
	VisionSubsystem(CORERobot& robot):
		CORESubsystem(robot)

		{
		try{
			visionTable = NetworkTable::GetTable("Vision");
		}catch(...){
			std::cout << "ERROR: Failed to pull network tables!" << std::endl;
			run = false;
			checkTimer.Reset();
			checkTimer.Start();

		}
		}

	void robotInit(void);
	void teleopInit(void);
	void teleop(void);
	double angleError(side motorSide);
	double distFromBall(void);
	double getBallX();
	double getBallArea();
	double getGoalX();

void teleopEnd(void);
};

#endif /* SRC_VISIONSUBSYSTEM_H_ */
