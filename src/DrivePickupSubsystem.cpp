#include <DrivePickupSubsystem.h>
#include <iostream>


std::string DrivePickupSubsystem::name(void){
	return "Drive";
}

void DrivePickupSubsystem::robotInit(void){

	robot.outLog.appendLog("DriveSubsystem: RobotInit Success");
	robot.joystick.register_axis(DRIVE_X, 1, 4);
	robot.joystick.register_axis(DRIVE_Y, 1, 5);
	robot.joystick.register_button(AUTO_PICKUP, 2, 8);
}
void DrivePickupSubsystem::teleopInit(void){
	robot.outLog.appendLog("DriveSubsystem: TeleopInit Success");


	frontLeft.SetSafetyEnabled(true);
	backLeft.SetSafetyEnabled(true);
	frontRight.SetSafetyEnabled(true);
	backRight.SetSafetyEnabled(true);
	pickupMotor.SetSafetyEnabled(true);
	frontLeft.Set(0.0);
	backLeft.Set(0.0);
	frontRight.Set(0.0);
	backRight.Set(0.0);
	pickupMotor.Set(0.0);

}

void DrivePickupSubsystem::teleop(void){
	double drive_y = robot.joystick.axis(controllerInputs::DRIVE_Y);
	double drive_x = robot.joystick.axis(controllerInputs::DRIVE_X);
	bool autoPickupButton = robot.joystick.button(controllerInputs::AUTO_PICKUP);
	bool pickupOn = false;
	bool cycleLift = false;

//Simple Dead-banding
	if (drive_x < 0.05 && drive_x > -.05){
		drive_x = 0;
	}
	if (drive_y < .05 && drive_y > -.05){
		drive_y = 0;
	}
	drive_y *= -1;

 // Arcade Dive //
	double maxPercent = 1;
	double maxMotorSpeed = .99;

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

	// AutoPickup //
//	double angleTollerance = 3;
//	if(autoPickupButton == true){
//		if(vision->angleError(LEFT))
//	}

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

void DrivePickupSubsystem::bolderAlign(double lError, double rError, double distAway){

	//need's to be written!!

}

void DrivePickupSubsystem::setPickupSpeed(double speed){
	pickupMotor.Set(speed);
}

