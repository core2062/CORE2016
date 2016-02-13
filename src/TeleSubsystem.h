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

using namespace CORE;


class TeleSubsystem: public CORESubsystem{

	double currentX = 0.0;
	double currentY = 0.0;

	double setX = 0.0;
	double setY = 0.0;

	double oldGyro = 0.0;

	AutoControl& seq;


public:





	std::string name(void){
		return "TeleSubsystem";
	}
	TeleSubsystem(CORERobot& robot, AutoControl& sequen):
		CORESubsystem(robot),
		seq(sequen)

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
			return (robot.ahrs->GetCompassHeading());
		}else{
			return (robot.ahrs->GetCompassHeading());
		}

#else
		return -1;
#endif


	}
};






#endif /* TELESUBSYSTEM_H_ */
