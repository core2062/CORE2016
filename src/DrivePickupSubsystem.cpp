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
	robot.joystick.register_axis(DRIVE_MAG2, 1, 3);
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

	std::string* arcade = new std::string("arcade");
	std::string* tank = new std::string("tank");
	std::string* ether = new std::string("ether");

	driveChooser.AddDefault("ether", ether);
	driveChooser.AddObject("arcade", arcade);
	driveChooser.AddObject("tank", tank);

	SmartDashboard::PutData("drive-chooser", &driveChooser);

}

void DrivePickupSubsystem::teleop(void){
	double drive_mag = robot.joystick.axis(controllerInputs::DRIVE_MAG);
	double drive_mag2 = robot.joystick.axis(controllerInputs::DRIVE_MAG2);
	double drive_rot = robot.joystick.axis(controllerInputs::DRIVE_ROT);
//	drive_mag*=(robot.joystick.button(controllerInputs::DRIVE_SPEED))?1.0:NORMAL_SPEED;
//	drive_rot*=(robot.joystick.button(controllerInputs::DRIVE_SPEED))?1.0:NORMAL_SPEED;

//	bool autoPickupButton = robot.joystick.button(controllerInputs::AUTO_PICKUP);
//	bool pickupOn = false;
//	bool cycleLift = false;

//Simple Dead-banding
	if (drive_rot < 0.05 && drive_rot > -.05){
		drive_rot = 0;
	}

	if (drive_mag < .05 && drive_mag > -.05){
		drive_mag = 0;
	}
	if (drive_mag2 < .05 && drive_mag2 > -.05){
		drive_mag2 = 0;
	}


	drive_mag *= -1;
	drive_mag2 *= -1;
 // Arcade Dive //
//	double maxPercent = 1;
//	double maxMotorSpeed = .99;



	// AutoPickup //
//	double angleTollerance = 3;
//	if(autoPickupButton == true){
//		if(vision->angleError(LEFT))
//	}


/////////////////////////////
/////   Motor Outputs   /////
/////////////////////////////

	double left = 0;
	double right = 0;

	std::string choice = * (std::string*) driveChooser.GetSelected();
//std::string choice = "tank";
if (choice == "ether"){
//	double a = SmartDashboard::GetNumber(etherA.n, etherA.v);
//	double b = SmartDashboard::GetNumber(etherB.n, etherB.v);
double a = 1.0;
double b = 0.0;


	if (drive_mag>0){
		if (drive_rot>=0){
			left = etherL(drive_mag, drive_rot, a, b);
			right = etherR(drive_mag, drive_rot, a, b);
		} else{
			left = etherR(drive_mag, -drive_rot, a, b);
			right = etherL(drive_mag, -drive_rot, a, b);
		}
	} else if (drive_mag < 0){
		if (drive_rot>=0){

			left = -etherR(-drive_mag, drive_rot, a, b);
			right = -etherL(-drive_mag, drive_rot, a, b);
		} else{
			left = -etherL(-drive_mag, -drive_rot, a, b);
			right = -etherR(-drive_mag, -drive_rot, a, b);
		}
	} else {
		left = (drive_rot);
		right = (-drive_rot);
	}
}else if (choice == "tank"){
	left = drive_mag;
	right = drive_mag2;
}

frontLeft.Set(left);
backLeft.Set(left);
frontRight.Set(right);
backRight.Set(right);





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


