#include "Frog.h"
#include "DxLib.h"
#include "Bank.h"
#include "Mouse.h"
#include "MainGame.h"
#include <math.h>
#include "EffectMgr.h"

bool Frog::KasanatteruMouse()
{
	int mx = Mouse::Instance()->GetX();
	int my = Mouse::Instance()->GetY();

	if (MoveF == 0 && mx > X - 8 * 4 && mx<X + 8 * 4 && my>Y - 8 * 4 && my < Y + 8 * 4)
	{
		if (FuchiByougaF == 0)
			FuchiByougaF = 1;
		//ƒNƒŠƒbƒN‚³‚ê‚½
		if ((Mouse::Instance()->GetInputSyunkan()  & MOUSE_INPUT_LEFT) != 0)
		{
			(*Tesuu)++;
			Bank::Instance()->PlaySe(3);
			MoveStart();
			FuchiByougaF = -1;
		}
		return 1;

	}
	else
	{
		FuchiByougaF = 0;
	}
	return 0;
}


void Frog::Update(SceneBase * MG, int Itr)
{
	SitaVY = 0;
	SitaVX = 0;
	for (int i = 0; i < ((MainGame*)MG)->Enemy.size(); i++)
		//for (int i = ((MainGame*)MG)->Enemy.size() - 1; i >= 0; i--)
	{
		if (i == Itr)
			continue;
		EnemyBase* Aite = ((MainGame*)MG)->Enemy[i];
		//‰E‚É“G
		if (MigiMuki == 1 && CheckHitSpDeka(Aite) == 1 && X < Aite->GetX() && abs(Y - Aite->GetY())<14 * ExRate)
		{
			while (CheckHitSpDeka(Aite) == 1 && X < Aite->GetX() && abs(Y - Aite->GetY()) < 14 * ExRate)
			{
				//if (TurnStopCnt == 0)
				if (VX != 0)
					X--;
				else
				{
					////printfDx("B");
					Aite->SetXY((Aite->GetX() + 1), Aite->GetY());
				}
			}

			//if (GetMoveF() == 1)
			{
				//SpAnim(10, 13, 10, 12, 10, 12, 18, 4, 1);
				MigiMuki = 0;
				VX = 0;
				if (MoveF == 1)
					TurnStopCnt = 1;
				if (Aite->GetEnemyType() == 0 && Aite->GetMoveF()==1)
				{
					//Aite->SetMoveF(1);
					Aite->SetMigiMuki(1);
					Aite->SetTurnStopCnt(1);
					Aite->SetVX(0);
					Aite->SpAnim(10, 5, 10, 4, 10, 4, 18, 12, 1);
				}
			}

			//MoveF = 1;
		}

		//¶‚É“G
		if (MigiMuki == 0 && CheckHitSpDeka(Aite) == 1 && X > Aite->GetX() && abs(Y - Aite->GetY())<14 * ExRate)
		{
			while (CheckHitSpDeka(Aite) == 1 && X > Aite->GetX() && abs(Y - Aite->GetY()) < 14 * ExRate)
			{
				//if (TurnStopCnt == 0)
				if(VX!=0)
					X++;
				else
				{
					////printfDx("B");
					Aite->SetXY((Aite->GetX() - 1), Aite->GetY());
				}
			}

			//if (GetMoveF() == 1)
			{
				//SpAnim(10, 5, 10, 4, 10, 4, 18, 12, 1);
				MigiMuki = 1;
				VX = 0;
				if (MoveF == 1)
					TurnStopCnt = 1;
				if (Aite->GetEnemyType() == 0 && Aite->GetMoveF() == 1)
				{
					Aite->SetMoveF(1);
					Aite->SetMigiMuki(0);
					Aite->SetTurnStopCnt(1);
					Aite->SetVX(0);
					Aite->SpAnim(10, 13, 10, 12, 10, 12, 18, 4, 1);
				}
			}

			//MoveF = 1;
		}

		//‰º‚É“G‚ª‚¢‚é
		if (CheckHitSpDeka(Aite) == 1 && Y < Aite->GetY() && abs(X - Aite->GetX())<13 * ExRate)
		{
			StandF = 1;
			//TurnStopCnt = 1;
			VX = 0;
			VY = 0;
			MoveF = 0;
			Y = (int)Y;
			while (CheckHitSpDeka(Aite) == 1 && Y < Aite->GetY() && abs(X - Aite->GetX())<13 * ExRate)
			{
				Y--;
			}
			Y++;
			SitaVY = Aite->GetVY() + Aite->GetSitaVY();
			if (TurnStopCnt == 0)
				SitaVX = Aite->GetVX() + Aite->GetSitaVX();

			//VY = Aite->GetVY();
			//VX = Aite->GetVX();

		}
		else
		{
			//‰º‚É’n–Ê‚ª–³‚¢
			if (Bg->GetChip(0, X + AtariX[0] * ExRate + 1, Y + AtariY[1] * ExRate) == -1 && Bg->GetChip(0, X + AtariX[1] * ExRate - 1, Y + AtariY[1] * ExRate) == -1)
			{
				StandF = 0;
			}
		}
	}

	if (CheckUp(MG,Itr)==1)
	{
		//printfDx("‚©‚×");
		//while (CheckUpGround())
			//Y++;
		//Y += 5;
		VY = 1;
		SitaVY = 0;
	}
	//printfDx("StandF=%d", StandF);
	KasanatteruMouse();

}

