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

if(run){
//
//	double goalXCords[3] =
//	{
//			visionTable->GetNumber("goal1_x",-1),
//			visionTable->GetNumber("goal2_x",-1),
//			visionTable->GetNumber("goal3_x",-1)
//	};
//	double goalAreas[3] = {
//			visionTable->GetNumber("goal1_width",-1)*visionTable->GetNumber("goal1_height",-1),
//			visionTable->GetNumber("goal2_width",-1)*visionTable->GetNumber("goal2_height",-1),
//			visionTable->GetNumber("goal3_width",-1)*visionTable->GetNumber("goal3_height",-1)
//	};

	std::string debug = visionTable->GetString("debug", "NoTable");
//	std::string debug = "NoTable";
	if (debug == "NoTable" && !flag){
		std::cout << "ERROR: Vision table not found!, check PIs" << std::endl;
		flag = true;
		return;
	}

	goalX = visionTable->GetNumber("goal_x",-1);
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


//		goalX = -1;
//
//		double biggestArea = 5;
//		for (uint8_t i = 0; i < 3; i++){
//			if ((goalAreas[i] > biggestArea) /*&& goalAreas[i] < (VISION_WIDTH * VISION_HEIGHT * .9333)*/){
//				goalX = goalXCords[i];
////				std::cout << "WARNING: new goalx found" << std::endl;
//				biggestArea = goalAreas[i];
//			}
//		}
//		if (biggestArea == 5){
//			goalX = -1;
//		}
//
//		SmartDashboard::PutNumber("Goal Area", goalAreas[0]);
		SmartDashboard::PutNumber("Goal X", goalX);
}else if (checkTimer.Get() >=5.0){
	try{
		visionTable = NetworkTable::GetTable("Vision");
		std::cout << "Warning: Vision Table Found" << std::endl;
		run = true;
		checkTimer.Stop();
	}catch(...){
		run = false;
		checkTimer.Reset();
		checkTimer.Start();

	}
}
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


