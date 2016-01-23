/*
 * VisionSubsystem.cpp
 *
 *  Created on: Jan 15, 2016
 *      Author: core
 */
#include "VisionSubsystem.h"
std::string VisionSubsystem::name(void){
	return "Vision";
}

void VisionSubsystem::robotInit(void){

	robot.outLog.appendLog("VisionSubsystem: RobotInit Success");



}
void VisionSubsystem::teleopInit(void){
	robot.outLog.appendLog("VisionSubsystem: TeleopInit Success");



}

void VisionSubsystem::teleop(void){

	///////////////////////////////////////////////////
	///////                                      //////
	///////      Camera Angle Calculations       //////
	///////                                      //////
	///////////////////////////////////////////////////

	const double cameraFOV = 68.5;
	const double cameraMountAngle = 10; // Angle center of camera makes with the chassis //
	const double distBetweenCameras = 10; //In inches //
	const int maxXRes = 1280;

	int leftCameraXPoint; //need to be supplied this with vision //
	int rightCameraXPoint; // need to be supplied this with vision //

	double relativeLeftAngle = 0;
	double relativeRightAngle = 0;
	double rightAngleError = 0;
	double leftAngleError = 0;
	double precentLeftAngle = leftCameraXPoint/maxXRes;
	double precentRightAngle = rightCameraXPoint/maxXRes;

	SmartDashboard::PutNumber("Left Camera Angle", relativeLeftAngle);
	SmartDashboard::PutNumber("Right Camera Angle", relativeRightAngle);
	SmartDashboard::PutNumber("Left Camera Angle Error", leftAngleError);
	SmartDashboard::PutNumber("Right Camera Angle Error", rightAngleError);

	// Angle Calculations for each side camera //
	if(precentLeftAngle <= .5){
		relativeLeftAngle = ((.5*cameraFOV)-(precentLeftAngle*cameraFOV))+(cameraMountAngle);
	}else{
		relativeLeftAngle =	cameraMountAngle-((precentLeftAngle*cameraFOV)-(.5*cameraFOV));
	}
	if(precentRightAngle <= .5){
		relativeRightAngle = cameraMountAngle-((.5*cameraFOV)-(precentRightAngle*cameraFOV));
	}else{
		relativeRightAngle = ((precentRightAngle*cameraFOV)-(.5*cameraFOV))+(cameraMountAngle);
	}
	// Determine Angle Error //
	leftAngleError = relativeLeftAngle - cameraMountAngle; // Positive Error is away from chassis //
	rightAngleError = relativeRightAngle - cameraMountAngle; // Negative Error is towards chassis //



	}

void VisionSubsystem::teleopEnd(void){
	robot.outLog.appendLog("Vision tele end");
}



