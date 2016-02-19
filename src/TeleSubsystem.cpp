/*
 * TeleSubsystem.cpp
 *
 *  Created on: Feb 12, 2016
 *      Author: Joshua
 */
#include "TeleSubsystem.h"


	void TeleSubsystem::robotInit(void){
		robot.outLog.appendLog("TeleAuto Robot Init");
	}
	void TeleSubsystem::teleopInit(void){
		robot.outLog.appendLog("TeleSubsystem: TeleopInit Success");
		robot.joystick.register_combo(HYBRID_GOTO_SDXY, 2, 7);
		oldCompass = getHeading();

	}
	void TeleSubsystem::teleop(){
#if !defined(USE_NAVX)
robot.outLog.appendLog("[ERROR] NAVX NOT DEFINED!! (some things may not work as intended)");
#endif
#if defined(SHOW_MOTORS) // cuz for some reason && / || dont work
#if defined(SHOW_SENSORS)
robot.outLog.appendLog("[NOTE] Showing motor / sensor values on SmartDB");
#endif
#else
robot.outLog.appendLog("[NOTE] Not Showing motor / sensor values on SmartDB");
#endif
//		double leftEnc = robot.motorMap[FRONT_LEFT]->GetEncPosition();
//		double rightEnc = robot.motorMap[FRONT_RIGHT]->GetEncPosition();
		double leftEnc = 0.0;
		double rightEnc = 0.0;
		double compassVal = getHeading();

		if (!robot.isHybrid){
			if (drive.drive_rot == 0.0 && drive.drive_mag !=0){
				double averageCompass = (compassVal+oldCompass)/2.0;
				double deltaDist = ((leftEnc-oldLeftEnc)+(rightEnc-oldRightEnc))/2.0;
				currentY+=cos(RADIANS(averageCompass))*(deltaDist);
				currentX+=sin(RADIANS(averageCompass))*(deltaDist);



			}
		}


		if (!robot.isHybrid && robot.joystick.combo(HYBRID_GOTO_SDXY)){
			robot.isHybrid = true;
			seq.reset();
			seq.add(new CoordinateAction (robot,currentX,currentY,
								SmartDashboard::GetNumber(testTargetX.n,testTargetY.v),
								SmartDashboard::GetNumber(testTargetY.n,testTargetY.v),
								SmartDashboard::GetNumber(testTargetAngle.n,testTargetAngle.v)));
			seq.init();



		}


		oldLeftEnc = leftEnc;
		oldRightEnc = rightEnc;
		oldCompass = compassVal;

	}




