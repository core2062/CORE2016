/*
 * TeleSubsystem.h
 *
 *  Created on: Feb 12, 2016
 *      Author: Joshua
 */

#ifndef TELESUBSYSTEM_H_
#define TELESUBSYSTEM_H_

#include "CORELIB/CORERobot.h"
#include "WPILib.h"
#include <cmath>
#include <iostream>
#include <math.h>
#include "CORELIB/COREAuto.h"
#include "Actions/Actions.h"
#include "DrivePickupSubsystem.h"

using namespace CORE;


class TeleSubsystem: public CORESubsystem{



	double setX = 0.0;
	double setY = 0.0;

	double oldCompass = 0.0;

	double oldLeftEnc = 0.0;
	double oldRightEnc = 0.0;

	AutoControl& seq;
	DrivePickupSubsystem& drive;

public:

	double currentX = 0.0;
	double currentY = 0.0;



	std::string name(void){
		return "TeleSubsystem";
	}
	TeleSubsystem(CORERobot& robot, AutoControl& sequen, DrivePickupSubsystem& driv):
		CORESubsystem(robot),
		seq(sequen),
		drive(driv)

		{
		}

	void robotInit(void);
	void teleopInit(void);
	void teleop(void);
	void teleopEnd(void){

	}
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






#endif /* TELESUBSYSTEM_H_ */
