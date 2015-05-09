#pragma config(Motor,  port1,           leftMotor,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port2,           rightMotor,    tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port3,           frontMotor,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           rearMotor,     tmotorServoContinuousRotation, openLoop, reversed)
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

	int X1;            // will hold the X value of the analog stick (choices below)
	int Y1;            // will hold the Y value of the analog stick (choices below)
	int X2;
	int threshold = 10;   // helps to eliminate 'noise' from a joystick that isn't perfectly at (0,0)
	bool toggle1 = false;
	int toggletime = 150;
	bool togglecheck = false;
	while(1 == 1)
	{
		X1 = vexRT[Ch4];   // This is the RIGHT analog stick.  For LEFT, change 'Ch1' to 'Ch4'.
		Y1 = vexRT[Ch3];   // This is the RIGHT analog stick.  For LEFT, change 'Ch2' to 'Ch3
		X2 = vexRT[Ch1];

		if (time1[timer1] >= toggletime)
		{
			togglecheck = true;
			clearTimer(timer1);
		}

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

		if (abs(X1) < threshold)
			X1 = 0;
		if (abs(X2) < threshold)
			X2 = 0;
		if (abs(Y1) < threshold)
			Y1 = 0;

		// Forward, and swing turns: (both abs(X) and abs(Y) are above the threshold, and Y is POSITIVE)
		motor[leftMotor]  = (Y1 + X2)/2;
		motor[rightMotor] = (Y1 - X2)/2;

	}

}
