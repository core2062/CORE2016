#include "CORERobot.h"

using namespace CORE;


void CORERobot::add(CORESubsystem& subsystem){
	subsystems.push_back(&subsystem);
}

std::vector<CORESubsystem*>& CORERobot::getSubsystems(void){
	return subsystems;
}

void CORERobot::robotInit(void){
	outLog.appendLog("---------Robot Init---------");
	for (uint16_t i = 0; i < sdPointers.size(); i++){
		if (sdPointers[i]->isBool)
			SmartDashboard::PutBoolean(sdPointers[i]->n,sdPointers[i]->b);
		else
			SmartDashboard::PutNumber(sdPointers[i]->n,sdPointers[i]->v);
	}
	std::vector<CORESubsystem*>::iterator it;
		for(it = subsystems.begin(); it != subsystems.end(); ++it){
//			cout << "robot init " << (*it)->name() << endl;
			(*it)->robotInit();
		}
#if defined(USE_NAVX)
	try {
		ahrs = new AHRS(SerialPort::Port::kMXP);
		std::cout <<"WARNING: NAVX INIT" << std::endl;
	} catch (std::exception ex ) {
		std::string err_string = "ERROR: instantiating navX-MXP:  ";
		err_string += ex.what();
		DriverStation::ReportError(err_string.c_str());
	}
#endif
	outLog.appendLog("\n\n\n\n\n");
	outLog.printLog();
	loopTimer.Reset();
	loopTimer.Start();
	loopStarted = true;
//	CD.updateSD();
}

void CORERobot::teleopInit(void){
	outLog.appendLog("--------- Teleop Init---------");
	outLog.startTime();
//	outLog.Mode = Log::TELE;
	joystick.register_combo(COMBO3, 0, 4);
	joystick.register_combo(COMBO4, 0, 2);
#if defined(USE_NAVX)
    if (!ahrs->IsCalibrating()) {
//        Wait( 0.3 );
        ahrs->ZeroYaw();
    }
#endif
	std::vector<CORESubsystem*>::iterator it;
	for(it = subsystems.begin(); it != subsystems.end(); ++it){
//		cout << "tele init " << (*it)->name() << endl;
		(*it)->teleopInit();
	}
	outLog.appendLog("\n\n\n\n\n");
	outLog.printLog();
	loopTimer.Reset();
	loopTimer.Start();
	loopStarted = true;
//	CD.updateSD();
}

void CORERobot::teleop(){
	std::vector<CORESubsystem*>::iterator it;
	joystick.update_cache();
	if (joystick.combo(COMBO3)){
		isHybrid = false;
		outLog.appendLog("Hybrid Mode Manually Disabled");
	}
	if (joystick.combo(COMBO4)){
		outLog.appendLog("Logs Manually Printed");
		outLog.printLog();
	}
	for (it = subsystems.begin(); it != subsystems.end(); ++it){
//		cout << "teleop " << (*it)->name() << endl;
		(*it)->teleop();
	}
//	CD.updateSD();
}
void CORERobot::teleopEnd(){
	std::vector<CORESubsystem*>::iterator it;
	joystick.update_cache();
	for (it = subsystems.begin(); it != subsystems.end(); ++it){
//		cout << "teleop " << (*it)->name() << endl;
		(*it)->teleopEnd();
	}
	outLog.printLog();
	loopStarted = false;
//	CD.updateSD();
}

std::string CORESubsystem::name(void){
	return "undefined";
}

void CORESubsystem::robotInit(void){
	printf("Unimplemented robot_init\n");
}

void CORESubsystem::teleopInit(void){
	printf("Unimplemented teleop_init\n");
}

void CORESubsystem::teleop(){
	printf("Unimplemented teleop function\n");
}
void CORERobot::link(motors motorKey,CANTalon* motor){
	motorMap.insert(std::pair<motors,CANTalon*>(motorKey,motor));
}
void CORERobot::link(digitalSensors digitalSensorKey,DigitalInput* sensor){
	digitalSensorMap.insert(std::pair<digitalSensors,DigitalInput*>(digitalSensorKey, sensor));
}
void CORERobot::link(analogSensors analogSensorKey,AnalogInput* sensor){
	analogSensorMap.insert(std::pair<analogSensors,AnalogInput*>(analogSensorKey, sensor));
}
void CORERobot::link(pneumatics pneumaticKey, DoubleSolenoid* cylinder){
	pneumaticMap.insert(std::pair<pneumatics,DoubleSolenoid*>(pneumaticKey, cylinder));
}

double CORERobot::getLoopWait(){
	if (!loopStarted){
		loopTimer.Reset();
		loopTimer.Start();
		loopStarted = true;
	}
	double loopTime = loopTimer.Get()<.1?0.1-loopTimer.Get():0.0;
	SmartDashboard::PutNumber("Timer", loopTimer.Get());
	if (loopTimer.Get() >= .12){
		outLog.appendLog("[PROBLEM] Loop Time High! Timer at: ",loopTimer.Get());
	}
	loopTimer.Reset();
	return loopTime;
}
// void CORERobot::link()
