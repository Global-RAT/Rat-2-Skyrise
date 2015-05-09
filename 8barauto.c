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
int x_d = 0;
int x_r = 0;
int y_d = 0;

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

task main()
{
		y_d = 90;
		startTask(drive);
		wait(1);
		y_d = -90;
		startTask(drive);
		wait(.5);
		y_d = 0;
		startTask(drive);


}
