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

	}

void VisionSubsystem::teleopEnd(void){
	robot.outLog.appendLog("Vision tele end");
}



