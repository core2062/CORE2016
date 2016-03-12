/*
 * Constants.h
 *
 *  Created on: Aug 25, 2015
 *      Author: core
 */


#ifndef SRC_CORELIB_CONSTANTS_H_
#define SRC_CORELIB_CONSTANTS_H_

#define USE_NAVX
//#define SHOW_MOTORS
#define ETHER_DIRVE
#define SHOW_SENSORS
//#define TANK_DRIVE
//#define MECANUM_DRIVE
//#define ULTIMATE_MODE

#define PI 3.1415923565
#define RADIANS(d) ((d*PI)/180.0)
#define DEGREES(r) ((r*180.0)/PI)
#define DEADBAND(v,a) ((v<a && v>-a)?0:v)

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
	DRIVE_MAG_SPEED,
	DRIVE_ROT_SPEED,
	DRIVE_GOAL,
	DRIVE_REVERSE,
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
	ROLLER_AXIS,

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

 const smartDB rotationPValue(std::string("Rotation P"), 0.15);
 const smartDB rotationIValue(std::string("Rotation I"), 0.025);
 const smartDB rotationClosePValue(std::string("Rotation Close P"), 0.25);
 const smartDB rotationCloseIValue(std::string("Rotation Close I"), 0.1);
 const smartDB etherA(std::string("Ether A"), 1.0);
 const smartDB etherB(std::string("Ether B"), 0.5);
 const smartDB blueTowerCompass(std::string("Blue Tower Compass"), 0.0);
 const smartDB compass(std::string("NavX Compass"), 0.0);
 const smartDB shooterReturn(std::string("Shooter Return Time"), .5);
 const smartDB quickTurn(std::string("Quick Turn Speed"), .75);

 const smartDB testTargetX(std::string("Coordinate Target X"), 0.0);
 const smartDB testTargetY(std::string("Coordinate Target Y"), 0.0);
 const smartDB testTargetAngle(std::string("Coordinate Target Angle"), 0.0);



 const smartDB testAuto(std::string("Auto Test Value"), 5.0);
 const smartDB mediumDistance(std::string("Medium Distance"), 5.0);
 const smartDB secondaryMedium(std::string("Secondary Medium Distance"), 5.0);
 const smartDB longDistance(std::string("Long Distance"), 5.0);
 const smartDB secondaryLong(std::string("Secondary Long Distance"), 5.0);
 const smartDB pickupHeight1(std::string("Pickup Height 1"), 2.25);
 const smartDB pickupHeight2(std::string("Pickup Height 2"), .75);
 const smartDB pickupHeight3(std::string("Pickup Height 3"), 3.43);
 const smartDB pickupHeight4(std::string("Pickup Height 4"), 2.5);
 const smartDB pickupHeight5(std::string("Pickup Height 5"), 2.5);
 const smartDB pickupHeight1L(std::string("Pickup Height 1L"), -1.0);
 const smartDB pickupHeight2L(std::string("Pickup Height 2L"), -1.0);
 const smartDB pickupHeight3L(std::string("Pickup Height 3L"), -1.0);
 const smartDB pickupHeight4L(std::string("Pickup Height 4L"), -1.0);
 const smartDB pickupHeight5L(std::string("Pickup Height 5L"), -1.0);
 const smartDB leftPickupPos(std::string("Left Pickup Position"), 0.0);
 const smartDB rightPickupPos(std::string("Right Pickup Position"), 0.0);
 const smartDB liftLevel1(std::string("Lift Level 1"), 0.0);
 const smartDB liftLevel2(std::string("Lift Level 2"), 12.0);
 const smartDB pickupPValue(std::string("Pickup P Correction"), 0.0);
 const smartDB otherPickupP(std::string("Pickup P Main Control"), -2.0);
 const smartDB safePickupP(std::string("Safe Pickup P"), -1.0);
 const smartDB pickupCurrentThresh(std::string("Pickup Current Threshold"), 0.0);
 const smartDB pickupShootClearance(std::string("Pickup Safe Min"), 0.0);

 const smartDB magneticPotMax(std::string("Pot Max"), 5.0);
 const smartDB leftMagPotBase(std::string("Left Pot Base"), 0.0);
 const smartDB rightMagPotBase(std::string("Right Pot Base"), 0.0);



 const std::vector<const smartDB *> sdPointers = {
		 &rotationPValue,
		 &rotationIValue,
		 &rotationClosePValue,
		 &rotationCloseIValue,
		 &etherA,
		 &etherB,
		 &blueTowerCompass,
		 &compass,
		 &testAuto,
		 &shooterReturn,
		 &quickTurn,

		 &testTargetX,
		 &testTargetY,
		 &testTargetAngle,

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
		 &safePickupP,
		 &pickupCurrentThresh,
		 &magneticPotMax,
		 &leftMagPotBase,
		 &rightMagPotBase
 };






#endif /* SRC_CONSTANTS_H_ */
