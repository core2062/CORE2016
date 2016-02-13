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
	robot.joystick.register_button(SHOOTER_FIRE, 1, 2, JoystickCache::RISING);
	robot.outLog.appendLog("ShooterSubsystem: RobotInit Success");
}
void ShooterSubsystem::teleopInit(void){
	robot.outLog.appendLog("ShooterSubsystem: TeleopInit Success");
	shooterTimer.Reset();
	shooterTimer.Start();

}

void ShooterSubsystem::teleop(void){

	if (!robot.isHybrid){
		if (robot.joystick.button(SHOOTER_FIRE) && shooterTimer.Get() >=2.5){
			leftShooter.Set(DoubleSolenoid::kForward);
			rightShooter.Set(DoubleSolenoid::kForward);
			shooterTimer.Reset();
		}
	}
	if (shooterTimer.Get() >= SmartDashboard::GetNumber(shooterReturn.n, shooterReturn.v)){
		leftShooter.Set(DoubleSolenoid::kReverse);
		rightShooter.Set(DoubleSolenoid::kReverse);
	}

}

void ShooterSubsystem::teleopEnd(void){
	robot.outLog.appendLog("shooter tele end");

}
void ShooterSubsystem::shoot(void){
		leftShooter.Set(DoubleSolenoid::kForward);
		rightShooter.Set(DoubleSolenoid::kForward);
		shooterTimer.Reset();
}




