/*
 * Constants.h
 *
 *  Created on: Aug 25, 2015
 *      Author: core
 */


#ifndef SRC_CORELIB_CONSTANTS_H_
#define SRC_CORELIB_CONSTANTS_H_

#define USE_NAVX

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
	DRIVE_ROT,
	DRIVE_SPEED,
	DRIVE_GOAL,
	DRIVE_AUTO_PICKUP,
	DRIVE_PICKUP_IN,
	DRIVE_PICKUP_OUT,
	LIFT_LEVEL1,
	LIFT_LEVEL2,
	SHOOTER_FIRE,
	COMBO1,
	COMBO2,
	COMBO3,
	COMBO4,
	COMBO5
};

enum digitalSensors{
	BOT_LIFT_LIMIT,
	TOP_LIFT_LIMIT
};

enum analogSensors{
	GYRO,
	ACCELEROMETER,
	FR_ENCODER,
	FL_ENCODER,
	BR_ENCODER,
	BL_ENCODER
};

enum pneumatics{
	SHOOTER_LEFT_CYLINDER,
	SHOOTER_RIGHT_CYLINDER
};




//  Motor Speed Values //
const double FORWARD = .99;
const double OFF = 0;
const double REVERSE =-.99;
const double NORMAL_SPEED = .5;
const double HALF_SPEED_REVERSE =-.5;
const double PICKUP_SPEED = .85;

//	Vision Things	//
const int VISION_WIDTH = 640;
const int VISION_HEIGHT = 480;
const int VISION_BALL_DISP = 200;




/* SMART DASHBOARD CONSTANTS */
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

class smartDBValues{


public:

	 smartDB rotationPValue;
	 smartDB etherA;
	 smartDB etherB;
	 smartDB blueTowerCompass;
	 smartDB compass;


	 smartDBValues():
	 rotationPValue(std::string("Rotation P"), .05),
	 etherA(std::string("Ether A"), 1.0),
	 etherB(std::string("Ether B"), 0.0),
	 blueTowerCompass(std::string("Blue Tower Compass"), 0.0),
	 compass(std::string("NavX Compass"), 0.0)
	 {
	 }
};



#endif /* SRC_CONSTANTS_H_ */
