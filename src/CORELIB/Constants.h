/*
 * Constants.h
 *
 *  Created on: Aug 25, 2015
 *      Author: core
 */


#ifndef SRC_CORELIB_CONSTANTS_H_
#define SRC_CORELIB_CONSTANTS_H_

#define USE_NAVX
#define SHOW_MOTORS
#define ETHER_DIRVE
#define SHOW_SENSORS
//#define TANK_DRIVE
//#define MECANUM_DRIVE
#define ULTIMATE_MODE

#include <string>
#include <array>

enum motors{
	LIFT_MOTOR,
	BACK_RIGHT,
	BACK_LEFT,
	FRONT_RIGHT,
	FRONT_LEFT,
	LEFT_PICKUP,
	RIGHT_PICKUP,
	ROLLER
};

enum direction{
	IN,
	OUT

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
	DRIVE_GOAL,
	DRIVE_AUTO_PICKUP,
	DRIVE_PICKUP_HEIGHT1,
	DRIVE_PICKUP_HEIGHT2,
	DRIVE_PICKUP_HEIGHT3,
	DRIVE_PICKUP_HEIGHT4,
	DRIVE_PICKUP_HEIGHT5,
	LIFT_LEVEL1,
	LIFT_LEVEL2,
	SHOOTER_FIRE,
	PICKUP_AXIS,
	ROLLER_UP,
	ROLLER_DOWN,

	HYBRID_GOTO_SDXY,


	COMBO1,
	COMBO2,
	COMBO3,
	COMBO4,
	COMBO5
};

enum digitalSensors{
	BOT_LIFT_LIMIT,
	TOP_LIFT_LIMIT,
	PICKUP_UPPER_RIGHT_LIMIT,
	PICKUP_LOWER_RIGHT_LIMIT,
	PICKUP_UPPER_LEFT_LIMIT,
	PICKUP_LOWER_LEFT_LIMIT
};

enum analogSensors{
	GYRO,
	ACCELEROMETER,
	FR_ENCODER,
	FL_ENCODER,
	BR_ENCODER,
	BL_ENCODER,
	LEFT_POT,
	RIGHT_POT
};

enum pneumatics{
	SHOOTER_LEFT_CYLINDER,
	SHOOTER_RIGHT_CYLINDER
};

const double PI = 3.1415923565;


//  Motor Speed Values //
const double FORWARD = .99;
const double OFF = 0;
const double REVERSE =-.99;
const double NORMAL_SPEED = .5;
const double HALF_SPEED_REVERSE =-.5;
const double PICKUP_SPEED = .85;


const double WHEEL_DIA = 7.95;
const double ENCODER_CONST = 1.0/4.0;
const double ENCODER_RES = 1024;

//	Vision Things	//
const int VISION_WIDTH = 960;
const int VISION_HEIGHT = 544;
const int VISION_BALL_DISP = 200;
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
 const smartDB etherB(std::string("Ether B"), 0.25);
 const smartDB blueTowerCompass(std::string("Blue Tower Compass"), 0.0);
 const smartDB compass(std::string("NavX Compass"), 0.0);
 const smartDB shooterReturn(std::string("Shooter Return Time"), .5);
 const smartDB quickTurn(std::string("Quick Turn Speed"), .5);

 const smartDB testAuto(std::string("Auto Test Value"), 5.0);
 const smartDB mediumDistance(std::string("Medium Distance"), 5.0);
 const smartDB secondaryMedium(std::string("Secondary Medium Distance"), 5.0);
 const smartDB longDistance(std::string("Long Distance"), 5.0);
 const smartDB secondaryLong(std::string("Secondary Long Distance"), 5.0);
 const smartDB pickupHeight1(std::string("Pickup Height 1"), 0.0);
 const smartDB pickupHeight2(std::string("Pickup Height 2"), 12.0);
 const smartDB pickupHeight3(std::string("Pickup Height 3"), 24.0);
 const smartDB pickupHeight4(std::string("Pickup Height 4"), 36.0);
 const smartDB pickupHeight5(std::string("Pickup Height 5"), 48.0);
 const smartDB leftPickupPos(std::string("Left Pickup Position"), 0.0);
 const smartDB rightPickupPos(std::string("Right Pickup Position"), 0.0);
 const smartDB pickupP(std::string("Pickup P"), 0.0);
 const smartDB liftLevel1(std::string("Lift Level 1"), 0.0);
 const smartDB liftLevel2(std::string("Lift Level 2"), 12.0);
 const smartDB pickupPValue(std::string("Pickup P Mainly"), 0.0);
 const smartDB otherPickupP(std::string("Pickup P Sub loop"), 0.0);
 const smartDB pickupVoltThresh(std::string("Pickup Voltage Threshold"), 0.0);


 const std::vector<const smartDB *> sdPointers = {
		 &rotationPValue,
		 &etherA,
		 &etherB,
		 &blueTowerCompass,
		 &compass,
		 &testAuto,
		 &shooterReturn,
		 &quickTurn,
		 &mediumDistance,
		 &secondaryMedium,
		 &longDistance,
		 &secondaryLong,
		 &pickupHeight1,
		 &pickupHeight2,
		 &pickupHeight3,
		 &pickupHeight4,
		 &pickupHeight5,
		 &leftPickupPos,
		 &rightPickupPos,
		 &liftLevel1,
		 &liftLevel2,
		 &pickupPValue,
		 &otherPickupP,
		 &pickupVoltThresh
 };






#endif /* SRC_CONSTANTS_H_ */
