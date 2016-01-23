/*
 * Constants.h
 *
 *  Created on: Aug 25, 2015
 *      Author: core
 */


#ifndef SRC_CORELIB_CONSTANTS_H_
#define SRC_CORELIB_CONSTANTS_H_

#include <string>

enum motors{
	LIFT_MOTOR
};

enum liftHeights {
		LEVEL1 = 0,
		LEVEL2 = 12
};

enum controllerInputs{
	LIFT_AXIS,
	DRIVE_Y,
	DRIVE_X,
	DRIVE_ROT,
	DRIVE_SPEED,
	LIFT_LEVEL1,
	LIFT_LEVEL2,
	AUTO_PICKUP
};

enum digitalSensors{
	BOT_LIFT_LIMIT,
	TOP_LIFT_LIMIT
};

enum analogSensors{

};


/* SMART DASHBOARD CONSTANTS */
const std::string TESTVALUE = "Test_Value";


#endif /* SRC_CONSTANTS_H_ */
