#include <DrivePickupSubsystem.h>
#include <iostream>


std::string DrivePickupSubsystem::name(void){
	return "Drive";
}

void DrivePickupSubsystem::robotInit(void){

	robot.outLog.appendLog("DriveSubsystem: RobotInit Success");
	robot.joystick.register_axis(DRIVE_X, 1, 4);
	robot.joystick.register_axis(DRIVE_Y, 1, 5);
}
void DrivePickupSubsystem::teleopInit(void){
	robot.outLog.appendLog("DriveSubsystem: TeleopInit Success");


	frontLeft.SetSafetyEnabled(true);
	backLeft.SetSafetyEnabled(true);
	frontRight.SetSafetyEnabled(true);
	backRight.SetSafetyEnabled(true);
	frontLeft.Set(0.0);
	backLeft.Set(0.0);
	frontRight.Set(0.0);
	backRight.Set(0.0);

}

void DrivePickupSubsystem::teleop(void){
	double drive_y = robot.joystick.axis(controllerInputs::DRIVE_Y);
	double drive_x = robot.joystick.axis(controllerInputs::DRIVE_X);
	double maxPercent = 1;
	double maxMotorSpeed = .99;

//	double drive_rotation = robot.joystick.axis(controllerInputs::DRIVE_ROT);
//Simple Dead-banding
		if (drive_x < 0.05 && drive_x > -.05){
			drive_x = 0;
		}
	if (drive_y < .05 && drive_y > -.05){
		drive_y = 0;
	}
	drive_y *= -1;
//	if (drive_rotation < .05 && drive_rotation > -.05){
//		drive_rotation = 0;
//	}


	if((drive_y+drive_x) >= maxPercent){
		frontLeft.Set(maxMotorSpeed);
		backLeft.Set(maxMotorSpeed);
	}else if((drive_y+drive_x) <= (-maxPercent)){
		frontLeft.Set(-maxMotorSpeed);
		backLeft.Set(-maxMotorSpeed);
	}else{
		frontLeft.Set(drive_y+drive_x);
		backLeft.Set(drive_y+drive_x);
	}

	if((drive_y-drive_x) >= maxPercent){
		frontRight.Set(maxMotorSpeed);
		backRight.Set(maxMotorSpeed);
	}else if((drive_y-drive_x) <= (-maxPercent)){
		frontRight.Set(-maxMotorSpeed);
		backRight.Set(-maxMotorSpeed);
	}else{
		frontRight.Set(drive_y-drive_x);
		backRight.Set(drive_y-drive_x);
	}

	}

void DrivePickupSubsystem::teleopEnd(void){
	robot.outLog.appendLog("drive tele end");
	frontLeft.SetSafetyEnabled(false);
	frontRight.SetSafetyEnabled(false);
	backLeft.SetSafetyEnabled(false);
	backRight.SetSafetyEnabled(false);
	frontLeft.Set(0.0);
	frontRight.Set(0.0);
	backLeft.Set(0.0);
	backRight.Set(0.0);
}
