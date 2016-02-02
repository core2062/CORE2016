/*
 * TeleSubsystem.h
 *
 *  Created on: Feb 1, 2016
 *      Author: core2062
 */

#ifndef SRC_TELESUBSYSTEM_H_
#define SRC_TELESUBSYSTEM_H_

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





public:





	std::string name(void);
	TeleSubsystem(CORERobot& robot):
		CORESubsystem(robot)

		{
		}

	void robotInit(void);
	void teleopInit(void);
	void teleop(void);
	void teleopEnd(void);

};




#endif /* SRC_TELESUBSYSTEM_H_ */
