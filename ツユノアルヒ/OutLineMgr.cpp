#include "OutLineMgr.h"
#include "Bank.h"
#include "Shake.h"
#include "DxLib.h"


void OutLineMgr::Update()
{
}

void OutLineMgr::Draw()
{
	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			for (int d = 0; d < 4; d++)
			{
				if (OutLineData[y][x][d] == 1)
				{
					DrawRotaGraph((x + 0.5) * 16 * 4 + Shake::Instance()->GetX(), (y + 0.5) * 16 * 4 + Shake::Instance()->GetY(), 4, 0, GrHandleData[d], 1);
				}
			}
		}
	}
}

void OutLineMgr::KillLine(int X, int Y)
{
	for (int d = 0; d < 4; d++)
	{
		OutLineData[Y][X][d] = 0;
	}
}

void OutLineMgr::SetLine(int X, int Y, Dire Direction)
{
	OutLineData[Y][X][Direction] = 1;
}

void OutLineMgr::Init()
{
	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			for (int d = 0; d < 4; d++)
			{
				OutLineData[y][x][d] = 0;
			}
		}
	}
}

OutLineMgr::OutLineMgr()
{
	Init();
	GrHandleData = Bank::Instance()->GetGrHandle(11);
}


OutLineMgr::~OutLineMgr()
{
}
