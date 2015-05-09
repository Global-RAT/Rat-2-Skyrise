#pragma config(Motor,  port2,           frontRight,    tmotorNormal, openLoop)
#pragma config(Motor,  port4,           backRight,     tmotorNormal, openLoop)
#pragma config(Motor,  port1,           frontLeft,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           backLeft,      tmotorNormal, openLoop, reversed)
#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	// .....................................................................................
	// Insert user code here.
	// .....................................................................................

	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop
	bool toggle1 = false;
	int toggletime = 200;
	bool togglecheck = false;
	int X2 = 0, Y1 = 0, X1 = 0, threshold = 10;

	while (true)
	{
		if (time1[timer1] >= toggletime)
		{
			togglecheck = true;
			clearTimer(timer1);
		}
		//Create "deadzone" variables. Adjust threshold value to increase/decrease deadzone

		//Create "deadzone" for Y1/Ch3
		if(abs(vexRT[Ch3]) > threshold)
			Y1 = vexRT[Ch3];
		else
			Y1 = 0;
		//Create "deadzone" for X1/Ch4
		if(abs(vexRT[Ch4]) > threshold)
			X1 = vexRT[Ch4];
		else
			X1 = 0;
		//Create "deadzone" for X2/Ch1
		if(abs(vexRT[Ch1]) > threshold)
			X2 = vexRT[Ch1];
		else
			X2 = 0;


		if (togglecheck == true)
		{
			if (vexRT[Btn8D] == 1)
			{
				if (toggle1 == false)
					toggle1 = true;
				else
					if (toggle1 == true)
					toggle1 = false;
			}
		}
		if (toggle1 == true)
		{
			X1 = X1 * -1;
			Y1 = Y1 * -1;
		}
		togglecheck = false;

		//Remote Control Commands
		motor[frontRight] = Y1 - X2 - X1;
		motor[backRight] =  Y1 - X2 + X1;
		motor[frontLeft] = Y1 + X2 + X1;
		motor[backLeft] =  Y1 + X2 - X1;
	}
}
