#include "Sprite.h"
#include "DxLib.h"
#include "Shake.h"

void Sprite::SetXY(double X, double Y)
{
	this->X = X;
	this->Y = Y;
}

double Sprite::GetX()
{
	return X;
}

double Sprite::GetY()
{
	return Y;
}

void Sprite::SetVX(double VX)
{
	this->VX = VX;
}
void Sprite::SetVY(double VY)
{
	this->VY = VY;
}
double Sprite::GetVX()
{
	return VX;
}

double Sprite::GetVY()
{
	return VY;
}

void Sprite::SetAX(double AX)
{
	this->AX = AX;
}

void Sprite::SetAY(double AY)
{
	this->AY = AY;
}

double Sprite::GetAX()
{
	return AX;
}

double Sprite::GetAY()
{
	return AY;
}

void Sprite::SetDrawRGB(int R, int G, int B)
{
	DrawR = R;
	DrawG = G;
	DrawB = B;
}

void Sprite::SetGrHandle(int GrHandle)
{
	this->GrHandle = GrHandle;
}

void Sprite::SetGrHandleData(int * GrHandleData)
{
	this->GrHandleData = GrHandleData;
}

void Sprite::SetGrNum(int GrNum)
{
	this->GrNum = GrNum;
}

void Sprite::SetAngle(double Rad)
{
	Angle = Rad;
}
void Sprite::SetExRate(double ExRate)
{
	this->ExRate = ExRate;
}
void Sprite::SetDrawAlpha(int DrawAlpha)
{
	this->DrawAlpha = DrawAlpha;
}
double Sprite::GetAngle()
{
	return Angle;
}
void Sprite::SetColSqr(int X1, int Y1, int X2, int Y2)
{
	ColSqr[0] = X1;
	ColSqr[1] = Y1;
	ColSqr[2] = X2;
	ColSqr[3] = Y2;
}
void Sprite::GetColSqr(int * X1, int * Y1, int * X2, int * Y2)
{
	*X1 = ColSqr[0];
	*Y1 = ColSqr[1];
	*X2 = ColSqr[2];
	*Y2 = ColSqr[3];
}
bool Sprite::CheckHitSp(Sprite * Sp)
{
	int AiteColSqr[4];
	Sp->GetColSqr(&AiteColSqr[0], &AiteColSqr[1], &AiteColSqr[2], &AiteColSqr[3]);
	int AiteX = Sp->GetX(), AiteY = Sp->GetY();
	////printfDx("%d",AiteColSqr[0]);
	//X
	if (X + ColSqr[0] * ExRate < AiteX + AiteColSqr[2] * ExRate && X + ColSqr[2] * ExRate > AiteX + AiteColSqr[0] * ExRate)
	{
		////printfDx("YHEE");
		//Y
		if (Y + ColSqr[1] * ExRate < AiteY + AiteColSqr[3] * ExRate && Y + ColSqr[3] * ExRate > AiteY + AiteColSqr[1] * ExRate)
		{
			return true;
		}
	}

	return false;
}
bool Sprite::CheckHitSpDeka(Sprite * Sp)
{
	int AiteColSqr[4];
	Sp->GetColSqr(&AiteColSqr[0], &AiteColSqr[1], &AiteColSqr[2], &AiteColSqr[3]);
	int AiteX = Sp->GetX(), AiteY = Sp->GetY();
	////printfDx("%d",AiteColSqr[0]);
	//X
	if (X + (ColSqr[0]-1) * ExRate < AiteX + (AiteColSqr[2]+1) * ExRate && X + (ColSqr[2]+1) * ExRate > AiteX + (AiteColSqr[0]-1) * ExRate)
	{
		////printfDx("YHEE");
		//Y
		if (Y + (ColSqr[1]-1) * ExRate < AiteY + AiteColSqr[3] * ExRate && Y + ColSqr[3] * ExRate > AiteY + (AiteColSqr[1]-1) * ExRate)
		{
			return true;
		}
	}

	return false;
}
void Sprite::SpAnim(int T1, int C1, int T2, int C2, int T3, int C3, int T4, int C4, int LoopNum)
{
	SpAnimNum = 4;
	SpAnimF = 1;
	SpAnimTimeCnt = 0;
	SpAnimLoopCnt = 0;

	SpAnimTime[0] = T1;
	SpAnimGrHandle[0] = C1;
	SpAnimTime[1] = T1 + T2;
	SpAnimGrHandle[1] = C2;
	SpAnimTime[2] = T1 + T2 + T3;
	SpAnimGrHandle[2] = C3;
	SpAnimTime[3] = T1 + T2 + T3 + T4;
	SpAnimGrHandle[3] = C4;
	SpAnimLoop = LoopNum;
	//SpAnimTimeSum = T1 + T2 + T3 + T4;

	GrNum = C1;
}

