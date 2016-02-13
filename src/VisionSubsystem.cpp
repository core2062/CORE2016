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
/*
	double goalXCords[3] =
	{
			visionTable->GetNumber("goal1_x",-1),
			visionTable->GetNumber("goal2_x",-1),
			visionTable->GetNumber("goal3_x",-1)
	};
	double goalAreas[3] = {
			visionTable->GetNumber("goal1_width",-1)*visionTable->GetNumber("goal1_height",-1),
			visionTable->GetNumber("goal2_width",-1)*visionTable->GetNumber("goal2_height",-1),
			visionTable->GetNumber("goal3_width",-1)*visionTable->GetNumber("goal3_height",-1)
	};
*/
//	std::string debug = visionTable->GetString("debug", "NoTable");
	std::string debug = "NoTable";
	if (debug == "NoTable"){
		std::cout << "ERROR: Vision table not found!, check PIs" << std::endl;
		return;
	}
//	std::vector<double> ballXCords = ballTable->GetNumberArray("xCord", llvm::ArrayRef<double>());
//	std::vector<double> goalXCords = goalTable->GetNumberArray("xCord", llvm::ArrayRef<double>());
//	std::vector<double> ballAreas = ballTable->GetNumberArray("area", llvm::ArrayRef<double>());
//	std::vector<double> goalAreas = goalTable->GetNumberArray("area", llvm::ArrayRef<double>());


		ballArea = -1;
		ballX = -1;

//		for (uint8_t i = 0; i < ballXCords.size(); i++){
//			if ((ballAreas[i] > ballArea) && ballAreas[i] < (VISION_WIDTH * VISION_HEIGHT )){
//				ballX = ballXCords[i];
//				ballArea =  ballAreas[i];
//			}
//		}


		goalX = -1;
/*
		double biggestArea = 5;
		for (uint8_t i = 0; i < 3; i++){
			if ((goalAreas[i] > biggestArea) /*&& goalAreas[i] < (VISION_WIDTH * VISION_HEIGHT * .9333)*//*){
				goalX = goalXCords[i];
//				std::cout << "WARNING: new goalx found" << std::endl;
				biggestArea = goalAreas[i];
			}
		}
		if (biggestArea == 5){
			goalX = -1;
		}

		SmartDashboard::PutNumber("Goal Area", goalAreas[0]);
		SmartDashboard::PutNumber("Goal X", goalX);
	*/
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

double VisionSubsystem::getBallX(){
	return ballX;
}
double VisionSubsystem::getBallArea(){
	return ballArea;
}
double VisionSubsystem::getGoalX(){
	return goalX;
}


