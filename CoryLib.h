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

//Positional closed loop struct for closed loop control
typedef struct
{
	tGearBox *gearBox;
	float kP;
	float kI;
	float kD;
	float lastError;
	float lastI;
}tPositionalGearbox;

int limit(int inValue)
{
	if(inValue > 127) return 127;
	if(inValue < -127) return -127;
	return inValue;
}

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

//Create positional gearbox with PID Gains
void createPositionalGearbox(tPositionalGearbox &sensoredGearbox, tGearBox normalGearbox, float kP, float kI, float kD)
{
	sensoredGearbox.gearBox = &normalGearbox;
	sensoredGearbox.kP = kP;
	sensoredGearbox.kI = kI;
	sensoredGearbox.kD = kD;
}

//Arcade drive based on throttle and wheel
void arcadeDrive(tDriveTrain driveTrain, int throttle, int wheel)
{
	int leftSide = throttle + wheel;
	int rightSide = throttle - wheel;
	for(int i = 0; i < driveTrain.leftGearbox->numMotors; i++)
	{
		motor[driveTrain.leftGearbox->motors[i]] = limit(leftSide);
	}
	for(int i = 0; i < driveTrain.rightGearbox->numMotors; i++)
	{
		motor[driveTrain.rightGearbox->motors[i]] = limit(rightSide);
	}
}

//Tank drive based on side power
void tankDrive(tDriveTrain driveTrain, int leftSide, int rightSide)
{
	for(int i = 0; i < driveTrain.leftGearbox->numMotors; i++)
	{
		motor[driveTrain.leftGearbox->motors[i]] = limit(leftSide);
	}
	for(int i = 0; i < driveTrain.rightGearbox->numMotors; i++)
	{
		motor[driveTrain.rightGearbox->motors[i]] = limit(rightSide);
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
		motor[gearBox.motors[i]] = limit(power);
	}
}

//Control manipulator based on joystick
void stickManipulate(tGearBox gearBox, int power)
{
	for(int i = 0; i < gearBox.numMotors; i++)
	{
		motor[gearBox.motors[i]] = limit(power);
	}
}

void positionControl(tPositionalGearbox gearbox, float error)
{
	float proportion = gearbox.kP * error;
	float integral = (gearbox.kI * error) + gearbox.lastI;
	float derivative = (error - gearbox.lastError) * gearbox.kD;
	float outValue = proportion + integral + derivative;
	gearbox.lastError = error;
	for(int i = 0; i < gearbox.gearBox->numMotors; i++)
	{
		motor[gearbox.gearBox->motors[i]] = limit(outValue);
	}
}

#endif