void Frog::Update()
{
	Sprite::Update();
	if (CheckUpGround() == 1)
	{
		while (CheckUpGround())
		{
			////printfDx("kabe");
			Y++;
		}
		Y--;
		VY = 1;
		SitaVY = 0;
	}

	X += (VX + SitaVX);

	//‰E‚É’n–Ê‚ª‚ ‚é
	if (Bg->GetChip(0, X + AtariX[1] * ExRate - 1, Y + AtariY[0] * ExRate + 1) != -1 || Bg->GetChip(0, X + AtariX[1] * ExRate - 1, Y + AtariY[1] * ExRate - 1) != -1)
	{
		//‚ß‚èž‚Ý–hŽ~
		while (Bg->GetChip(0, X + AtariX[1] * ExRate - 1, Y + AtariY[0] * ExRate + 1) != -1 || Bg->GetChip(0, X + AtariX[1] * ExRate - 1, Y + AtariY[1] * ExRate - 1) != -1)
		{
			X--;
		}
		//X -= 4;
		MigiMuki = 0;
		//VX = 0;
		SitaVX = 0;
		//if (MoveF == 1)
		{
			//SpAnim(10, 13, 10, 12, 10, 12, 18, 4, 1);
			//TurnStopCnt = 1;
			//MoveF = 1;
		}
	}


	//¶‚É’n–Ê‚ª‚ ‚é
	if (Bg->GetChip(0, X + AtariX[0] * ExRate, Y + AtariY[0] * ExRate + 1) != -1 || Bg->GetChip(0, X + AtariX[0] * ExRate, Y + AtariY[1] * ExRate - 1) != -1)
	{
		//‚ß‚èž‚Ý–hŽ~
		while (Bg->GetChip(0, X + AtariX[0] * ExRate, Y + AtariY[0] * ExRate + 1) != -1 || Bg->GetChip(0, X + AtariX[0] * ExRate, Y + AtariY[1] * ExRate - 1) != -1)
		{
			X++;
		}
		MigiMuki = 1;
		//VX = 0;
		SitaVX = 0;
		//if (MoveF == 1)
		{
			//SpAnim(10, 5, 10, 4, 10, 4, 18, 12, 1);
			//TurnStopCnt = 1;
			//MoveF = 1;
		}
	}

	if (TurnStopCnt > 0)
	{
		TurnStopCnt++;
		if (TurnStopCnt >= 50)
		{
			TurnStopCnt = 0;
			if (MoveF == 1)
			{
				if (MigiMuki == 1)
				{
					//SpAnim(10, 8, 10, 9, 10, 10, 10, 11, -1);
					//VX = 1;
				}
				else
				{
					//SpAnim(10, 0, 10, 1, 10, 2, 10, 3, -1);
					//VX = -1;
				}
			}
		}
	}



	if (StandF == 0)
	{
		VY += 0.1;
		if (VY > 5)
			VY = 5;
		Y += (VY + SitaVY);
	}


	//‰º‚É’n–Ê‚ª‚ ‚é
	if (Bg->GetChip(0, X + AtariX[0] * ExRate + 1, Y + AtariY[1] * ExRate) != -1 || Bg->GetChip(0, X + AtariX[1] * ExRate - 1, Y + AtariY[1] * ExRate) != -1)
	{
		MoveF = 0;
		VX = 0;
		if (StandF == 0)
		{
			SpAnim(180 + GetRand(240), 0, 5, 1, 16, 2, 5, 1, 8, 0, 5, 1, 12, 2, 5, 1, 0);
			StandF = 1;
			Y = (int)Y;
			//‚ß‚èž‚Ý–hŽ~
			while (Bg->GetChip(0, X + AtariX[0] * ExRate + 1, Y + AtariY[1] * ExRate) != -1 || Bg->GetChip(0, X + AtariX[1] * ExRate - 1, Y + AtariY[1] * ExRate) != -1)
			{
				Y--;
			}
			Y++;
		}
	}
	else
	{
		//ƒJƒGƒ‹‚É‚ÍŠÖŒW‚È‚¢H
		
		if (StandF == 1)
		{
			StandF = 0;
			VY = 0;
		}
		
	}

	if (CheckUpGround() == 1)
	{
		while (CheckUpGround())
		{
			////printfDx("kabe");
			Y++;
		}
		//Y--;
		VY = 1;
		SitaVY = 0;
	}

}

