#include <DrivePickupSubsystem.h>
#include <iostream>

double inline etherL(double fwd, double rcw, double a, double b){
	return fwd + b*rcw*(1-fwd);
}

double inline etherR(double fwd, double rcw, double a, double b){
	return fwd-b*rcw + fwd*rcw*(b-a-1);
}

void DrivePickupSubsystem::setPickupHeight(smartDB height){
	leftPickupMotor.Set(height.v);
	rightPickupMotor.Set(height.v);
};



std::string DrivePickupSubsystem::name(void){
	return "Drive";
}

void DrivePickupSubsystem::robotInit(void){

	robot.outLog.appendLog("DriveSubsystem: RobotInit Success");
}
void DrivePickupSubsystem::teleopInit(void){


	robot.joystick.register_axis(DRIVE_ROT, 0, 2);
	robot.joystick.register_axis(DRIVE_MAG, 0, 1);
	robot.joystick.register_axis(DRIVE_MAG2, 0, 3);
	robot.joystick.register_button(DRIVE_SPEED, 0, 7);
	robot.joystick.register_button(DRIVE_AUTO_PICKUP, 0, 2);
	robot.joystick.register_button(DRIVE_GOAL, 0 , 1);
	robot.joystick.register_button(DRIVE_PICKUP_HEIGHT1, 1, 6);
	robot.joystick.register_button(DRIVE_PICKUP_HEIGHT2, 1, 7);
	robot.joystick.register_button(DRIVE_PICKUP_HEIGHT3, 1, 8);
	robot.joystick.register_button(DRIVE_PICKUP_HEIGHT4, 1, 9);
	robot.joystick.register_button(DRIVE_PICKUP_HEIGHT5, 1, 10);
	robot.joystick.register_combo(COMBO5, 0, 3);

	frontLeft.SetSafetyEnabled(true);
	backLeft.SetSafetyEnabled(true);
	frontRight.SetSafetyEnabled(true);
	backRight.SetSafetyEnabled(true);
	leftPickupMotor.SetSafetyEnabled(true);
	rightPickupMotor.SetSafetyEnabled(true);
	rollerMotor.SetSafetyEnabled(true);
	frontLeft.Set(0.0);
	backLeft.Set(0.0);
	frontRight.Set(0.0);
	backRight.Set(0.0);
	leftPickupMotor.Set(0.0);
	rightPickupMotor.Set(0.0);
	rollerMotor.Set(0.0);



	std::string* arcade = new std::string("arcade");
	std::string* tank = new std::string("tank");
	std::string* ether = new std::string("ether");
	std::string* cord = new std::string("cord test");

	driveChooser.AddDefault("ether", ether);
	driveChooser.AddObject("arcade", arcade);
	driveChooser.AddObject("tank", tank);
	driveChooser.AddObject("cord test", cord);

	SmartDashboard::PutData("drive-chooser", &driveChooser);


	robot.outLog.appendLog("DriveSubsystem: TeleopInit Success");

}

