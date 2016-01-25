#include "WPILib.h"
#include "CoreLib/CORERobot.h"
#include "CoreLib/CoreAuto.h"
#include "Actions/TestAction.h"
#include "Subsytems.h"

using namespace CORE;

class Robot: public SampleRobot
{
	CORERobot robot;
	AutoControl autoControl;
	LiftSubsystem lift;
	DrivePickupSubsystem drive;
	ShooterSubsystem shooter;
	VisionSubsystem vision;


public:
	Robot() :
		robot(),
		autoControl(robot),
		lift(robot),
		drive(robot, vision),
		shooter(robot),
		vision(robot)
	{
		robot.add(lift);
		robot.add(drive);
		robot.add(shooter);
		robot.add(vision);
	}

	void RobotInit() {
		robot.robotInit();
	}

	void Autonomous()
	{
//		TestAction test(robot,&conditions::testStart,&conditions::testEnd);
//		TestAction test(robot);
//		autoControl.add(test);
//		autoControl.init();
		while (IsAutonomous() and !IsDisabled()) {
			autoControl.iter();
			Wait(robot.getLoopWait());
		}
	}

	void OperatorControl()
	{
		robot.teleopInit();
		while (IsOperatorControl() && IsEnabled())
		{
			robot.teleop();
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
