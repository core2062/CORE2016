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
	LIFT_MOTOR,
	BACK_RIGHT,
	BACK_LEFT,
	FRONT_RIGHT,
	FRONT_LEFT,
	PICKUP
};

enum liftHeights {
	LEVEL1 = 0,
	LEVEL2 = 12
};
enum side {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum controllerInputs{
	LIFT_AXIS,
	DRIVE_MAG,
	DRIVE_MAG2,
	DRIVE_ROT,
	DRIVE_SPEED,
	LIFT_LEVEL1,
	LIFT_LEVEL2,
	AUTO_PICKUP,
	SHOOTER_FIRE
};

enum digitalSensors{
	BOT_LIFT_LIMIT,
	TOP_LIFT_LIMIT
};

enum analogSensors{

};

//  Motor Speed Values //
const double FORWARD = .99;
const double OFF = 0;
const double REVERSE =-.99;
const double NORMAL_SPEED = .5;
const double HALF_SPEED_REVERSE =-.5;


enum pneumatics{
	LEFT_SOLINOID,
	RIGHT_SOLINOID
};



/* SMART DASHBOARD CONSTANTS */
const std::string TESTVALUE = "Test_Value";

const std::tuple<std::string,double> test1("hey",5.3);

 class smartDB{
public:
	std::string n;
	double v = 0.0;
	bool b = true;

	smartDB(std::string name, double base){
		n = name;
		v = base;
		SmartDashboard::PutNumber(name, base);
	}
	smartDB(std::string name, double base, bool put){
		n = name;
		v = base;
		if (put){
			SmartDashboard::PutNumber(name, base);
		}
	}
	smartDB(std::string name, bool base){
		n = name;
		b = base;
		SmartDashboard::PutBoolean(name, base);
	}
	smartDB(std::string name, bool base, bool put){
		n = name;
		b = base;
		if (put){
			SmartDashboard::PutBoolean(name, base);
		}
	}


};






#endif /* SRC_CONSTANTS_H_ */
