#ifndef CORESUBSYSTEM_H
#define CORESUBSYSTEM_H

#include <string>
#include "WPILib.h"
#include <vector>
#include <map>
#include "CORELIB.h"




namespace CORE {

class CORESubsystem;

class CORERobot {
	std::vector<CORESubsystem*> subsystems;


public:

	std::map<motors,CANSpeedController*> motorMap;
	std::map<digitalSensors,DigitalInput*> digitalSensorMap;
	std::map<analogSensors,AnalogInput*> analogSensorMap;
	std::map<pneumatics, DoubleSolenoid*> pneumaticMap;


	JoystickCache joystick;
	Log outLog;
	Timer loopTimer;
	bool loopStarted = false;
	bool isHybrid = false;
//	COREDash CD;
//	AutoControl autoControl;

	CORERobot():
		subsystems(),
		joystick(),
		outLog()//,
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
