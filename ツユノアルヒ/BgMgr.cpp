#include "BgMgr.h"
#include "Shake.h"
#include "DxLib.h"


void BgMgr::Initialize()
{
}

void BgMgr::Draw()
{
	for (int l = 0; l < 3; l++)
	{
		for (int y = 0; y < 15; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				int home = 8 * ExRate;
				int d = 16 * ExRate;
				DrawRotaGraph(home + x * d+X + Shake::Instance()->GetX(), home + y * d+Y + Shake::Instance()->GetY(), ExRate, 0, BgData[l][y][x], 1);
			}
		}
	}
}

void BgMgr::Draw(int Layer)
{
	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			int home = 8 * ExRate;
			int d = 16 * ExRate;
			DrawRotaGraph(home + x * d + X + Shake::Instance()->GetX(), home + y * d + Y + Shake::Instance()->GetY(), ExRate, 0, BgData[Layer][y][x], 1);
		}
	}

}

void BgMgr::PutChip(int Layer, int X, int Y, int GrHandle)
{
	BgData[Layer][Y][X] = GrHandle;
}

int BgMgr::GetChip(int Layer, int ScreenX, int ScreenY)
{
	int BgX = (ScreenX - X) / (16 * ExRate);
	int BgY = (ScreenY - Y) / (16 * ExRate);
	if (BgX >= 0 && BgX <= 20 && BgY >= 0 && BgY <= 15)
	{
		return BgData[Layer][BgY][BgX];
	}
	else
	{
		return -1;
	}
}

int BgMgr::GetChipBgZahyo(int Layer, int BgX, int BgY)
{
	if (BgX >= 0 && BgX <= 20 && BgY >= 0 && BgY <= 15)
	{
		return BgData[Layer][BgY][BgX];
	}
	else
	{
		return -1;
	}
}

void BgMgr::SetExRate(double ExRate)
{
	this->ExRate = ExRate;
}

void BgMgr::SetXY(int X, int Y)
{
	this->X = X;
	this->Y = Y;
}

int BgMgr::GetX()
{
	return X;
}

int BgMgr::GetY()
{
	return Y;
}

BgMgr::BgMgr()
{
	for (int l = 0; l < 3; l++)
	{
		for (int y = 0; y < 15; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				BgData[l][y][x] = -1;
			}
		}
	}

}


BgMgr::~BgMgr()
{
}
