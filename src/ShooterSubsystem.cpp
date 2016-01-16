/*
 * ShooterSubsystem.cpp
 *
 *  Created on: Jan 15, 2016
 *      Author: core
 */
#include "ShooterSubsystem.h"

std::string ShooterSubsystem::name(void){
	return "Shooter";
}

void ShooterSubsystem::robotInit(void){

	robot.outLog.appendLog("ShooterSubsystem: RobotInit Success");
}
void ShooterSubsystem::teleopInit(void){
	robot.outLog.appendLog("ShooterSubsystem: TeleopInit Success");


}

void ShooterSubsystem::teleop(void){


	}

void ShooterSubsystem::teleopEnd(void){
	robot.outLog.appendLog("shooter tele end");

}



