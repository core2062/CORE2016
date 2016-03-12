#include <DrivePickupSubsystem.h>
#include <iostream>

double inline etherL(double fwd, double rcw, double a, double b){
	return fwd + b*rcw*(1-fwd);
}

double inline etherR(double fwd, double rcw, double a, double b){
	return fwd-b*rcw + fwd*rcw*(b-a-1);
}

double DrivePickupSubsystem::leftPotValue(){
	double base = SmartDashboard::GetNumber(leftMagPotBase.n,leftMagPotBase.v);
	double max = SmartDashboard::GetNumber(magneticPotMax.n,magneticPotMax.v);
	double raw = base<0?max-leftPot.GetVoltage():leftPot.GetVoltage();
	base = fabs(base);

	return raw<base?max+raw-base:raw-base;
}
double DrivePickupSubsystem::rightPotValue(){
	double base = SmartDashboard::GetNumber(rightMagPotBase.n,rightMagPotBase.v);
	double max = SmartDashboard::GetNumber(magneticPotMax.n,magneticPotMax.v);
	double raw = base<0?max-rightPot.GetVoltage():rightPot.GetVoltage();
	base = fabs(base);

	return raw<base?max+raw-base:raw-base;
}

void DrivePickupSubsystem::setPickupHeight(smartDB height){

//	double rightPickupError =  rightPotValue() - leftPotValue() ;
//	SmartDashboard::PutNumber("Right Pickup Error", rightPickupError);
//	double rightPickupOutput = (SmartDashboard::GetNumber(pickupPValue.n, pickupPValue.v)*rightPickupError);
//	rightPickupOutput = rightPickupOutput > 0.3 ? 0.3 : (rightPickupOutput < -0.3 ? -0.3 : rightPickupOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
//	if (rightPickupOutput < .05 && rightPickupOutput > -.05){
//		rightPickupOutput = 0;
//	}
//	SmartDashboard::PutNumber("Right Pickup Output", rightPickupOutput);
//
//	double leftPickupError =  leftPotValue() - rightPotValue();
//	SmartDashboard::PutNumber("Left Pickup Error", leftPickupError);
//	double leftPickupOutput = (SmartDashboard::GetNumber(pickupPValue.n, pickupPValue.v)*leftPickupError);
//	leftPickupOutput = leftPickupOutput > 0.3 ? 0.3 : (leftPickupOutput < -0.3 ? -0.3 : leftPickupOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
//	if (leftPickupOutput < .05 && leftPickupOutput > -.05){
//		leftPickupOutput = 0;
//	}
//	SmartDashboard::PutNumber("Left Pickup Output", rightPickupOutput);
//	double otherPickupError =  ((leftPotValue() + rightPotValue()) / 2) - SmartDashboard::GetNumber(height.n, height.v);
//	SmartDashboard::PutNumber("Main Pickup Error", otherPickupError);
//	double otherPickupOutput = (SmartDashboard::GetNumber(otherPickupP.n, otherPickupP.v)*otherPickupError);
//	otherPickupOutput = otherPickupOutput > 0.8 ? 0.8 : (otherPickupOutput < -0.8 ? -0.8 : otherPickupOutput);

	double otherPickupError =  (rightPotValue()) - SmartDashboard::GetNumber(height.n, height.v);
	SmartDashboard::PutNumber("Main Pickup Error", otherPickupError);
	double otherPickupOutput = (SmartDashboard::GetNumber(otherPickupP.n, otherPickupP.v)*otherPickupError);
	otherPickupOutput = otherPickupOutput > 0.8 ? 0.8 : (otherPickupOutput < -0.8 ? -0.8 : otherPickupOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
	if (otherPickupOutput < .05 && otherPickupOutput > -.05){
		otherPickupOutput = 0;
	}
	SmartDashboard::PutNumber("Main Pickup Output", otherPickupOutput);
	leftPickupMotor.Set(DEADBAND(otherPickupOutput, .05));
	rightPickupMotor.Set(DEADBAND(otherPickupOutput, .05));
};
void DrivePickupSubsystem::setPickupHeight(smartDB height, smartDB heightL){

	double rightPickupError =  rightPotValue() - SmartDashboard::GetNumber(height.n, height.v) ;
	SmartDashboard::PutNumber("Right Pickup Error", rightPickupError);
	double rightPickupOutput = (SmartDashboard::GetNumber(pickupPValue.n, pickupPValue.v)*rightPickupError);
	rightPickupOutput = rightPickupOutput > 0.8 ? 0.8 : (rightPickupOutput < -0.8 ? -0.8 : rightPickupOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
	if (rightPickupOutput < .05 && rightPickupOutput > -.05){
		rightPickupOutput = 0;
	}
	SmartDashboard::PutNumber("Right Pickup Output", rightPickupOutput);

	double leftPickupError =  leftPotValue() - SmartDashboard::GetNumber(heightL.n, heightL.v);
	SmartDashboard::PutNumber("Left Pickup Error", leftPickupError);
	double leftPickupOutput = (SmartDashboard::GetNumber(pickupPValue.n, pickupPValue.v)*leftPickupError);
	leftPickupOutput = leftPickupOutput > 0.8 ? 0.8 : (leftPickupOutput < -0.8 ? -0.8 : leftPickupOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
	if (leftPickupOutput < .05 && leftPickupOutput > -.05){
		leftPickupOutput = 0;
	}
	SmartDashboard::PutNumber("Left Pickup Output", rightPickupOutput);



	leftPickupMotor.Set(DEADBAND(leftPickupOutput,.05));
	rightPickupMotor.Set(DEADBAND(rightPickupOutput,.05));
};
void DrivePickupSubsystem::setPickupHeight(double height){
	smartDB temp((std::string)"NULL",height);
	setPickupHeight(temp);
	}

bool DrivePickupSubsystem::autoPickup(void){
	if(rollerMotor.GetOutputCurrent() > SmartDashboard::GetNumber(pickupCurrentThresh.n, pickupCurrentThresh.v) || autoPickupFlag){
		if(!autoPickupFlag){
			autoPickupFlag = true;
			autoPickupTimer.Reset();
			autoPickupTimer.Start();
		}
		if(autoPickupTimer.Get() > 1.0){
			if(((leftPotValue() + rightPotValue()) / 2) >= SmartDashboard::GetNumber(pickupHeight5.n, pickupHeight5.v)){ //pickup height & direction will have to be tuned
				robot.motorMap[LEFT_PICKUP]->Set(0.0);
				robot.motorMap[RIGHT_PICKUP]->Set(0.0);
				autoPickupFlag = false;
				autoPickupTimer.Stop();
				autoPickupTimer.Reset();
				return true;
			} else {
				robot.motorMap[ROLLER]->Set(0.0);
				double rightPickupError =  rightPotValue() - leftPotValue() ;
				double rightPickupOutput = (SmartDashboard::GetNumber(pickupPValue.n, pickupPValue.v)*rightPickupError);
				rightPickupOutput = rightPickupOutput > 0.3 ? 0.3 : (rightPickupOutput < -0.3 ? -0.3 : rightPickupOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
				if (rightPickupOutput < .05 && rightPickupOutput > -.05){
					rightPickupOutput = 0;
				}


				double leftPickupError =  leftPotValue() - rightPotValue() ;
				double leftPickupOutput = (SmartDashboard::GetNumber(pickupPValue.n, pickupPValue.v)*leftPickupError);
				leftPickupOutput = leftPickupOutput > 0.3 ? 0.3 : (leftPickupOutput < -0.3 ? -0.3 : leftPickupOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
				if (leftPickupOutput < .05 && leftPickupOutput > -.05){
					leftPickupOutput = 0;
				}



				double otherPickupError =  ((leftPotValue() + rightPotValue()) / 2) - SmartDashboard::GetNumber(pickupHeight5.n, pickupHeight5.v);
				double otherPickupOutput = (SmartDashboard::GetNumber(otherPickupP.n, otherPickupP.v)*otherPickupError);
				otherPickupOutput = otherPickupOutput > 0.8 ? 0.8 : (otherPickupOutput < -0.8 ? -0.8 : otherPickupOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
				if (otherPickupOutput < .05 && otherPickupOutput > -.05){
					otherPickupOutput = 0;
				}
				leftPickupMotor.Set(otherPickupOutput + leftPickupOutput);
				rightPickupMotor.Set(otherPickupOutput + rightPickupOutput);
			}
		} else {
			return false;
		}
	} else {
		robot.motorMap[ROLLER]->Set(FORWARD);
		return false;
	}
	return false;
}

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
	robot.joystick.register_axis(PICKUP_AXIS, 1, 1);
	robot.joystick.register_button(DRIVE_SPEED, 0, 5);

	robot.joystick.register_button(DRIVE_LSPEED, 0, 7);
	robot.joystick.register_button(DRIVE_AUTO_PICKUP, 0, 8);
	robot.joystick.register_button(DRIVE_GOAL, 0 , 1);
	robot.joystick.register_button(DRIVE_REVERSE, 0, 6, JoystickCache::RISING);
	robot.joystick.register_button(DRIVE_PICKUP_HEIGHT1, 1, 1);
	robot.joystick.register_button(DRIVE_PICKUP_HEIGHT2, 1, 2);
	robot.joystick.register_button(DRIVE_PICKUP_HEIGHT3, 1, 3);
	robot.joystick.register_button(DRIVE_PICKUP_HEIGHT4, 1, 4);
	robot.joystick.register_button(DRIVE_PICKUP_HEIGHT5, 1, 6);
	robot.joystick.register_combo(COMBO5, 0, 3);
	robot.joystick.register_axis(ROLLER_AXIS, 1, 3);

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

if (robot.joystick.button(DRIVE_REVERSE)){
	driveDirection *= -1;
}


//#if defined(USE_NAVX)
SmartDashboard::PutNumber( compass.n, robot.ahrs->GetCompassHeading());
//#endif
#ifdef SHOW_MOTORS
  SmartDashboard::PutNumber(std::string("back right motor current"), robot.motorMap[BACK_RIGHT]->GetOutputCurrent());
  SmartDashboard::PutNumber(std::string("front right motor current"), robot.motorMap[FRONT_RIGHT]->GetOutputCurrent());
  SmartDashboard::PutNumber(std::string("back left motor current"), robot.motorMap[BACK_LEFT]->GetOutputCurrent());
  SmartDashboard::PutNumber(std::string("front left motor current"), robot.motorMap[FRONT_LEFT]->GetOutputCurrent());
#endif
#ifdef SHOW_SENSORS
  SmartDashboard::PutNumber("Left Pot Raw", leftPot.GetVoltage());
  SmartDashboard::PutNumber("Right Pot Raw", rightPot.GetVoltage());
  SmartDashboard::PutNumber("Jumper", jumper.GetVoltage());

  SmartDashboard::PutNumber("Gyro Yaw",robot.ahrs->GetYaw());

  SmartDashboard::PutNumber(std::string("Left Pot Value"), leftPotValue());
  SmartDashboard::PutNumber(std::string("Right Pot Value"), rightPotValue());
#endif
	if (!robot.isHybrid){


  	SmartDashboard::PutNumber(leftPickupPos.n,leftPotValue());
  	SmartDashboard::PutNumber(rightPickupPos.n,rightPotValue());

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


  	rollerMotor.Set(DEADBAND(robot.joystick.axis(ROLLER_AXIS),.05));

	if ((drive_rot == 0) && (oldRot != 0.0)){
		resetQ = 12;
	}
	if (resetQ != 0){
		if (resetQ == 3){
#if defined(USE_NAVX)
		robot.ahrs->ZeroYaw();
//		std::cout << "WARNING: NavX Zeroed" << std::endl;
		gyroSet = robot.ahrs->GetYaw();
#endif
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
			if(oldGoalX!=goalX){
				oldGyroYaw = robot.ahrs->GetYaw();
				gyroIntegral = 0.0;

			}

			if (goalX == -1){
//				drive_rot = (oldGoalX == -1)?NORMAL_SPEED:0.0;
			}else if (std::fabs(goalX-VISION_WIDTH/2.0) > VISION_WIDTH/2.0){
				if (goalX>VISION_WIDTH/2.0){
					drive_rot = -NORMAL_SPEED;
				}else{
					drive_rot = NORMAL_SPEED;
				}
			}else{
				gyroSet  = oldGyroYaw+((goalX-(VISION_WIDTH/2.0))/(VISION_WIDTH/2.0))*(VISION_H_FOV/2.0);
				SmartDashboard::PutNumber("Gyro Set", gyroSet);
			}
			double gyroRate = robot.ahrs->GetYaw();
				//Gyro PID
				if((drive_rot==0.0 && resetQ == 0 && !SmartDashboard::GetBoolean("disableGyro",false))){
					double gyroError =  gyroSet - gyroRate;
//					double time = gyroITimer.Get();

					gyroIntegral += gyroError;
		//			SmartDashboard::PutNumber("Gyro PID Error", gyroPID.mistake);
					double gyroOutput = 0.0;
					if(fabs(gyroError)>2){
						gyroOutput = ((SmartDashboard::GetNumber( rotationPValue.n,  rotationPValue.v)*gyroError) + (SmartDashboard::GetNumber( rotationIValue.n,  rotationIValue.v)*gyroIntegral));
					}else{
						gyroOutput = ((SmartDashboard::GetNumber( rotationClosePValue.n,  rotationClosePValue.v)*gyroError) + (SmartDashboard::GetNumber( rotationCloseIValue.n,  rotationCloseIValue.v)*gyroIntegral));
					}
//					double gyroOutput = ((SmartDashboard::GetNumber( rotationPValue.n,  rotationPValue.v)*gyroError) + (SmartDashboard::GetNumber( rotationIValue.n,  rotationIValue.v)*gyroIntegral));
		//			SmartDashboard::PutNumber("Gyro PID Out before", gyroOutput);
					gyroOutput = gyroOutput > 1.0 ? 1.0 : (gyroOutput < -1.0 ? -1.0 : gyroOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
					drive_rot = gyroOutput;
				}


		}
	}
	oldBallX = ballX;
	oldGoalX = goalX;
	gyroITimer.Reset();


	///////////////////////////////////////
	///////// GYRO CALCULATIONS ///////////
	///////////////////////////////////////

			if (drive_rot < .05 && drive_rot > -.05){
				drive_rot = 0;
			}



	// AutoPickup //
//	double angleTollerance = 3;
//	if(autoPickupButton == true){
//		if(vision->angleError(LEFT))
//	}
			drive_mag*=driveDirection;
//			drive_rot*=driveDirection;

/////////////////////////////
/////   Motor Outputs   /////
/////////////////////////////
	double left;
	double right;
	double a = SmartDashboard::GetNumber( etherA.n,  etherA.v);
	double b = SmartDashboard::GetNumber( etherB.n,  etherB.v);
	if(!robot.joystick.button(DRIVE_LSPEED)){
		drive_mag *= .5;
	}

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
	if(DEADBAND(robot.joystick.axis(PICKUP_AXIS),.05) != 0){
//		double rightPickupError =  rightPotValue() - leftPotValue() ;
//		SmartDashboard::PutNumber("Right Pickup Error", rightPickupError);
//		double rightPickupOutput = (SmartDashboard::GetNumber(pickupPValue.n, pickupPValue.v)*rightPickupError);
//		rightPickupOutput = rightPickupOutput > 0.3 ? 0.3 : (rightPickupOutput < -0.3 ? -0.3 : rightPickupOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
//		if (rightPickupOutput < .05 && rightPickupOutput > -.05){
//			rightPickupOutput = 0;
//		}
//		SmartDashboard::PutNumber("Right Pickup Output", rightPickupOutput);
//
//		double leftPickupError =  leftPotValue() - rightPotValue() ;
//		SmartDashboard::PutNumber("Left Pickup Error", leftPickupError);
//		double leftPickupOutput = (SmartDashboard::GetNumber(pickupPValue.n, pickupPValue.v)*leftPickupError);
//		leftPickupOutput = leftPickupOutput > 0.3 ? 0.3 : (leftPickupOutput < -0.3 ? -0.3 : leftPickupOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
//		if (leftPickupOutput < .05 && leftPickupOutput > -.05){
//			leftPickupOutput = 0;
//		}
//		SmartDashboard::PutNumber("Left Pickup Output", leftPickupOutput);
		double pickupSet = (robot.joystick.axis(PICKUP_AXIS)*-.8);
//		pickupSet = (pickupSet<0 && rightPot.GetVoltage() < SmartDashboard::GetNumber(pickupHeight3.n,pickupHeight3.v))?pickupSet:0.0;
		leftPickupMotor.Set(pickupSet);
		rightPickupMotor.Set(pickupSet);
	}
	else if(robot.joystick.button(DRIVE_PICKUP_HEIGHT1))
		if(SmartDashboard::GetNumber(pickupHeight1L.n, pickupHeight1L.v) == -1)
			setPickupHeight(pickupHeight1);
		else
			setPickupHeight(pickupHeight1,pickupHeight1L);
	else if(robot.joystick.button(DRIVE_PICKUP_HEIGHT2)){
		rollerMotor.Set(1.0);
		if(SmartDashboard::GetNumber(pickupHeight2L.n, pickupHeight2L.v) == -1)
			setPickupHeight(pickupHeight2);
		else
			setPickupHeight(pickupHeight2,pickupHeight2L);
	}
	else if(robot.joystick.button(DRIVE_PICKUP_HEIGHT3)){
		double setP = SmartDashboard::GetNumber(otherPickupP.n,otherPickupP.v);
		SmartDashboard::PutNumber(otherPickupP.n, SmartDashboard::GetNumber(safePickupP.n,safePickupP.v));
		if(SmartDashboard::GetNumber(pickupHeight3L.n, pickupHeight3L.v) == -1)
			setPickupHeight(pickupHeight3);
		else
			setPickupHeight(pickupHeight3,pickupHeight3L);
		SmartDashboard::PutNumber(otherPickupP.n, setP);
	}
	else if(robot.joystick.button(DRIVE_PICKUP_HEIGHT4)){
		if(SmartDashboard::GetNumber(pickupHeight4L.n, pickupHeight4L.v) == -1)
			setPickupHeight(pickupHeight4);
		else
			setPickupHeight(pickupHeight4,pickupHeight4L);
		rollerMotor.Set(-.5);
	}
	else if(robot.joystick.button(DRIVE_PICKUP_HEIGHT5))
		if(SmartDashboard::GetNumber(pickupHeight5L.n, pickupHeight5L.v) == -1)
			setPickupHeight(pickupHeight5);
		else
			setPickupHeight(pickupHeight5,pickupHeight5L);
	else{
		setPickupHeight(rightPotValue());
	}



}

void DrivePickupSubsystem::teleopEnd(void){
	robot.outLog.appendLog("drive tele end");
	frontLeft.SetSafetyEnabled(false);
	frontRight.SetSafetyEnabled(false);
	backLeft.SetSafetyEnabled(false);
	backRight.SetSafetyEnabled(false);
	rightPickupMotor.SetSafetyEnabled(false);
	leftPickupMotor.SetSafetyEnabled(false);
	rollerMotor.SetSafetyEnabled(false);
	frontLeft.Set(0.0);
	frontRight.Set(0.0);
	backLeft.Set(0.0);
	backRight.Set(0.0);
	drive_rot = 0.0;
	drive_mag = 0.0;
}

void DrivePickupSubsystem::bolderAlign(double lError, double rError, double distAway){

	//need's to be written!!

}

void DrivePickupSubsystem::setPickupSpeed(double speed){
//	pickupMotor.Set(speed);
}