void Sprite::SpAnim(int T1, int C1, int T2, int C2, int T3, int C3, int T4, int C4, int T5,int C5,int T6,int C6,int LoopNum)
{
	SpAnimNum = 6;
	SpAnimF = 1;
	SpAnimTimeCnt = 0;
	SpAnimLoopCnt = 0;

	SpAnimTime[0] = T1;
	SpAnimGrHandle[0] = C1;
	SpAnimTime[1] = T1 + T2;
	SpAnimGrHandle[1] = C2;
	SpAnimTime[2] = T1 + T2 + T3;
	SpAnimGrHandle[2] = C3;
	SpAnimTime[3] = T1 + T2 + T3 + T4;
	SpAnimGrHandle[3] = C4;
	SpAnimTime[4] = T1 + T2 + T3 + T4 + T5;
	SpAnimGrHandle[4] = C5;
	SpAnimTime[5] = T1 + T2 + T3 + T4 + T5 + T6;
	SpAnimGrHandle[5] = C6;
	SpAnimLoop = LoopNum;
	//SpAnimTimeSum = T1 + T2 + T3 + T4;

	GrNum = C1;
}
void Sprite::SpAnim(int T1, int C1, int T2, int C2, int T3, int C3, int T4, int C4, int T5, int C5, int LoopNum)
{
	SpAnimNum = 5;
	SpAnimF = 1;
	SpAnimTimeCnt = 0;
	SpAnimLoopCnt = 0;

	SpAnimTime[0] = T1;
	SpAnimGrHandle[0] = C1;
	SpAnimTime[1] = T1 + T2;
	SpAnimGrHandle[1] = C2;
	SpAnimTime[2] = T1 + T2 + T3;
	SpAnimGrHandle[2] = C3;
	SpAnimTime[3] = T1 + T2 + T3 + T4;
	SpAnimGrHandle[3] = C4;
	SpAnimTime[4] = T1 + T2 + T3 + T4 + T5;
	SpAnimGrHandle[4] = C5;
	SpAnimLoop = LoopNum;
	//SpAnimTimeSum = T1 + T2 + T3 + T4;

	GrNum = C1;
}
void Sprite::SpAnim(int T1, int C1, int T2, int C2, int T3, int C3, int T4, int C4, int T5, int C5, int T6, int C6, int T7, int C7, int T8, int C8, int LoopNum)
{
	SpAnimNum = 8;
	SpAnimF = 1;
	SpAnimTimeCnt = 0;
	SpAnimLoopCnt = 0;

	SpAnimTime[0] = T1;
	SpAnimGrHandle[0] = C1;
	SpAnimTime[1] = T1 + T2;
	SpAnimGrHandle[1] = C2;
	SpAnimTime[2] = T1 + T2 + T3;
	SpAnimGrHandle[2] = C3;
	SpAnimTime[3] = T1 + T2 + T3 + T4;
	SpAnimGrHandle[3] = C4;
	SpAnimTime[4] = T1 + T2 + T3 + T4 + T5;
	SpAnimGrHandle[4] = C5;
	SpAnimTime[5] = T1 + T2 + T3 + T4 + T5 + T6;
	SpAnimGrHandle[5] = C6;
	SpAnimTime[6] = T1 + T2 + T3 + T4 + T5 + T6 + T7;
	SpAnimGrHandle[6] = C7;
	SpAnimTime[7] = T1 + T2 + T3 + T4 + T5 + T6 + T7 + T8;
	SpAnimGrHandle[7] = C8;
	SpAnimLoop = LoopNum;
	//SpAnimTimeSum = T1 + T2 + T3 + T4;

	GrNum = C1;
}

