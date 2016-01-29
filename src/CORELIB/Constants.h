/*
 * Constants.h
 *
 *  Created on: Aug 25, 2015
 *      Author: core
 */


#ifndef SRC_CORELIB_CONSTANTS_H_
#define SRC_CORELIB_CONSTANTS_H_

#include <string>
#include <array>

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
const int VISION_BALL_TARGET = VISION_WIDTH/2.0;
const int VISION_H_FOV = 58.0;
const double VISION_FAST = NORMAL_SPEED;
const double VISION_SLOW = NORMAL_SPEED / 2.5;



/* SMART DASHBOARD CONSTANTS */
 class smartDB{
public:
	std::string n;
	double v = 0.0;
	bool b = true;
	bool isBool;

	smartDB(std::string name, double base){
		n = name;
		v = base;
		isBool = false;
	}
	smartDB(std::string name, bool base){
		n = name;
		b = base;
		isBool = true;
	}
	void put(){
		if (isBool)
			SmartDashboard::PutBoolean(n,v);
		else
			SmartDashboard::PutNumber(n,b);
	}


};


/*
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
*/

 const smartDB rotationPValue(std::string("Rotation P"), .05);
 const smartDB etherA(std::string("Ether A"), 1.0);
 const smartDB etherB(std::string("Ether B"), 0.0);
 const smartDB blueTowerCompass(std::string("Blue Tower Compass"), 0.0);
 const smartDB compass(std::string("NavX Compass"), 0.0);

 const std::array<const smartDB *,5> sdPointers = {
		 &rotationPValue,
		 &etherA,
		 &etherB,
		 &blueTowerCompass,
		 &compass
 };






#endif /* SRC_CONSTANTS_H_ */
