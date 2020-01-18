#include "BgChip.h"
#include "DxLib.h"


void BgChip::Draw()
{
	if (GrHandle != -1)
		DrawRotaGraph(X, Y, ExRate, 0, GrHandle, 1);
}

void BgChip::SetXY(int X, int Y)
{
	this->X = X;
	this->Y = Y;
}

int BgChip::GetX()
{
	return X;
}

int BgChip::GetY()
{
	return Y;
}

void BgChip::SetGrHandle(int GrHandle)
{
	this->GrHandle = GrHandle;
}

int BgChip::GetGrHandle()
{
	return GrHandle;
}

BgChip::BgChip()
{
	ExRate = 4;
}


BgChip::~BgChip()
{
}