void Sprite::SpAnim(int T1, int C1, int T2, int C2, int T3, int C3, int T4, int C4, int T5, int C5, int T6, int C6, int T7, int C7, int T8, int C8,int T9,int C9,int T10,int C10,int T11,int C11, int LoopNum)
{
	SpAnimNum = 11;
	SpAnimF = 1;
	SpAnimTimeCnt = 0;
	SpAnimLoopCnt = 0;

	SpAnimTime[0] = T1;
	SpAnimGrHandle[0] = C1;
	SpAnimTime[1] = T1 + T2;
	SpAnimGrHandle[1] = C2;
	SpAnimTime[2] = T1 + T2 + T3;
	SpAnimGrHandle[2] = C3;
	SpAnimTime[3] = T1 + T2 + T3 + T4;
	SpAnimGrHandle[3] = C4;
	SpAnimTime[4] = T1 + T2 + T3 + T4 + T5;
	SpAnimGrHandle[4] = C5;
	SpAnimTime[5] = T1 + T2 + T3 + T4 + T5 + T6;
	SpAnimGrHandle[5] = C6;
	SpAnimTime[6] = T1 + T2 + T3 + T4 + T5 + T6 + T7;
	SpAnimGrHandle[6] = C7;
	SpAnimTime[7] = T1 + T2 + T3 + T4 + T5 + T6 + T7 + T8;
	SpAnimGrHandle[7] = C8;
	SpAnimTime[8] = T1 + T2 + T3 + T4 + T5 + T6 + T7 + T8 + T9;
	SpAnimGrHandle[8] = C9;
	SpAnimTime[9] = T1 + T2 + T3 + T4 + T5 + T6 + T7 + T8 + T9 + T10;
	SpAnimGrHandle[9] = C10;
	SpAnimTime[10] = T1 + T2 + T3 + T4 + T5 + T6 + T7 + T8 + T9 + T10 + T11;
	SpAnimGrHandle[10] = C11;
	SpAnimLoop = LoopNum;
	//SpAnimTimeSum = T1 + T2 + T3 + T4;

	GrNum = C1;
}

void Sprite::SpAnimStop()
{
	SpAnimF = 0;
}

void Sprite::SpAnimUpdate()
{
	////printfDx("\n[[[YHEEEE]]]\n");
	if (SpAnimF == 1)
	{
		for (int i = 0; i < SpAnimNum; i++)
		{
			if (SpAnimTimeCnt == SpAnimTime[i])
			{
				if (i == SpAnimNum-1)
				{
					if (SpAnimLoopCnt != SpAnimLoop-1)
					{
						GrNum = SpAnimGrHandle[(i + 1) % SpAnimNum];
						SpAnimTimeCnt = 0;
						SpAnimLoopCnt++;
					}
					else
					{
						SpAnimF = 0;
					}
				}
				else
				{
					GrNum = SpAnimGrHandle[(i + 1) % SpAnimNum];
				}
			}
		}
		SpAnimTimeCnt++;
	}
}

int Sprite::GetSpAnimF()
{
	return SpAnimF;
}

int Sprite::GetSpAnimTimeCnt()
{
	return SpAnimTimeCnt;
}

void Sprite::SpAnimColor(int R1, int G1, int B1, int Time, int R2, int G2, int B2)
{
	SpAnimColorF = 1;

	SpAnimColorR[0] = R1;
	SpAnimColorG[0] = G1;
	SpAnimColorB[0] = B1;
	SpAnimColorTime = Time;
	SpAnimColorCnt = 0;
	SpAnimColorR[1] = R2;
	SpAnimColorG[1] = G2;
	SpAnimColorB[1] = B2;

	DrawR = R1;
	DrawG = G1;
	DrawB = B1;
}

void Sprite::SpAnimColorUpdate()
{
	if (SpAnimColorF == 1)
	{
		if (SpAnimColorCnt++ < SpAnimColorTime)
		{
			DrawR = SpAnimColorR[0] + (SpAnimColorR[1] - SpAnimColorR[0])*((double)SpAnimColorCnt / SpAnimColorTime);
			DrawG = SpAnimColorG[0] + (SpAnimColorG[1] - SpAnimColorG[0])*((double)SpAnimColorCnt / SpAnimColorTime);
			DrawB = SpAnimColorB[0] + (SpAnimColorB[1] - SpAnimColorB[0])*((double)SpAnimColorCnt / SpAnimColorTime);
		}
		else
		{
			SpAnimColorF = 0;
			DrawR = SpAnimColorR[1];
			DrawG = SpAnimColorG[1];
			DrawB = SpAnimColorB[1];
		}
	}
}

