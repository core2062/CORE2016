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
	shooterFlag = false;
	shooterTimer.Reset();
	shooterTimer.Start();
}
void ShooterSubsystem::teleop(void){
//	double fireTime = SmartDashboard::GetNumber(shooterReturn.n, shooterReturn.v);
	if (!robot.isHybrid){
		if (robot.joystick.button(SHOOTER_FIRE) && robot.analogSensorMap[RIGHT_POT]->GetVoltage() < SmartDashboard::GetNumber(pickupHeight1.n,pickupHeight1.v)
			&& (shooterTimer.Get() >= SmartDashboard::GetNumber(shooterReturn.n, shooterReturn.v) + 3.0)){
			shooterFlag = true;
			leftShooter.Set(DoubleSolenoid::kForward);
			rightShooter.Set(DoubleSolenoid::kForward);
			shooterTimer.Reset();
		}
		if (shooterTimer.Get() >= (SmartDashboard::GetNumber(shooterReturn.n, shooterReturn.v))
				&& (shooterTimer.Get() <= (SmartDashboard::GetNumber(shooterReturn.n, shooterReturn.v) + 2.5)) && shooterFlag){
			leftShooter.Set(DoubleSolenoid::kReverse);
			rightShooter.Set(DoubleSolenoid::kReverse);
		}
		if(shooterTimer.Get() > (SmartDashboard::GetNumber(shooterReturn.n, shooterReturn.v) + 2.5) && shooterFlag){
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
