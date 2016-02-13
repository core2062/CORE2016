#include "WPILib.h"
#include "CoreLib/CORERobot.h"
#include "CoreLib/CoreAuto.h"
#include "Actions/Actions.h"
#include "Subsytems.h"
#include <iostream>

using namespace CORE;

int toEnc(double inches){
	return (inches/(PI*WHEEL_DIA)) * ENCODER_CONST;
}




class Robot: public SampleRobot
{
	CORERobot robot;
	AutoControl autoControl;
	AutoControl teleControl;
//	LiftSubsystem lift;
	DrivePickupSubsystem drive;
	ShooterSubsystem shooter;
	VisionSubsystem vision;
	SendableChooser autoChooser;
public:


	Robot() :
		robot(),
		autoControl(robot.outLog),
		teleControl(robot.outLog),
//		lift(robot),
		drive(robot, vision),
		shooter(robot),
		vision(robot)
	{
//		robot.add(lift);
		robot.add(drive);
		robot.add(shooter);
		robot.add(vision);
	}

	void RobotInit() {


		robot.robotInit();
		autoChooser.AddDefault("Lowbar", new std::string("Lowbar"));
		autoChooser.AddObject("Obstacle 2", new std::string("Obstacle2"));
		autoChooser.AddObject("Obstacle 3", new std::string("Obstacle3"));
		autoChooser.AddObject("Obstacle 4", new std::string("Obstacle4"));
		autoChooser.AddObject("Obstacle 5", new std::string("Obstacle5"));
		SmartDashboard::PutData("auto-choose", &autoChooser);
	}

	void Autonomous()
	{

//		TestAction test(robot,&conditions::testStart,&conditions::testEnd);
//		TestAction test(robot);
//		autoControl.add(test);
//		autoControl.init();
        std::string choice = *(std::string*) autoChooser.GetSelected();
        std::cout<<"Auto mode:" <<choice<<std::endl;
        robot.outLog.appendLog(choice);

//					autoControl.add( new DriveAction(robot, 100, 10.0));

				if(choice=="Lowbar"){
			//		getTicks(SmartDashboard::GetNumber(secondaryLong.n,secondaryLong.v));

					autoControl.add( new DriveAction(robot, toEnc(95.75), NORMAL_SPEED));
					autoControl.add( new DriveUntillSettleAction(robot, NORMAL_SPEED));
					autoControl.add( new TurnWithGyroAction(robot, 45.0));
					autoControl.add( new ShootAction(robot));

				}
				else if(choice=="Obstacle 2"){

					//getTicks(SmartDashboard::GetNumber(secondaryMedium.n,secondaryMedium.v));

					autoControl.add( new DriveAction(robot, toEnc(47.875), NORMAL_SPEED));
					autoControl.add( new DriveUntillSettleAction(robot, NORMAL_SPEED));
					autoControl.add( new TurnWithGyroAction(robot, 30.0));
					autoControl.add( new ShootAction(robot));

				}
				else if(choice=="Obstacle 3"){
				//	getTicks(SmartDashboard::GetNumber(testAuto.n,testAuto.v));

					autoControl.add( new DriveAction(robot, toEnc(74), NORMAL_SPEED));
					autoControl.add( new DriveUntillSettleAction(robot, NORMAL_SPEED));
					autoControl.add( new ShootAction(robot));

				}
				else if(choice=="Obstacle 4"){

				//	getTicks(SmartDashboard::GetNumber(mediumDistance.n,mediumDistance.v));

					autoControl.add( new DriveAction(robot, toEnc(47.875), NORMAL_SPEED));
					autoControl.add( new DriveUntillSettleAction(robot, NORMAL_SPEED));
					autoControl.add( new TurnWithGyroAction(robot, -30.0));
					autoControl.add( new ShootAction(robot));

				}
				else if(choice=="Obstacle 5"){
				//	getTicks(SmartDashboard::GetNumber(longDistance.n,longDistance.v));

					autoControl.add( new DriveAction(robot, toEnc(95.75), NORMAL_SPEED));
					autoControl.add( new DriveUntillSettleAction(robot, NORMAL_SPEED));
					autoControl.add( new TurnWithGyroAction(robot, -45.0));
					autoControl.add( new ShootAction(robot));

				}
				autoControl.init();
		while (IsAutonomous() and !IsDisabled()) {
//			autoControl.iter();
			vision.teleop();
			Wait(robot.getLoopWait());
		}
	}

	void OperatorControl()
	{
		robot.teleopInit();
		while (IsOperatorControl() && IsEnabled())
		{

			robot.teleop();

			if (robot.isHybrid){
				teleControl.iter();
			}
//			SmartDashboard::PutNumber("topLiftLim", robot.digitalSensorMap[digitalSensors::BOT_LIFT_LIMIT]->Get());
//			SmartDashboard::PutNumber("botLiftLim", robot.digitalSensorMap[digitalSensors::TOP_LIFT_LIMIT]->Get());
//			SmartDashboard::PutNumber("motorVal", robot.motorMap[motors::LIFT_MOTOR]->Get());
//			SmartDashboard::PutNumber("joyval", robot.joystick.axis(controllerInputs::LIFT_AXIS));
			Wait(robot.getLoopWait());				// wait for a motor update time
		}
		robot.teleopEnd();
	}
	void Test()
	{
	}
};

START_ROBOT_CLASS(Robot);
