#include <DrivePickupSubsystem.h>
#include <iostream>

double inline etherL(double fwd, double rcw, double a, double b){
	return fwd + b*rcw*(1-fwd);
}

double inline etherR(double fwd, double rcw, double a, double b){
	return fwd-b*rcw + fwd*rcw*(b-a-1);
}



std::string DrivePickupSubsystem::name(void){
	return "Drive";
}

void DrivePickupSubsystem::robotInit(void){

	robot.outLog.appendLog("DriveSubsystem: RobotInit Success");
	robot.joystick.register_axis(DRIVE_ROT, 1, 2);
	robot.joystick.register_axis(DRIVE_MAG, 1, 1);
	robot.joystick.register_button(DRIVE_SPEED, 1, 5);
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
	double drive_mag = robot.joystick.axis(controllerInputs::DRIVE_MAG);
	double drive_rot = robot.joystick.axis(controllerInputs::DRIVE_ROT);
//	drive_mag*=(robot.joystick.button(controllerInputs::DRIVE_SPEED))?1.0:NORMAL_SPEED;
//	drive_rot*=(robot.joystick.button(controllerInputs::DRIVE_SPEED))?1.0:NORMAL_SPEED;

	bool autoPickupButton = robot.joystick.button(controllerInputs::AUTO_PICKUP);
	bool pickupOn = false;
	bool cycleLift = false;

//Simple Dead-banding
	if (drive_rot < 0.05 && drive_rot > -.05){
		drive_rot = 0;
	}
	if (drive_mag < .05 && drive_mag > -.05){
		drive_mag = 0;
	}
	drive_mag *= -1;

 // Arcade Dive //
	double maxPercent = 1;
	double maxMotorSpeed = .99;



	// AutoPickup //
//	double angleTollerance = 3;
//	if(autoPickupButton == true){
//		if(vision->angleError(LEFT))
//	}


/////////////////////////////
/////   Motor Outputs   /////
/////////////////////////////
	double left;
	double right;
	double a = SmartDashboard::GetNumber(etherA.n, etherA.v);
	double b = SmartDashboard::GetNumber(etherB.n, etherB.v);


	if (drive_mag>=0){
		if (drive_rot>=0){
			left = etherL(drive_mag, drive_rot, a, b);
			right = etherR(drive_mag, drive_rot, a, b);
		} else{
			left = etherR(drive_mag, -drive_rot, a, b);
			right = etherL(drive_mag, -drive_rot, a, b);
		}
	} else{
		if (drive_rot>=0){

			left = -etherR(-drive_mag, drive_rot, a, b);
			right = -etherL(-drive_mag, drive_rot, a, b);
		} else{
			left = -etherL(-drive_mag, -drive_rot, a, b);
			right = -etherR(-drive_mag, -drive_rot, a, b);
		}
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

void DrivePickupSubsystem::bolderAlign(double lError, double rError, double distAway){

	//need's to be written!!

}

void DrivePickupSubsystem::setPickupSpeed(double speed){
	pickupMotor.Set(speed);
}


