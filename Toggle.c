
task main()
{
	clearTimer(timer1);
	bool toggle1 = false;
	int toggletime = 200;
	bool togglecheck = false;
	int X1 = 1;
	int Y1 = 1;
	while (1 == 1)
	{
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
	}
}
