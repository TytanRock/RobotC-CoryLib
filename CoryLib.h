#ifndef CORYLIB_H
#define CORYLIB_H

//Gearbox struct for drivetrain/manipulators
typedef struct
{
	int numMotors;
	int motors[5];
}tGearBox;

//Drivetrain struct for types of driving
typedef struct
{
	tGearBox *leftGearbox;
	tGearBox *rightGearbox;
}tDriveTrain;

//Create the gearboxes based on number of motors
void createGearBox(tGearBox &gearBox, int m1 = -1, int m2 = -1, int m3 = -1, int m4 = -1)
{
	int numberOfMotors = 0;
	if(m1 != -1)
	{
		gearBox.motors[0] = m1;
		numberOfMotors = 1;
	}
	if(m2 != -1)
	{
		gearBox.motors[1] = m2;
		numberOfMotors = 2;
	}
	if(m3 != -1)
	{
		gearBox.motors[2] = m3;
		numberOfMotors = 3;
	}
	if(m4 != -1)
	{
		gearBox.motors[3] = m4;
		numberOfMotors = 4;
	}
	gearBox.numMotors = numberOfMotors;
}

//Create the drivetrain from your gearbox
void createDriveTrain(tDriveTrain &driveTrain, tGearBox left, tGearBox right)
{
	driveTrain.leftGearbox = &left;
	driveTrain.rightGearbox = &right;
}

//Arcade drive based on throttle and wheel
void arcadeDrive(tDriveTrain driveTrain, int throttle, int wheel)
{
	int leftSide = throttle + wheel;
	int rightSide = throttle - wheel;
	for(int i = 0; i < driveTrain.leftGearbox->numMotors; i++)
	{
		motor[driveTrain.leftGearbox->motors[i]] = leftSide;
	}
	for(int i = 0; i < driveTrain.rightGearbox->numMotors; i++)
	{
		motor[driveTrain.rightGearbox->motors[i]] = rightSide;
	}
}

//Tank drive based on side power
void tankDrive(tDriveTrain driveTrain, int leftSide, int rightSide)
{
	for(int i = 0; i < driveTrain.leftGearbox->numMotors; i++)
	{
		motor[driveTrain.leftGearbox->motors[i]] = leftSide;
	}
	for(int i = 0; i < driveTrain.rightGearbox->numMotors; i++)
	{
		motor[driveTrain.rightGearbox->motors[i]] = rightSide;
	}
}

//Control manipulator based on two buttons
void buttonManipulate(tGearBox gearBox, bool buttonUp, bool buttonDown, int powerUp = 127, int powerDown = -127)
{
	int power;
	if(buttonUp) power = powerUp;
	else if(buttonDown) power = powerDown;
	else power = 0;
	for(int i = 0; i < gearBox.numMotors; i++)
	{
		motor[gearBox.motors[i]] = power;
	}
}

//Control manipulator based on joystick
void stickManipulate(tGearBox gearBox, int power)
{
	for(int i = 0; i < gearBox.numMotors; i++)
	{
		motor[gearBox.motors[i]] = power;
	}
}

#endif
