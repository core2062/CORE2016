#include "WPILib.h"
#include "CoreLib/CORERobot.h"
#include "CoreLib/CoreAuto.h"
#include "Actions/Actions.h"
#include "Subsytems.h"
#include <iostream>

using namespace CORE;

int toEnc(double inches){
	return ((inches/((PI)*WHEEL_DIA)) * ENCODER_CONST * ENCODER_RES);
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
#if defined(ULTIMATE_MODE)
	TeleSubsystem teleSubsystem;
#endif
public:


	Robot() :
		robot(),
		autoControl(robot.outLog),
		teleControl(robot.outLog),
//		lift(robot),
		drive(robot, vision),
		shooter(robot),
		vision(robot)
#if defined(ULTIMATE_MODE)
		,teleSubsystem(robot, teleControl, drive)
#endif
	{
//		robot.add(lift);
		robot.add(drive);
		robot.add(shooter);
		robot.add(vision);
#if defined(ULTIMATE_MODE)
		robot.add(teleSubsystem);
#endif
	}

	void RobotInit() {


		robot.robotInit();
		autoChooser.AddDefault("Lowbar", new std::string("Lowbar"));
		autoChooser.AddObject("Obstacle 2", new std::string("Obstacle2"));
		autoChooser.AddObject("Obstacle 3 / Center", new std::string("Obstacle3"));
		autoChooser.AddObject("Obstacle 4", new std::string("Obstacle4"));
		autoChooser.AddObject("Obstacle 5", new std::string("Obstacle5"));
		autoChooser.AddObject("Drop the Ball", new std::string("DropTheBall"));
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
        autoControl.reset();
//					autoControl.add( new DriveAction(robot, 100, 10.0));

				if(choice=="Lowbar"){
			//		getTicks(SmartDashboard::GetNumber(secondaryLong.n,secondaryLong.v));

//					autoControl.add( new DriveAction(robot, toEnc(95.75), NORMAL_SPEED));
					autoControl.add( new DriveUntillSettleAction(robot, NORMAL_SPEED, false));
//TODO: this			autoControl.add( new DriveAction)
					autoControl.add( new WaitAction(robot, .5));
//					autoControl.add( new TurnWithGyroAction(robot, 0.0));
//					autoControl.add( new WaitAction(robot, .5));
					autoControl.add( new DriveAction(robot, toEnc(SmartDashboard::GetNumber(lowbarDist.n,lowbarDist.v)),NORMAL_SPEED,1));
					autoControl.add( new WaitAction(robot, .5));
					autoControl.add( new PickupArmAction(robot, pickupHeight1, false));
					autoControl.add( new TurnWithGyroAction(robot, SmartDashboard::GetNumber(lowbarTurnAngle.n,lowbarTurnAngle.v)));
					autoControl.add( new WaitAction(robot, .5));
					autoControl.add( new GoalAlign(robot, vision));
//					autoControl.add( new WaitAction(robot, .5));
					autoControl.add( new ShootAction(robot));

				}
				else if(choice=="Obstacle2"){

					//autoControl.add( new DriveAction(robot, toEnc(95.75), NORMAL_SPEED));
//					autoControl.add( new DriveUntillSettleAction(robot, NORMAL_SPEED, true));
////TODO: this			autoControl.add( new DriveAction)
//					autoControl.add( new WaitAction(robot, 2.0));
//					autoControl.add( new DriveAction(robot, toEnc(SmartDashboard::GetNumber(lowbarDist.n,lowbarDist.v)),NORMAL_SPEED,1));
//					autoControl.add( new WaitAction(robot, 2.0));
//					autoControl.add( new TurnWithGyroAction(robot, 30.0));
//					autoControl.add( new WaitAction(robot, 2.0));
					autoControl.add( new GoalAlign(robot, vision));
					autoControl.add( new ShootAction(robot));
////					autoControl.add( new PickupArmAction(robot, pickupHeight1));
//					autoControl.add( new ShootAction(robot));

				}
				else if(choice=="Obstacle3"){
					//autoControl.add( new DriveAction(robot, toEnc(95.75), NORMAL_SPEED));
					autoControl.add( new DriveUntillSettleAction(robot, (SmartDashboard::GetBoolean(autoRockwall.n,autoRockwall.b))?-NORMAL_SPEED:NORMAL_SPEED, (SmartDashboard::GetBoolean(autoMoat.n,autoMoat.b))?true:false));
					autoControl.add( new WaitAction(robot, .5));
					autoControl.add( new DriveAction(robot, toEnc(SmartDashboard::GetNumber(autoDriveBack.n,autoDriveBack.v)), -NORMAL_SPEED));

					if(SmartDashboard::GetBoolean(autoRockwall.n,autoRockwall.b)){
						autoControl.add( new WaitAction(robot, .5));
						autoControl.add( new TurnWithGyroAction(robot, -170, 1.0));

					}

//TODO: this			autoControl.add( new DriveAction)
					autoControl.add( new WaitAction(robot, .5));
					if(SmartDashboard::GetBoolean(autoRockwall.n,autoRockwall.b)){
//						autoControl.add( new ResetYawAction(robot));

					}
//					autoControl.add( new TurnWithGyroAction(robot, 0.0));
//					autoControl.add( new WaitAction(robot, .5));
//					autoControl.add( new DriveAction(robot, toEnc(SmartDashboard::GetNumber(lowbarDist.n,lowbarDist.v)),NORMAL_SPEED,1));
//					autoControl.add( new WaitAction(robot, .5));
					autoControl.add( new PickupArmAction(robot, pickupHeight1, false));
//					autoControl.add( new TurnWithGyroAction(robot, SmartDashboard::GetNumber(lowbarTurnAngle.n,lowbarTurnAngle.v)));
					autoControl.add( new WaitAction(robot, .5));
					autoControl.add( new GoalAlign(robot, vision));
//					autoControl.add( new WaitAction(robot, .5));
					autoControl.add( new ShootAction(robot));

				}
				else if(choice=="Obstacle4"){

					//autoControl.add( new DriveAction(robot, toEnc(95.75), NORMAL_SPEED));
					autoControl.add( new DriveUntillSettleAction(robot, NORMAL_SPEED, true));
//TODO: this			autoControl.add( new DriveAction)
					autoControl.add( new WaitAction(robot, 2.0));
					autoControl.add( new DriveAction(robot, toEnc(SmartDashboard::GetNumber(lowbarDist.n,lowbarDist.v)),NORMAL_SPEED,1));
					autoControl.add( new WaitAction(robot, 2.0));
					autoControl.add( new TurnWithGyroAction(robot, -25.0));
					autoControl.add( new WaitAction(robot, 2.0));
					autoControl.add( new GoalAlign(robot, vision));
//					autoControl.add( new PickupArmAction(robot, pickupHeight1));
					autoControl.add( new ShootAction(robot));

				}
				else if(choice=="Obstacle5"){
					//autoControl.add( new DriveAction(robot, toEnc(95.75), NORMAL_SPEED));
					autoControl.add( new DriveUntillSettleAction(robot, NORMAL_SPEED, true));
//TODO: this			autoControl.add( new DriveAction)
					autoControl.add( new WaitAction(robot, 2.0));
					autoControl.add( new DriveAction(robot, toEnc(SmartDashboard::GetNumber(lowbarDist.n,lowbarDist.v)),NORMAL_SPEED,1));
					autoControl.add( new WaitAction(robot, 2.0));
					autoControl.add( new TurnWithGyroAction(robot, -40.0));
					autoControl.add( new WaitAction(robot, 2.0));
					autoControl.add( new GoalAlign(robot, vision));
//					autoControl.add( new PickupArmAction(robot, pickupHeight1));
					autoControl.add( new ShootAction(robot));

				}
				else if(choice=="DropTheBall"){
				//	getTicks(SmartDashboard::GetNumber(longDistance.n,longDistance.v));

					//autoControl.add( new DriveAction(robot, toEnc(95.75), NORMAL_SPEED));
					autoControl.add( new DriveUntillSettleAction(robot, NORMAL_SPEED));
					autoControl.add( new TurnWithGyroAction(robot, 45.0));
					autoControl.add( new GoalAlign(robot, vision));
					autoControl.add( new ShootAction(robot));
					autoControl.add( new TurnWithGyroAction(robot, -45.0));
					autoControl.add( new DriveUntillSettleAction(robot, -NORMAL_SPEED));
					autoControl.add( new PickupRollerAction(robot, IN, true, 5.0));
					autoControl.add( new PickupArmAction(robot, pickupHeight2));
					autoControl.add( new DriveAction(robot, toEnc(-95.75), -.3));
					//autoControl.add( new PickupArmAction(robot, DRIVE_PICKUP_HEIGHT5));
					autoControl.add( new DriveUntillSettleAction(robot, NORMAL_SPEED));
					autoControl.add( new TurnWithGyroAction(robot, 45.0));
					autoControl.add( new GoalAlign(robot, vision));
					autoControl.add( new ShootAction(robot));
				}
				autoControl.init();
		while (IsAutonomous() and !IsDisabled()) {
			autoControl.iter();
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
#ifdef SHOW_MOTORS
  SmartDashboard::PutNumber(std::string("back right motor voltage"), robot.motorMap[BACK_RIGHT]->GetOutputCurrent());
  SmartDashboard::PutNumber(std::string("front right motor voltage"), robot.motorMap[FRONT_RIGHT]->GetOutputCurrent());
  SmartDashboard::PutNumber(std::string("back left motor voltage"), robot.motorMap[BACK_LEFT]->GetOutputCurrent());
  SmartDashboard::PutNumber(std::string("front left motor voltage"), robot.motorMap[FRONT_LEFT]->GetOutputCurrent());
  SmartDashboard::PutNumber(std::string("right pickup motor voltage"), robot.motorMap[ROLLER]->GetOutputCurrent());
  SmartDashboard::PutNumber(std::string("left pickup motor voltage"), robot.motorMap[LEFT_PICKUP]->GetOutputCurrent());
  SmartDashboard::PutNumber(std::string("roller motor voltage"), robot.motorMap[RIGHT_PICKUP]->GetOutputCurrent());
  SmartDashboard::PutNumber(std::string("lift motor voltage"), robot.motorMap[LIFT_MOTOR]->GetOutputCurrent());
#endif
#ifdef SHOW_SENSORS
 // SmartDashboard::PutNumber(std::string("Left Pickup Pot"), robot.analogSensors[LEFT_POT]->getAnalogAverageVoltage());
#endif

			Wait(robot.getLoopWait());				// wait for a motor update time
		}
		robot.teleopEnd();
	}
	void Test()
	{
	}
};

START_ROBOT_CLASS(Robot);
