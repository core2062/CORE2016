/*
 * Coordinate.h
 *
 *  Created on: Feb 16, 2016
 *      Author: Joshua
 */

#ifndef SRC_ACTIONS_COORDINATEACTION_H_
#define SRC_ACTIONS_COORDINATEACTION_H_

#include "CoreLib/COREAuto.h"
//#include "TeleSubsystem.h"

using namespace CORE;

class CoordinateAction : public OrderAction{

//	TeleSubsystem & tele;
	double targetX = 0.0;
	double targetY = 0.0;
	double targetAngle = 0.0;

	double oldLeftEnc = 0.0;
	double oldRightEnc = 0.0;
	double oldCompass = 0.0;

	bool beenThere = false;

	int direction = 1;

	double & currentX;
	double & currentY;

public:

	virtual bool backgroundCondition(){
		return false;
	}
	virtual bool endCondition(){
		return false;
	}
	CoordinateAction(CORERobot& robot, double & cX, double cY, double x, double y, double angle):
		OrderAction(robot),

		targetX(x),
		targetY(y),
		targetAngle(angle),
		currentX(cX),
		currentY(cY)
	{
	};

	void init(){
		double compassVal = getHeading();

		double tempAngle = 0.0;
		if (currentX >= targetX){
			if (currentY >= targetY){
				tempAngle = DEGREES(atan(fabs((targetY-currentY)/(targetX/currentX)))) + 270;
			}else{
				tempAngle = DEGREES(atan(-fabs((targetX-currentX)/(targetY-currentY)))) + 360;
			}
		}else{
			if (currentY >= targetY){
				tempAngle = DEGREES(atan(fabs((targetY-currentY)/(targetX/currentX)))) + 90;
			}else{
				tempAngle = DEGREES(atan(fabs((targetX-currentX)/(targetY-currentY))));
			}
		}
		double aTempError = (fabs(compassVal - tempAngle) <= fabs(compassVal>180?compassVal-360:compassVal - tempAngle>180?tempAngle-360:tempAngle))?(compassVal - tempAngle):(compassVal>180?compassVal-360:compassVal - tempAngle>180?tempAngle-360:tempAngle);
		double aFinalError = (fabs(tempAngle - targetAngle) <= fabs(tempAngle>180?tempAngle-360:tempAngle - targetAngle>180?targetAngle-360:targetAngle))?(tempAngle - targetAngle):(tempAngle>180?tempAngle-360:tempAngle - targetAngle>180?targetAngle-360:targetAngle);
		double aTotalError = aTempError + aFinalError;

		tempAngle = (tempAngle+180>360?tempAngle-180:tempAngle+180);

		double bTempError = (fabs(compassVal - tempAngle) <= fabs(compassVal>180?compassVal-360:compassVal - tempAngle>180?tempAngle-360:tempAngle))?(compassVal - tempAngle):(compassVal>180?compassVal-360:compassVal - tempAngle>180?tempAngle-360:tempAngle);
		double bFinalError = (fabs(tempAngle - targetAngle) <= fabs(tempAngle>180?tempAngle-360:tempAngle - targetAngle>180?targetAngle-360:targetAngle))?(tempAngle - targetAngle):(tempAngle>180?tempAngle-360:tempAngle - targetAngle>180?targetAngle-360:targetAngle);
		double bTotalError = bTempError + bFinalError;

		if (bTotalError < aTotalError){
			direction = -1;
		}
	}
	void end(){}
	ControlFlow autoCall(){
		double leftEnc = robot.motorMap[FRONT_LEFT]->GetEncPosition();
		double rightEnc = robot.motorMap[FRONT_RIGHT]->GetEncPosition();
		double compassVal = getHeading();

		if(beenThere){
			double gyroError =  (fabs(compassVal - targetAngle) <= fabs(compassVal>180?compassVal-360:compassVal - targetAngle>180?targetAngle-360:targetAngle))?(compassVal - targetAngle):(compassVal>180?compassVal-360:compassVal - targetAngle>180?targetAngle-360:targetAngle);
//			SmartDashboard::PutNumber("Gyro PID Error", gyroPID.mistake);
			double gyroOutput = (SmartDashboard::GetNumber(rotationPValue.n, rotationPValue.v)*gyroError);
//			SmartDashboard::PutNumber("Gyro PID Out before", gyroOutput);
			gyroOutput = gyroOutput > 1.0 ? 1.0 : (gyroOutput < -1.0 ? -1.0 : gyroOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
			double drive_rot = gyroOutput;
			if (drive_rot < .05 && drive_rot > -.05){
				drive_rot = 0;
			}

			double left = drive_rot;
			double right = -drive_rot;

			robot.motorMap[BACK_RIGHT]->Set(right);
			robot.motorMap[FRONT_RIGHT]->Set(right);
			robot.motorMap[FRONT_LEFT]->Set(left);
			robot.motorMap[BACK_LEFT]->Set(left);
			if (drive_rot ==0){
				return END;
			}
		}else{
			double tempAngle = 0.0;
			if (currentX >= targetX){
				if (currentY >= targetY){
					tempAngle = DEGREES(atan(fabs((targetY-currentY)/(targetX/currentX)))) + 270;
				}else{
					tempAngle = DEGREES(atan(-fabs((targetX-currentX)/(targetY-currentY)))) + 360;
				}
			}else{
				if (currentY >= targetY){
					tempAngle = DEGREES(atan(fabs((targetY-currentY)/(targetX/currentX)))) + 90;
				}else{
					tempAngle = DEGREES(atan(fabs((targetX-currentX)/(targetY-currentY))));
				}
			}
			if (direction == -1){
				tempAngle = (tempAngle+180>360?tempAngle-180:tempAngle+180);
			}
//			double errorA = (compassVal - tempAngle);
//			double errorB = (compassVal>180?compassVal-360:compassVal - tempAngle>180?tempAngle-360:tempAngle);


			double gyroError = (fabs(compassVal - tempAngle) <= fabs(compassVal>180?compassVal-360:compassVal - tempAngle>180?tempAngle-360:tempAngle))?(compassVal - tempAngle):(compassVal>180?compassVal-360:compassVal - tempAngle>180?tempAngle-360:tempAngle);
//			SmartDashboard::PutNumber("Gyro PID Error", gyroPID.mistake);
			double gyroOutput = (SmartDashboard::GetNumber(rotationPValue.n, rotationPValue.v)*gyroError);
//			SmartDashboard::PutNumber("Gyro PID Out before", gyroOutput);
			gyroOutput = gyroOutput > 1.0 ? 1.0 : (gyroOutput < -1.0 ? -1.0 : gyroOutput); //Conditional (Tenerary) Operator limiting values to between 1 and -1
			double drive_rot = gyroOutput;
			if (drive_rot < .05 && drive_rot > -.05){
				drive_rot = 0;
			}

			double left = drive_rot;
			double right = -drive_rot;

			robot.motorMap[BACK_RIGHT]->Set(right);
			robot.motorMap[FRONT_RIGHT]->Set(right);
			robot.motorMap[FRONT_LEFT]->Set(left);
			robot.motorMap[BACK_LEFT]->Set(left);
			if (drive_rot == 0){
				if (sqrt(pow(currentX-targetX,2)+pow(currentY-targetY,2))>3){
					robot.motorMap[BACK_RIGHT]->Set(NORMAL_SPEED * direction);
					robot.motorMap[FRONT_RIGHT]->Set(NORMAL_SPEED * direction);
					robot.motorMap[FRONT_LEFT]->Set(NORMAL_SPEED * direction);
					robot.motorMap[BACK_LEFT]->Set(NORMAL_SPEED * direction);
				}else{
					robot.motorMap[BACK_RIGHT]->Set(0);
					robot.motorMap[FRONT_RIGHT]->Set(0);
					robot.motorMap[FRONT_LEFT]->Set(0);
					robot.motorMap[BACK_LEFT]->Set(0);
					beenThere = true;
				}
			}
		}




		double averageCompass = (compassVal+oldCompass)/2.0;
		double deltaDist = ((leftEnc-oldLeftEnc)+(rightEnc-oldRightEnc))/2.0;
		currentY+=cos(averageCompass)*(deltaDist);
		currentX+=sin(averageCompass)*(deltaDist);







		oldLeftEnc = leftEnc;
		oldRightEnc = rightEnc;
		oldCompass = compassVal;
		return CONTINUE;
	}

	~CoordinateAction(){}

	double getHeading(){

	#if defined(USE_NAVX)
			DriverStation::Alliance color;
			color = DriverStation::GetInstance().GetAlliance();
			if(color == DriverStation::Alliance::kBlue){
				double total = (robot.ahrs->GetCompassHeading()+SmartDashboard::GetNumber(blueTowerCompass.n,blueTowerCompass.v));
				return total>=360?total-360:total;
			}else{
				double total = (robot.ahrs->GetCompassHeading()+SmartDashboard::GetNumber(blueTowerCompass.n,blueTowerCompass.v) + 180);
				return total>=360?(total-360>=360?total-720:total-360):total;
			}

	#else
			return -1;
	#endif


		}

};



#endif /* SRC_ACTIONS_COORDINATEACTION_H_ */
