#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  rightEncode,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncode,     sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  beltEncode,     sensorQuadEncoder)
#pragma config(Motor,  port1,           topLeft,       tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           topRight,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           botLeft,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           botRight,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           frontRight,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           backRight,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           frontLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           backLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           belt,          tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

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
int auton = 1;
int btnPressed = 0;
int x_d = 0;
int x_r = 0;
int y_d = 0;
int correct;
string mode;
string mainBattery;
string auto;
int beltspeed;
int liftspeed = 90;

task stoplift()
{
	motor[topLeft] = 0;
	motor[topRight] =  0;
	motor[botLeft] = 0;
	motor[botRight] =  0;
}


task lift()
{
	motor[topLeft] = liftspeed;
	motor[topRight] =  liftspeed;
	motor[botLeft] = liftspeed;
	motor[botRight] =  liftspeed;
}

task LCD()
{
	displayLCDCenteredString(0, mode);
	while(true)
	{
		if(mode == "teleop")
		{
			sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V');
			displayLCDCenteredString(1, mainBattery);
		}
		if(mode == "auton")
		{
			if(auton == 1)
			{
				auto = "Auton 1";
			}
			if(auton == 2)
			{
				auto = "Auton 2";
			}
			if(auton == 3)
			{
				auto = "Auton 3";
			}
			if(auton == 4)
			{
				auto = "Auton 4";
			}
			if(auton == 10)
			{
				auto = "Finished";
			}
			displayLCDCenteredString(1, auto);
		}
	}
}

task drive()
{
	correct = x_d * .20;
	if(x_d > 0) x_r = x_r - correct;
	if(x_d < 0) x_r = x_r + correct;
	motor[frontRight] = y_d - x_r - x_d;
	motor[backRight] =  y_d - x_r + x_d;
	motor[frontLeft] = y_d + x_r + x_d;
	motor[backLeft] =  y_d + x_r - x_d;
}

void pre_auton()
{
	displayLCDCenteredString(0, "Choose Auton:");

	while (btnPressed != 2)
	{
		if (auton == 1)
		{
			displayLCDCenteredString(1, "Forward / Back");
		}
		if (auton == 2)
		{
			displayLCDCenteredString(1, "Dump Back");
		}
		if (auton == 3)
		{
			displayLCDCenteredString(1, "Spin Dump");
		}
		if (auton == 4)
		{
			displayLCDCenteredString(1, "Short Pole");
		}
		if (auton == 5)
		{
			displayLCDCenteredString(1, "Tall Pole");
		}
		btnPressed = nLCDButtons;
		if (btnPressed == 4)
		{
			auton = auton + 1;
		}
		if (btnPressed == 1)
		{
			auton = auton - 1;
		}
		if(auton > 5)
		{
			auton = 1;
		}
		if(auton < 1)
		{
			auton = 5;
		}
	}

	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

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
	/*	mode = "auton";
	startTask(LCD);
	if(auton == 1)
	{*/
	y_d = 90;
	startTask(drive);
	wait(1);
	y_d = -90;
	startTask(drive);
	wait(.5);
	y_d = 0;
	startTask(drive);
	/*	auton = 10;
	}
	if(auton == 2)
	{
	y_d = 90;
	startTask(drive);
	wait(1);
	y_d = 0;
	wait(.5);
	liftspeed = 90;
	startTask(lift);
	wait(.25);
	startTask(stoplift);
	motor[belt] = 90;
	wait(1/3);
	motor[belt] = 0;
	liftspeed = 90;
	startTask(lift);
	wait(1);
	startTask(stoplift)
	motor[belt] = 90;
	wait(2);
	motor[belt] = 0;
	auton = 10;
	}
	if(auton = 3)
	{

	}*/
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
	clearTimer(timer4);
	mode = "teleop";
	startTask(LCD);
	int threshold = 15;
	beltspeed = 90;
	int cubes = 0;
	clearTimer(timer1);
	bool toggle1 = false;
	int toggletime = 200;
	bool togglecheck = false;
	liftspeed = 90;

	while(true)
	{
		x_d = vexRT[Ch1];
		x_r = vexRT[Ch4];
		y_d = vexRT[Ch3];

		if (time1[timer1] >= toggletime)
		{
			togglecheck = true;
			clearTimer(timer1);
		}
		if (togglecheck == true)
		{
			if (vexRT[Btn8U] == 1)
			{
				if (toggle1 == false) toggle1 = true;
			}
			else if(vexRT[Btn6D] == 1)
			{
				if (toggle1 == true) toggle1 = false;
			}
		}


		if(abs(x_d) < threshold) x_d = 0;
		if(abs(x_r) < threshold) x_r = 0;
		if(abs(y_d) < threshold) y_d = 0;

		if(vexRT[Btn5U] == 1)
		{
			liftspeed = sqrt(liftspeed ^ 2);
			startTask(lift);
		}
		else if(vexRT[Btn5D] == 1)
		{
			liftspeed = sqrt(liftspeed ^ 2);
			liftspeed = liftspeed * -1;
			startTask(lift);
		}
		else
		{
			startTask(stoplift);
		}

		if(vexRT[Btn8L] == 1) cubes = 0;
		if(vexRT[Btn8D] == 1) cubes = 1;
		if(vexRT[Btn8R] == 1) cubes = 2;

		if (toggle1 == true)
		{
			if(vexRT[Btn6U] == 1)
			{
				if(cubes == 0) motor[belt] = 0;
				if(cubes == 1) motor[belt] = 10;
				if(cubes == 2) motor[belt] = 20;
			}
			else
			{
				if(vexRT[Btn6U] == 1)
				{
					motor[belt] = beltspeed;
				}
				else if(vexRT[Btn6D] == 1)
				{
					motor[belt] = beltspeed * -1;
				}
				else
				{
					if(cubes == 0) motor[belt] = 0;
					if(cubes == 1) motor[belt] = 10;
					if(cubes == 2) motor[belt] = 20;
				}
			}
		}
		else
		{
			if(vexRT[Btn6U] == 1)
			{
				motor[belt] = beltspeed;
			}
			else if(vexRT[Btn6D] == 1)
			{
				motor[belt] = beltspeed * -1;
			}
			else
			{
				if(cubes == 0) motor[belt] = 0;
				if(cubes == 1) motor[belt] = 10;
				if(cubes == 2) motor[belt] = 20;
			}
		}

		startTask(drive);

	}
}