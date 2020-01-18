#include "Shake.h"
#include "DxLib.h"
#include <math.h>

int Shake::Update()
{
	switch (ShakeF)
	{
	case true:
		if (Cnt++ > ShakeTime)
		{
			ShakeF = false;
			break;
		}
		Haba = ShakeHaba * (ShakeTime - Cnt) / ShakeTime;
		//X = GetRand(Haba) - Haba / 2;
		//Y = GetRand(Haba) - Haba / 2;
		double Radian;
		Radian = GetRand(359) / 180.0 * 3.141592;
		X = Haba * cos(Radian);
		Y = Haba * sin(Radian);
		break;
	case false:

		break;
	}
	return 0;
}

void Shake::Start(int ShakeTime, int ShakeHaba)
{
	ShakeF = true;
	Cnt = 0;
	this->ShakeTime = ShakeTime;
	this->ShakeHaba = ShakeHaba;
}

int Shake::GetX()
{
	return X;
}

int Shake::GetY()
{
	return Y;
}

Shake::Shake()
{
	ShakeF = false;
	X = 0;
	Y = 0;
}


Shake::~Shake()
{
}