void DrivePickupSubsystem::teleop(void){





if (robot.joystick.combo(COMBO5)){
	robot.ahrs->ZeroYaw();
	robot.outLog.appendLog("Manual Reset Gyro Yaw");
	std::cout << "WARNING: Manual Reset Gyro Yaw" << std::endl;
//	DriveAction driveThing(robot, 5, 1.0);
//	robot.teleSeq->add(driveThing);
}

SmartDashboard::PutNumber( compass.n, robot.ahrs->GetCompassHeading());

	if (!robot.isHybrid){
#ifdef SHOW_MOTORS
  SmartDashboard::PutNumber(std::string("back right motor current"), robot.motorMap[BACK_RIGHT]->GetOutputCurrent());
  SmartDashboard::PutNumber(std::string("front right motor current"), robot.motorMap[FRONT_RIGHT]->GetOutputCurrent());
  SmartDashboard::PutNumber(std::string("back left motor current"), robot.motorMap[BACK_LEFT]->GetOutputCurrent());
  SmartDashboard::PutNumber(std::string("front left motor current"), robot.motorMap[FRONT_LEFT]->GetOutputCurrent());
#endif
  	SmartDashboard::PutNumber(leftPickupPos.n,leftPickupMotor.Get());
  	SmartDashboard::PutNumber(rightPickupPos.n,rightPickupMotor.Get());
//	double pickup_val = (robot.joystick.button(DRIVE_PICKUP_IN))?PICKUP_SPEED:(robot.joystick.button(DRIVE_PICKUP_OUT))?-PICKUP_SPEED:0.0;

	/////////////////////////////////////////
	//////// FIND AND DEADBAND DRIVE ////////
	/////////////////////////////////////////
	drive_mag = robot.joystick.axis(DRIVE_MAG);
	drive_rot = robot.joystick.axis(DRIVE_ROT);
	double drive_mag2 = robot.joystick.axis(DRIVE_MAG2);

	//Simple Dead-banding
	if (drive_rot < 0.05 && drive_rot > -.05){
		drive_rot = 0;
	}
	if (drive_mag < .05 && drive_mag > -.05){
		drive_mag = 0;
	}
	drive_mag *= -1;
	if (drive_mag2 < .05 && drive_mag2 > -.05){
		drive_mag2 = 0;
	}
	drive_mag2 *= -1;

	if ((drive_rot == 0) && (oldRot != 0.0)){
		resetQ = 6;
	}
	if (resetQ != 0){
		if (resetQ == 3){
			robot.ahrs->ZeroYaw();
//				gyroPID.setPoint = imu->GetYaw();
		}
		resetQ--;
	}
	oldRot = drive_rot;

	//////////////////////////////////////
	///////// VISION DRIVE THINGS ////////
	//////////////////////////////////////
	int ballX = vision->getBallX();
	int goalX = vision->getGoalX();
	gyroSet = 0.0;

	if((drive_rot == 0 && drive_mag == 0)){

		if(robot.joystick.button(DRIVE_AUTO_PICKUP)){

			int ballArea = vision->getBallArea();
			if (ballX == -1){
				drive_rot = (oldBallX == -1)?NORMAL_SPEED:0.0;
			}else if (std::fabs(ballX-VISION_BALL_TARGET) > VISION_WIDTH/2.0){
				if (ballX>VISION_BALL_TARGET){
					drive_rot = -NORMAL_SPEED;
				}else{
					drive_rot = NORMAL_SPEED;
				}
			}else{
				gyroSet = ((ballX-(VISION_WIDTH/2.0))/(VISION_WIDTH/2.0))*(VISION_H_FOV/2.0);
//				pickup_val = PICKUP_SPEED;
				if (ballArea <= VISION_WIDTH * VISION_HEIGHT * .35){
					drive_mag = VISION_FAST;
				}else{
					drive_mag = VISION_SLOW;
				}
			}



		}else if (robot.joystick.button(DRIVE_GOAL)){

			if (goalX == -1){
				drive_rot = (oldGoalX == -1)?NORMAL_SPEED:0.0;
			}else if (std::fabs(goalX-VISION_WIDTH/2.0) > VISION_WIDTH/2.0){
				if (goalX>VISION_WIDTH/2.0){
					drive_rot = -NORMAL_SPEED;
				}else{
					drive_rot = NORMAL_SPEED;
				}
			}else{
				gyroSet  = ((goalX-(VISION_WIDTH/2.0))/(VISION_WIDTH/2.0))*(VISION_H_FOV/2.0);
			}



		}
	}
	oldBallX = ballX;
	oldGoalX = goalX;



	///////////////////////////////////////
	///////// GYRO CALCULATIONS ///////////
	///////////////////////////////////////

		double gyroRate = robot.ahrs->GetYaw();
		//Gyro PID
		if((drive_rot==0.0 && resetQ == 0 && !SmartDashboard::GetBoolean("disableGyro",false))){
			double gyroError =  gyroSet - gyroRate;
//			SmartDashboard::PutNumber("Gyro PID Error", gyroPID.mistake);

			double gyroOutput = (SmartDashboard::GetNumber( rotationPValue.n,  rotationPValue.v)*gyroError);
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
	double a = SmartDashboard::GetNumber( etherA.n,  etherA.v);
	double b = SmartDashboard::GetNumber( etherB.n,  etherB.v);

	std::string choice = * (std::string*) driveChooser.GetSelected();

	if (choice == "ether"){
		if (drive_mag>0){
			if (drive_rot>=0){
				left = etherL(drive_mag, drive_rot, a, b * (robot.joystick.button(DRIVE_SPEED)?2:1));
				right = etherR(drive_mag, drive_rot, a, b * (robot.joystick.button(DRIVE_SPEED)?2:1));
			} else{
				left = etherR(drive_mag, -drive_rot, a, b * (robot.joystick.button(DRIVE_SPEED)?2:1));
				right = etherL(drive_mag, -drive_rot, a, b * (robot.joystick.button(DRIVE_SPEED)?2:1));
			}
		} else if (drive_mag < 0){
			if (drive_rot>=0){

				left = -etherR(-drive_mag, drive_rot, a, b * (robot.joystick.button(DRIVE_SPEED)?2:1));
				right = -etherL(-drive_mag, drive_rot, a, b * (robot.joystick.button(DRIVE_SPEED)?2:1));
			} else{
				left = -etherL(-drive_mag, -drive_rot, a, b * (robot.joystick.button(DRIVE_SPEED)?2:1));
				right = -etherR(-drive_mag, -drive_rot, a, b * (robot.joystick.button(DRIVE_SPEED)?2:1));
			}
		} else {
			left = (drive_rot * (robot.joystick.button(DRIVE_SPEED)?1:SmartDashboard::GetNumber(quickTurn.n,quickTurn.v)));
			right = (-drive_rot * (robot.joystick.button(DRIVE_SPEED)?1:SmartDashboard::GetNumber(quickTurn.n,quickTurn.v)));
		}
	}else if (choice == "tank"){
		left = drive_mag;
		right = drive_mag2;
	}else if (choice == "cord test"){
		if (drive_mag != 0){
			left = (drive_mag);
			right = (drive_mag);
		}else{
			left = (drive_rot * (robot.joystick.button(DRIVE_SPEED)?1:SmartDashboard::GetNumber(quickTurn.n,quickTurn.v)));
			right = (-drive_rot * (robot.joystick.button(DRIVE_SPEED)?1:SmartDashboard::GetNumber(quickTurn.n,quickTurn.v)));
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
	}

//Pickup Height's buttons
	if(robot.joystick.button(DRIVE_PICKUP_HEIGHT1))
		setPickupHeight(pickupHeight1);
	else if(robot.joystick.button(DRIVE_PICKUP_HEIGHT2))
		setPickupHeight(pickupHeight2);
	else if(robot.joystick.button(DRIVE_PICKUP_HEIGHT3))
		setPickupHeight(pickupHeight3);
	else if(robot.joystick.button(DRIVE_PICKUP_HEIGHT4))
		setPickupHeight(pickupHeight4);
	else if(robot.joystick.button(DRIVE_PICKUP_HEIGHT5))
		setPickupHeight(pickupHeight5);



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
//	pickupMotor.Set(speed);
}
