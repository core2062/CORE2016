#include <DrivePickupSubsystem.h>
#include <iostream>


std::string DrivePickupSubsystem::name(void){
	return "Drive";
}

void DrivePickupSubsystem::robotInit(void){

	robot.outLog.appendLog("DriveSubsystem: RobotInit Success");
}
void DrivePickupSubsystem::teleopInit(void){
	robot.outLog.appendLog("DriveSubsystem: TeleopInit Success");


//	frontLeft.SetSafetyEnabled(true);
//	backLeft.SetSafetyEnabled(true);
//	frontRight.SetSafetyEnabled(true);
//	backRight.SetSafetyEnabled(true);
//	frontLeft.Set(0.0);
//	backLeft.Set(0.0);
//	frontRight.Set(0.0);
//	backRight.Set(0.0);

}

void DrivePickupSubsystem::teleop(void){


//Simple Dead-banding
//		drive_x = robot.joystick.axis(controllerInputs::DRIVE_X);
//		if (drive_x < 0.05 && drive_x > -.05){
//			drive_x = 0;
//		}
//		drive_y = robot.joystick.axis(controllerInputs::DRIVE_Y);
//		if (drive_y < .05 && drive_y > -.05){
//			drive_y = 0;
//		}
//		drive_y *= -1;
//	drive_rotation = robot.joystick.axis(controllerInputs::DRIVE_ROT);
//	if (drive_rotation < .05 && drive_rotation > -.05){
//		drive_rotation = 0;
//	}

	}

void DrivePickupSubsystem::teleopEnd(void){
	robot.outLog.appendLog("drive tele end");
//	frontLeft.SetSafetyEnabled(false);
//	frontRight.SetSafetyEnabled(false);
//	backLeft.SetSafetyEnabled(false);
//	backRight.SetSafetyEnabled(false);
//	frontLeft.Set(0.0);
//	frontRight.Set(0.0);
//	backLeft.Set(0.0);
//	backRight.Set(0.0);
}
