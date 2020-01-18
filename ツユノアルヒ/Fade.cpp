#include "Fade.h"
#include "Bank.h"
#include "DxLib.h"
#include <math.h>

void Fade::SetCnt(int Cnt)
{
	this->Cnt = Cnt;
	for (int y = StartY; y < 9; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			Chip[y][x].SetGrNum(Cnt);
		}
	}


}

void Fade::SetDrawRGB(int R, int G, int B)
{
	for (int y = StartY; y < 9; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			Chip[y][x].SetDrawRGB(R,G,B);
		}
	}

}

void Fade::SetDrawAlpha(int DrawAlpha)
{
	for (int y = StartY; y < 9; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			Chip[y][x].SetDrawAlpha(DrawAlpha);
		}
	}

}

int Fade::GetCnt()
{
	return Cnt;
}

int Fade::GetFadeInF()
{
	return FadeInF;
}

int Fade::GetFadeOutF()
{
	return FadeOutF;
}

void Fade::FadeInStart()
{
	//Cnt = 0;
	FadeInF = 1;
	FadeOutF = 0;
	for (int y = StartY; y < 9; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			Chip[y][x].SetGrNum(min(max(Cnt, 0), 15));
		}
	}

}

void Fade::FadeInStartOsyare()
{
	//Cnt = 0;
	FadeInF = 2;
	FadeOutF = 0;
	for (int y = StartY; y < 9; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			Chip[y][x].SetGrNum(min(max(Cnt, 0), 15));
		}
	}

}

void Fade::FadeOutStart()
{
	//Cnt = 15;
	FadeOutF = 1;
	FadeInF = 0;
	for (int y = StartY; y < 9; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			Chip[y][x].SetGrNum(min(max(Cnt, 0), 15));
		}
	}
}


void Fade::FadeOutStartOsyare()
{
	//Cnt = 15;
	FadeOutF = 2;
	FadeInF = 0;
	for (int y = StartY; y < 9; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			Chip[y][x].SetGrNum(min(max(Cnt, 0), 15));
		}
	}
}

void Fade::Update()
{
	if (FadeInF == -1)
		FadeInF = 0;
	if (FadeOutF == -1)
		FadeOutF = 0;

	if (FadeInF == 1)
	{
		Cnt++;
		for (int y = StartY; y < 9; y++)
		{
			for (int x = 0; x < 12; x++)
			{
				Chip[y][x].SetGrNum(min(max(Cnt, 0), 15));
			}
		}
		if (Cnt >= 16)
		{
			FadeInF = -1;
			Cnt = 16;
		}

	}
	if (FadeInF == 2)
	{
		Cnt++;
		for (int y = StartY; y < 9; y++)
		{
			for (int x = 0; x < 12; x++)
			{
				Chip[y][x].SetGrNum(min(max(Cnt - x - y, 0), 15));
			}
		}
		if (Cnt - 11 - 8 >= 15)
		{
			FadeInF = -1;
			Cnt = 15;
		}

	}


	if (FadeOutF == 1)
	{
		Cnt--;
		for (int y = StartY; y < 9; y++)
		{
			for (int x = 0; x < 12; x++)
			{
				Chip[y][x].SetGrNum(min(max(Cnt,0),15));
			}
		}
		if (Cnt <= 0)
		{
			FadeOutF = -1;
			Cnt = 0;
		}

	}
	if (FadeOutF == 2)
	{
		Cnt--;
		for (int y = StartY; y < 9; y++)
		{
			for (int x = 0; x < 12; x++)
			{
				Chip[y][x].SetGrNum(min(max(Cnt+x+y,0),15));
			}
		}
		if (Cnt + 11 + 8 <= 0)
		{
			FadeOutF = -1;
			Cnt = 0;
		}

	}
}

void Fade::Draw()
{
	
	for (int y = StartY; y < 9; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			Chip[y][x].Draw();
		}
	}
	
}

Fade::Fade(int StartY,int DrawAlpha,int R,int G,int B)
{
	ExRate = 4;
	this->StartY = StartY;
	//GrHandleData = Bank::Instance()->GetGrHandle(6);
	for (int y = StartY; y < 9; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			Chip[y][x].SetGrHandleData(Bank::Instance()->GetGrHandle(6));
			Chip[y][x].SetGrNum(0);
			Chip[y][x].SetExRate(4);
			Chip[y][x].SetDrawAlpha(DrawAlpha);
			Chip[y][x].SetXY(x * 16 * ExRate + 8 * ExRate, y * 16 * ExRate + 8 * ExRate);
			Chip[y][x].SetDrawRGB(R, G, B);
		}
	}
	Cnt = 0;
	FadeInF = 0;
	FadeOutF = 0;

}


Fade::~Fade()
{
}
