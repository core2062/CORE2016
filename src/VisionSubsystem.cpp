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

/*
 // two camera ball code
//	int leftCameraXPoint; //need to be supplied this with vision //
//	int rightCameraXPoint; // need to be supplied this with vision //

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
*/

std::vector<double> ballXCords = ballTable->GetNumberArray("xCord", llvm::ArrayRef<double>());
std::vector<double> goalXCords = goalTable->GetNumberArray("xCord", llvm::ArrayRef<double>());
std::vector<double> ballAreas = ballTable->GetNumberArray("area", llvm::ArrayRef<double>());
std::vector<double> goalAreas = goalTable->GetNumberArray("area", llvm::ArrayRef<double>());




	}

void VisionSubsystem::teleopEnd(void){
	robot.outLog.appendLog("Vision tele end");
}

double VisionSubsystem::angleError(side motorSide){
	/*
	if(motorSide == LEFT){
		return leftAngleError;
	}else if(motorSide == RIGHT){
		return rightAngleError;
	}else{
		return 0;
	}
	*/
	return 0;
}

double VisionSubsystem::distFromBall(void){
	 // Calc distance From ball //
	//return (((distBetweenCameras/2)/(sin((180-relativeLeftAngle-relativeRightAngle)/2)))*sin(relativeRightAngle));
	return 0;
}


