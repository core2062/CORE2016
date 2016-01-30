#ifndef CORESUBSYSTEM_H
#define CORESUBSYSTEM_H

#include <string>
#include "WPILib.h"
#include <vector>
#include <map>
#include "CORELIB.h"
#include <array>

#if defined(USE_NAVX)
//NavX stuff
#include <navx2.0/AHRS.h>
#endif

/* NOTE:  Comment in only ONE of the following definitions. */

//#define ENABLE_IMU
//#define ENABLE_IMU_ADVANCED
#define ENABLE_AHRS





namespace CORE {

class Action;
class OrderAction/* : public Action*/;
class ConditionAction/* : public Action*/;
class AutoControl;

class CORESubsystem;

class CORERobot {
	std::vector<CORESubsystem*> subsystems;
    SerialPort *serial_port;


public:


	std::map<motors,CANSpeedController*> motorMap;
	std::map<digitalSensors,DigitalInput*> digitalSensorMap;
	std::map<analogSensors,AnalogInput*> analogSensorMap;
	std::map<pneumatics, DoubleSolenoid*> pneumaticMap;

	AutoControl * autoSeq;
	AutoControl * teleSeq;

	std::queue<OrderAction*> aQueue;
	std::vector<Action*> aBackground;

	std::queue<OrderAction*> tQueue;
	std::vector<Action*> tBackground;

#if defined(USE_NAVX)
#if defined(ENABLE_AHRS)
        AHRS *ahrs;
#elif defined(ENABLE_IMU_ADVANCED)
        IMUAdvanced *ahrs;
#elif defined(ENABLE_IMU) // ENABLE_IMU
        IMU *ahrs;
#endif
#endif

	JoystickCache joystick;
	Log outLog;
	Timer loopTimer;
	bool loopStarted = false;
	bool isHybrid = false;
//	COREDash CD;
//	AutoControl autoControl;

	CORERobot():
		subsystems(),
		serial_port(),
		joystick(),
		outLog()
//		autoControl()
//		CD(outLog)
	{}

	void add(CORESubsystem& subsystem);

	std::vector<CORESubsystem*>& getSubsystems(void);

	void robotInit(void);
	void teleopInit(void);
	void teleop(void);
	void teleopEnd(void);
	void link(motors motorKey,CANSpeedController* motor);
	void link(digitalSensors digitalSensorKey ,DigitalInput* sensor);
	void link(analogSensors analogSensorKey ,AnalogInput* sensor);
	void link(pneumatics pneumaticKey , DoubleSolenoid* cylinder);
/*
	void addA (OrderAction& a){
		aQueue.push(&a);
	}
	void addA (OrderAction* a){
		aQueue.push(a);
	}
	void addA (ConditionAction& a){
		aBackground.push_back(&a);
	}
	void addA (ConditionAction* a){
		aBackground.push_back(a);
	}
	void addT (OrderAction& a){
		tQueue.push(&a);
	}
	void addT (OrderAction* a){
		tQueue.push(a);
	}
	void addT (ConditionAction& a){
		tBackground.push_back(&a);
	}
	void addT (ConditionAction* a){
		tBackground.push_back(a);
	}
*/



	double getLoopWait();

	~CORERobot(){
	}


};

class CORESubsystem{
	public:
	virtual std::string name(void) = 0;
	CORERobot& robot;
	CORESubsystem(CORERobot& robot):
	robot(robot)
	{}


	virtual ~CORESubsystem(){};	// Suppresses GNU GCC warning. Can be removed under GCC version 4.3

	// Called before loop at start of Teleop period
	virtual void robotInit(void) = 0;

	virtual void teleopInit(void) = 0;

	//Called sequentially during loop, interleaved with other subsystems
	virtual void teleop(void) = 0;
	virtual void teleopEnd(void){
		//nothing
	}
};

}
#endif
