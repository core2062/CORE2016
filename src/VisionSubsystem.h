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

	const double cameraFOV = 68.5;
	const double cameraMountAngle = 10; // Angle center of camera makes with the chassis //
	const double distBetweenCameras = 10; //In inches //
	const int maxXRes = 1280;

	//Camera Error Calc Values //

	int leftCameraXPoint = 0; //need to be supplied this with vision //
	int rightCameraXPoint = 0; // need to be supplied this with vision //
	double relativeLeftAngle = 0;
	double relativeRightAngle = 0;
	double precentLeftAngle = 0;
	double precentRightAngle = 0;
	double rightAngleError = 0;
	double leftAngleError = 0;

public:

		CANSpeedController::ControlMode mode = CANSpeedController::kPercentVbus;
//		CANSpeedController::ControlMode mode = CANSpeedController::kVoltage;





	std::string name(void);
	VisionSubsystem(CORERobot& robot):
		CORESubsystem(robot)

		{

		}

	void robotInit(void);
	void teleopInit(void);
	void teleop(void);
	double angleError(side motorSide);
	double distFromBall(void);

void teleopEnd(void);
};

#endif /* SRC_VISIONSUBSYSTEM_H_ */
