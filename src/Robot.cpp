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
	SendableChooser defenseChooser;
	#if defined(ULTIMATE_MODE)
		TeleSubsystem teleSubsystem;
	#endif
public:
	Robot() :
		robot(),
		autoControl(robot.outLog),
		teleControl(robot.outLog),
//		lift(robot),
		drive(robot, vision, teleControl),
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
		autoChooser.AddObject("Test", new std::string("TestActions"));
		SmartDashboard::PutData("auto-choose", &autoChooser);
		defenseChooser.AddDefault("Lowbar", new std::string("Lowbar"));
		defenseChooser.AddObject("Moat", new std::string("Moat"));
		defenseChooser.AddObject("Rough Terrain", new std::string("Rough"));
		defenseChooser.AddObject("Rockwall", new std::string("Rockwall"));
		defenseChooser.AddObject("Ramparts", new std::string("Ramp"));
		SmartDashboard::PutData("defense-choose", &defenseChooser);
	}
	void Autonomous()
	{
//		TestAction test(robot,&conditions::testStart,&conditions::testEnd);
//		TestAction test(robot);
//		autoControl.add(test);
//		autoControl.init();
        std::string choice = *(std::string*) autoChooser.GetSelected();
        std::string defense = *(std::string*) defenseChooser.GetSelected();
        std::cout<<"WARNING: Auto Position:" <<choice<<std::endl;
        robot.outLog.appendLog(choice);
        std::cout<<"WARNING: Auto Def:" << defense << std::endl;
        autoControl.reset();
//		autoControl.add( new DriveAction(robot, 100, 10.0));
//		if(choice=="Lowbar"){
//			getTicks(SmartDashboard::GetNumber(secondaryLong.n,secondaryLong.v));
//			autoControl.add( new DriveAction(robot, toEnc(95.75), NORMAL_SPEED));
        if(choice != "DropTheBall" && choice!="TestActions"){
			if(defense == "Lowbar"){
				autoControl.add( new DriveAction(robot, toEnc(SmartDashboard::GetNumber(lowbarDist.n,lowbarDist.v)),NORMAL_SPEED,1));
			}
	//      if(choice!="Lowbar"){
			else if(defense == "Ramp"){
				autoControl.add(new DriveActionTimePhotoGyro(robot, SmartDashboard::GetNumber(rampartTime.n,rampartTime.v), NORMAL_SPEED));
	//        	autoControl.add( new DriveUntillSettleAction(robot, NORMAL_SPEED));
			}else if (defense == "Moat"){
				autoControl.add(new DriveActionTimePhotoGyro(robot, SmartDashboard::GetNumber(moatTime.n,moatTime.v), NORMAL_SPEED));
			}else if (defense == "Rockwall"){
	//        	autoControl.add(new DriveActionTime(robot, SmartDashboard::GetNumber(wallTime.n,wallTime.v), -NORMAL_SPEED));
	//        	autoControl.add( new WaitAction(robot, .25));
				autoControl.add( new DriveUntillSettleAction(robot, -NORMAL_SPEED));
				autoControl.add( new WaitAction(robot, .05));
//				autoControl.add( new DriveAction(robot, toEnc(SmartDashboard::GetNumber(rockWallFastDrive.n, rockWallFastDrive.v)), -1.0));
				autoControl.add( new WaitAction(robot, .25));
	//        	autoControl.add( new WaitAction(robot, .5));
				autoControl.add( new TurnWithGyroAction(robot, -150, .8));
//				autoControl.add( new WaitAction(robot, .25));
//				autoControl.add( new ResetYawAction(robot));
//				autoControl.add( new WaitAction(robot, .1));
//				autoControl.add( new TurnWithGyroAction(robot, -90, .8));
				autoControl.add( new WaitAction(robot, .25));
				autoControl.add( new ResetYawAction(robot));
				autoControl.add( new WaitAction(robot, .1));
			}else if(defense == "Rough"){
				autoControl.add(new DriveActionTimePhotoGyro(robot, SmartDashboard::GetNumber(roughTime.n,roughTime.v), NORMAL_SPEED));
			}
			autoControl.add( new PickupArmAction(robot, pickupHeight1, true));
			if(defense != "RockWall"){
				autoControl.add( new DrivePhotoAction(robot, -NORMAL_SPEED*.75, FRONT_PHOTO, false));
			}
			autoControl.add( new WaitAction(robot, .25));
			if(choice == "Lowbar"){
				autoControl.add( new TurnWithGyroAction(robot, SmartDashboard::GetNumber(lowbarTurnAngle.n,lowbarTurnAngle.v)));
				autoControl.add( new WaitAction(robot, 1.0));
				autoControl.add( new GoalAlign(robot, vision, VisionSubsystem::LEFT));
			}
			else if(choice == "Obstacle2"){
				autoControl.add( new TurnWithGyroAction(robot, SmartDashboard::GetNumber(auto2Turn.n,auto2Turn.v)));
				autoControl.add( new WaitAction(robot, .5));
				   autoControl.add( new GoalAlign(robot, vision, VisionSubsystem::RIGHT));
			}
			else if(choice == "Obstacle5"){
				autoControl.add( new TurnWithGyroAction(robot, SmartDashboard::GetNumber(auto5Turn.n,auto5Turn.v)));
				autoControl.add( new WaitAction(robot, .5));
				autoControl.add( new GoalAlign(robot, vision, VisionSubsystem::LEFT));
			}else{
				autoControl.add( new WaitAction(robot, .15));
				autoControl.add( new GoalAlign(robot, vision));
			}
	//        if(defense != "Rockwall"){
			autoControl.add( new ShootAction(robot));
	//        }
        }else if(choice == "TestActions"){
        	autoControl.add( new GoalAlign(robot, vision, VisionSubsystem::RIGHT));
        	autoControl.add( new ShootAction(robot, false));
        }else if(choice == "DropTheBall"){

        	autoControl.add( new PickupRollerAction(robot,IN,1.5,true));
        	autoControl.add( new PickupArmAction(robot, pickupHeight2, false));
        	autoControl.add( new WaitAction(robot, .25));

        	autoControl.add( new DriveAction(robot, toEnc(20),.6,1));
        	autoControl.add( new TurnWithGyroAction(robot, -20));
        	autoControl.add( new DriveAction(robot, toEnc(50),.6,1));
        	autoControl.add( new TurnWithGyroAction(robot, 20));
        	autoControl.add( new WaitAction(robot, .25));

        	autoControl.add( new DriveAction(robot, toEnc(SmartDashboard::GetNumber(lowbarDist.n,lowbarDist.v)-50),.6,1));
        	autoControl.add( new PickupArmAction(robot, pickupHeight1, true));
        	autoControl.add( new PickupRollerAction(robot,IN,1.0,true));
        	autoControl.add( new WaitAction(robot, .1));
        	autoControl.add( new TurnWithGyroAction(robot, SmartDashboard::GetNumber(lowbarTurnAngle.n,lowbarTurnAngle.v)));
        	autoControl.add( new GoalAlign(robot, vision, VisionSubsystem::LEFT));
        	autoControl.add( new ShootAction(robot, true));
        	autoControl.add( new PickupArmAction(robot, pickupHeight2, true));
        	autoControl.add( new WaitAction(robot, .5));
        	autoControl.add( new TurnWithGyroAction(robot, 0.0));
        	autoControl.add( new DriveAction(robot, toEnc(SmartDashboard::GetNumber(lowbarDist.n,lowbarDist.v)),-.6,1));

        	autoControl.add( new PickupRollerAction(robot,IN,1.5,true));
        	autoControl.add( new PickupArmAction(robot, pickupHeight2, false));
        	autoControl.add( new WaitAction(robot, .25));

        	autoControl.add( new DriveAction(robot, toEnc(SmartDashboard::GetNumber(lowbarDist.n,lowbarDist.v)),.6,1));
        	autoControl.add( new PickupArmAction(robot, pickupHeight1, true));
        	autoControl.add( new PickupRollerAction(robot,IN,1.0,true));
        	autoControl.add( new WaitAction(robot, .1));
        	autoControl.add( new TurnWithGyroAction(robot, SmartDashboard::GetNumber(lowbarTurnAngle.n,lowbarTurnAngle.v)));
        	autoControl.add( new GoalAlign(robot, vision, VisionSubsystem::LEFT));
        	autoControl.add( new ShootAction(robot, true));


        }



				autoControl.init();
		while (IsAutonomous() and !IsDisabled()) {
			robot.motorMap[BACK_RIGHT]->Set(0.0);
			robot.motorMap[BACK_LEFT]->Set(0.0);
			robot.motorMap[FRONT_RIGHT]->Set(0.0);
			robot.motorMap[FRONT_LEFT]->Set(0.0);
			vision.teleop();
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
