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
	robot.joystick.register_button(SHOOTER_FIRE, 1, 5, JoystickCache::RISING);
	robot.outLog.appendLog("ShooterSubsystem: RobotInit Success");
}
void ShooterSubsystem::teleopInit(void){
	robot.outLog.appendLog("ShooterSubsystem: TeleopInit Success");
	shooterTimer.Reset();
	shooterTimer.Start();

}

void ShooterSubsystem::teleop(void){

	double fireTime = SmartDashboard::GetNumber(shooterReturn.n, shooterReturn.v);
	if (!robot.isHybrid){
		if (robot.joystick.button(SHOOTER_FIRE)
		&& (shooterTimer.Get() >= SmartDashboard::GetNumber(shooterReturn.n, shooterReturn.v) + 3.0)){
			leftShooter.Set(DoubleSolenoid::kForward);
			rightShooter.Set(DoubleSolenoid::kForward);
		}
		if (shooterTimer.Get() >= (SmartDashboard::GetNumber(shooterReturn.n, shooterReturn.v))
		&& (shooterTimer.Get() <= (SmartDashboard::GetNumber(shooterReturn.n, shooterReturn.v) + 2.5))){
			leftShooter.Set(DoubleSolenoid::kReverse);
			rightShooter.Set(DoubleSolenoid::kReverse);
		}
		if(shooterTimer.Get() > (SmartDashboard::GetNumber(shooterReturn.n, shooterReturn.v) + 2.5)){
			leftShooter.Set(DoubleSolenoid::kOff);
			rightShooter.Set(DoubleSolenoid::kOff);
		}


//		if (robot.joystick.button(SHOOTER_FIRE) && shooterTimer.Get() >=4.5){
//			leftShooter.Set(true);
//			rightShooter.Set(true);
////			backShooter.Set(false);
////			exhaustShooter.Set(false);
//			shooterTimer.Reset();
//		}
//	if (shooterTimer.Get() >= fireTime && shooterTimer.Get() <= fireTime+4.0){
//		leftShooter.Set(false);
//		rightShooter.Set(false);
////		backShooter.Set(true);
////		exhaustShooter.Set(false);
//	}//else if (shooterTimer.Get() >= fireTime+4.0 && shooterTimer.Get() <= fireTime+5.0){
////		leftShooter.Set(false);
////		rightShooter.Set(false);
////		backShooter.Set(false);
////		exhaustShooter.Set(true);
////	}

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