void Sprite::SpAnimAlpha(int Value1, int Time, int Value2)
{
	SpAnimAlphaF = 1;
	SpAnimAlphaCnt = 0;

	SpAnimAlphaValue[0] = Value1;
	SpAnimAlphaTime = Time;
	SpAnimAlphaValue[1] = Value2;

	DrawAlpha = Value1;
}

void Sprite::SpAnimAlphaStop()
{
	SpAnimAlphaF = 0;

}




void Sprite::SpAnimAlphaUpdate()
{
	if (SpAnimAlphaF == 1)
	{
		if (SpAnimAlphaCnt++ < SpAnimAlphaTime)
		{
			DrawAlpha = SpAnimAlphaValue[0] + (SpAnimAlphaValue[1] - SpAnimAlphaValue[0])*((double)SpAnimAlphaCnt / SpAnimAlphaTime);
		}
		else
		{
			DrawAlpha = SpAnimAlphaValue[1];
			SpAnimAlphaF = 0;
		}
	}
}

void Sprite::DrawFuchi()
{
	SetDrawBright(250, 240, 0);
	//SetDrawBlendMode(DX_BLENDMODE_ADD, 150);

	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			DrawRotaGraph((int)X + Shake::Instance()->GetX()+x*ExRate, (int)Y + Shake::Instance()->GetY()+y*ExRate, ExRate, Angle, GrHandleData[GrNum+32], 1);
		}
	}
	SetDrawBright(DrawR, DrawG, DrawB);
	SetDrawBright(255,255,255);

}

void Sprite::DrawFuchiEffect()
{
	FuchiEffectCnt++;
	if (FuchiEffectCnt > 30)
	{
		FuchiEffectF = 0;
		//if (FuchiByougaF == -11)
		//	FuchiByougaF = 1;
	}
	SetDrawBright(250, 240, 0);
	FuchiEffectV *= 0.85;
	FuchiEffectX += FuchiEffectV;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, FuchiEffectV*80);
	double exrate = (ExRate + FuchiEffectX);
	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			DrawRotaGraph((int)X + Shake::Instance()->GetX() + x * exrate, (int)Y + Shake::Instance()->GetY() + y * exrate, ExRate, Angle, GrHandleData[GrNum + 32], 1);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	SetDrawBright(255, 255, 255);

}

int Sprite::GetFuchiByougaF()
{
	return FuchiByougaF;
}

void Sprite::SetFuchiByougaF(int FuchiByougaF)
{
	this->FuchiByougaF = FuchiByougaF;
}

void Sprite::SetNegaF(bool NegaF)
{
	this->NegaF = NegaF;
}

bool Sprite::GetNegaF()
{
	return NegaF;
}

void Sprite::Update()
{
	SpAnimUpdate();
	SpAnimColorUpdate();
	SpAnimAlphaUpdate();
}


void Sprite::Draw()
{
	switch (FuchiByougaF)
	{
	case 1:
		DrawFuchi();
		break;
	case -1:
		FuchiEffectF = 1;
		FuchiEffectCnt = 0;
		FuchiEffectX = 0;
		FuchiEffectV = 2;
		FuchiByougaF = -2;
		break;
	case 10:
		FuchiEffectF = 1;
		FuchiEffectCnt = 0;
		FuchiEffectX = 0;
		FuchiEffectV = 2;
		FuchiByougaF = 11;
		break;
	case 11:
		DrawFuchi();
		break;
	}
	if (FuchiEffectF >= 1)
	{
		DrawFuchiEffect();
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, DrawAlpha);
	SetDrawBright(DrawR, DrawG, DrawB);
	if (NegaF == 1)
		SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
	DrawRotaGraph(((int)X + Shake::Instance()->GetX()), ((int)Y + Shake::Instance()->GetY()), ExRate, Angle, GrHandleData[GrNum], 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	SetDrawBright(255,255,255);

}

Sprite::Sprite()
{
	X = 0;
	Y = 0;
	VY = 0;
	ExRate = 1;
	Angle = 0;
	SpAnimColorF = 0;
	SpAnimAlphaF = 0;
	DrawR = 255;
	DrawG = 255;
	DrawB = 255;
	SpAnimF = 0;
	GrNum = 0;
	FuchiByougaF = 0;
	FuchiEffectF = 0;
	DrawAlpha = 255;
	NegaF = 0;
}


Sprite::~Sprite()
{
	////printfDx("@@@@@@@");
}
