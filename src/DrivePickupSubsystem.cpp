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

    	try {
            ahrs = new AHRS(SerialPort::Port::kMXP);
        } catch (std::exception ex ) {
            std::string err_string = "Error instantiating navX-MXP:  ";
            err_string += ex.what();
            DriverStation::ReportError(err_string.c_str());
        }

	robot.outLog.appendLog("DriveSubsystem: RobotInit Success");
}
void DrivePickupSubsystem::teleopInit(void){


    bool is_calibrating = ahrs->IsCalibrating();
    if ( !is_calibrating ) {
//        Wait( 0.3 );
        ahrs->ZeroYaw();
    }

	robot.joystick.register_axis(DRIVE_ROT, 0, 2);
	robot.joystick.register_axis(DRIVE_MAG, 0, 1);
	robot.joystick.register_button(DRIVE_SPEED, 0, 5);
	robot.joystick.register_button(DRIVE_AUTO_PICKUP, 0, 2);
	robot.joystick.register_button(DRIVE_GOAL, 0 , 1);
	robot.joystick.register_button(DRIVE_PICKUP_IN, 1, 7);
	robot.joystick.register_button(DRIVE_PICKUP_OUT, 1, 8);
	robot.joystick.register_combo(COMBO5, 0, 3);

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

	robot.outLog.appendLog("DriveSubsystem: TeleopInit Success");

}

void DrivePickupSubsystem::teleop(void){

if (robot.joystick.combo(COMBO5)){
	ahrs->ZeroYaw();
	robot.outLog.appendLog("Manual Reset Gyro Yaw");
}

SmartDashboard::PutNumber(robot.sd.compass.n, ahrs->GetCompassHeading());

	if (!robot.isHybrid){

	pickupMotor.Set((robot.joystick.button(DRIVE_PICKUP_IN))?PICKUP_SPEED:(robot.joystick.button(DRIVE_PICKUP_OUT))?-PICKUP_SPEED:0.0);


	/////////////////////////////////////////
	//////// FIND AND DEADBAND DRIVE ////////
	/////////////////////////////////////////
	double drive_mag = robot.joystick.axis(DRIVE_MAG);
	double drive_rot = robot.joystick.axis(DRIVE_ROT);

	//Simple Dead-banding
	if (drive_rot < 0.05 && drive_rot > -.05){
		drive_rot = 0;
	}
	if (drive_mag < .05 && drive_mag > -.05){
		drive_mag = 0;
	}
	drive_mag *= -1;

	if ((drive_rot == 0) && (oldRot != 0.0)){
		resetQ = 6;
	}
	if (resetQ != 0){
		if (resetQ == 3){
			ahrs->ZeroYaw();
//				gyroPID.setPoint = imu->GetYaw();
		}
		resetQ--;
	}
	oldRot = drive_rot;

	//////////////////////////////////////
	///////// VISION DRIVE THINGS ////////
	//////////////////////////////////////
	if((drive_rot == 0 && drive_mag == 0)){
		if(robot.joystick.button(DRIVE_AUTO_PICKUP)){





		}else if (robot.joystick.button(DRIVE_GOAL)){





		}
	}





	///////////////////////////////////////
	///////// GYRO CALCULATIONS ///////////
	///////////////////////////////////////
		double gyroRate = ahrs->GetYaw();
		//Gyro PID
		if((drive_rot==0.0 && resetQ == 0 && !SmartDashboard::GetBoolean("disableGyro",false))){
			double gyroError =  gyroSet - gyroRate;
//			SmartDashboard::PutNumber("Gyro PID Error", gyroPID.mistake);

			double gyroOutput = (SmartDashboard::GetNumber(robot.sd.rotationPValue.n, robot.sd.rotationPValue.v)*gyroError);
//			SmartDashboard::PutNumber("Gyro PID Out before", gyroOutput);
			gyroOutput = gyroOutput > 1.0 ? 1.0 : (gyroOutput < -1.0 ? -1.0 : gyroOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
			drive_rot = gyroOutput;
		}
			if (drive_rot < .05 && drive_rot > -.05){
				drive_rot = 0;
			}



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
	double a = SmartDashboard::GetNumber(robot.sd.etherA.n, robot.sd.etherA.v);
	double b = SmartDashboard::GetNumber(robot.sd.etherB.n, robot.sd.etherB.v);


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

	frontLeft.Set(left);
	backLeft.Set(left);
	frontRight.Set(right);
	backRight.Set(right);



	}else{
		frontLeft.Set(0);
		backLeft.Set(0);
		frontRight.Set(0);
		backRight.Set(0);
		pickupMotor.Set(0);
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