void Frog::Draw()
{
	Sprite::Draw();

}

void Frog::SetBgMgr(BgMgr * Bg)
{
	this->Bg = Bg;

}

void Frog::MoveStart()
{
	MoveF = 1;
	TurnStopCnt = 0;
	MigiMuki = 0;
	VX = -1.15;
	VY = -5.5;
	Y += VY;
	StandF = 0;
	SpAnim(10, 8, 10, 9, 10, 8, 10, 9, 0);


}


Frog::Frog(int BgX, int BgY, BgMgr * Bg)
{
	EnemyType = 1;
	ExRate = EXRATE;
	X = BgX * 16 * ExRate + 8 * ExRate + Bg->GetX();
	Y = BgY * 16 * ExRate + 8 * ExRate + Bg->GetY();
	this->Bg = Bg;
	HitType = ABLE_TO_STEP_ON;
	StandF = 0;
	MigiMuki = 0;
	VX = 0;
	SitaVY = 0;
	SitaVX = 0;
	MoveF = 0;
	TurnStopCnt = 0;
	GrHandleData = Bank::Instance()->GetGrHandle(7);
	GrNum = 4;

	SpAnim(180+GetRand(240), 0, 5, 1, 16, 2, 5, 1, 8, 0, 5, 1, 12, 2, 5, 1, 0);
	//SpAnim(60 * (10 + GetRand(600) / 10.0), 4, 60 * (3 + GetRand(50) / 10.0), 16, 60 * (3 + GetRand(50) / 10.0), 17, 40, 18, 40, 19, 40, 20, 1);

	SetColSqr(AtariX[0], AtariY[0], AtariX[1], AtariY[1]);
}

Frog::~Frog()
{
	EffectMgr::Instance()->SetEffect(X, Y, GrHandleData, STOP, 30, 5, 5, 60, 6, 60, 6, 60, 6, 1);

}
