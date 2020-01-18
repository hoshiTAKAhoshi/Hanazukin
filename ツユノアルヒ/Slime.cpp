#include "Slime.h"
#include "DxLib.h"
#include "Bank.h"
#include "Mouse.h"
#include "MainGame.h"
#include "EffectMgr.h"
#include <math.h>
#include "WarpMan.h"

bool Slime::KasanatteruMouse()
{
	int mx = Mouse::Instance()->GetX();
	int my = Mouse::Instance()->GetY();

	//if (MoveF == 0 && mx > X - 8 * 4 && mx<X + 8 * 4 && my>Y - 8 * 4 && my < Y + 8 * 4)
	if (mx > X - 8 * 4 && mx<X + 8 * 4 && my>Y - 8 * 4 && my < Y + 8 * 4)
	{
		if (FuchiByougaF == 0)
			FuchiByougaF = 1;
		//ƒNƒŠƒbƒN‚³‚ê‚½
		if ((Mouse::Instance()->GetInputSyunkan()  & MOUSE_INPUT_LEFT) != 0)
		{
			if (MoveF == 0)
			{
				(*Tesuu)++;
				Bank::Instance()->PlaySe(6);
				MoveStart();
				FuchiByougaF = 10;
			}
			else
			{
				(*Tesuu)++;
				Bank::Instance()->PlaySe(6);
				MoveStop();
				FuchiByougaF = 10;
			}
			//return 1;
		}
		return 1;

	}
	else
	{
		FuchiByougaF = 0;
	}
	return 0;
}

void Slime::Update(SceneBase * MG,int Itr)
{
	SitaVY = 0;
	SitaVX = 0;
	for (int i = 0; i < ((MainGame*)MG)->Enemy.size(); i++)
		//for (int i = ((MainGame*)MG)->Enemy.size() - 1; i >= 0; i--)
	{
		if (i == Itr)
			continue;
		EnemyBase* Aite = ((MainGame*)MG)->Enemy[i];
		//‰º‚É“G‚ª‚¢‚é
		if (CheckHitSpDeka(Aite) == 1 && Y < Aite->GetY() && abs(X - Aite->GetX())<13 * ExRate)
		{
			StandF = 1;
			//Y = (int)Y;
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
			/*
			//‰º‚É’n–Ê‚ª–³‚¢
			if (Bg->GetChip(0, X + AtariX[0] * ExRate + 1, Y + AtariY[1] * ExRate) == -1 && Bg->GetChip(0, X + AtariX[1] * ExRate - 1, Y + AtariY[1] * ExRate) == -1)
			{
			StandF = 0;
			}
			*/
		}
		//‰E‚É“G
		if (MigiMuki==1 && CheckHitSpDeka(Aite) == 1 && X < Aite->GetX() && abs(Y - Aite->GetY())<14 * ExRate)
		{
			while (CheckHitSpDeka(Aite) == 1 && X < Aite->GetX() && abs(Y - Aite->GetY()) < 14 * ExRate)
			{
				if (TurnStopCnt == 0)
				{
					X--;
				}
				else
				{
					Aite->SetXY((Aite->GetX() + 1), Aite->GetY());
				}
				/*
				//¶‚É’n–Ê‚ª‚È‚¢
				if (Bg->GetChip(0, X-1 + AtariX[0] * ExRate, Y + AtariY[0] * ExRate + 1) == -1 || Bg->GetChip(0, X-1 + AtariX[0] * ExRate, Y + AtariY[1] * ExRate - 1) == -1)
					X -= 1;
				else
				{
					int Aru = 0;
					for (int j = 0; j < ((MainGame*)MG)->Enemy.size(); j++)
					{
						if (j == Itr)
							continue;
						EnemyBase* At = ((MainGame*)MG)->Enemy[j];
						if (CheckHitSpDeka(At) == 1 && X > At->GetX() && abs(Y - At->GetY())<14 * ExRate)
							Aru = 1;
					}
					if (Aru == 0)
						X -= 1;
					else
						Aite->SetXY((Aite->GetX() + 1), Aite->GetY());
				}
				*/
			}

			//if (GetMoveF() == 1)
			{
				VX = 0;
				//if (MoveF == 1)
				{
					SpAnim(10, 13, 10, 12, 10, 12, 18, 4, 1);
					MigiMuki = 0;
					TurnStopCnt = 1;
				}
				Aite->SetTurnStopCnt(1);
				Aite->SetVX(0);
				//if (Aite->GetEnemyType() == 0 && Aite->GetMoveF() == 1)
				{
					Aite->SetMoveF(1);
					Aite->SetMigiMuki(1);
					Aite->SetTurnStopCnt(1);
					Aite->SpAnim(10, 5, 10, 4, 10, 4, 18, 12, 1);
				}
			}

			MoveF = 1;
		}

		//¶‚É“G
		if (MigiMuki==0 && CheckHitSpDeka(Aite) == 1 && X > Aite->GetX() && abs(Y - Aite->GetY())<14 * ExRate)
		{
			while (CheckHitSpDeka(Aite) == 1 && X > Aite->GetX() && abs(Y - Aite->GetY()) < 14 * ExRate)
			{
				if (TurnStopCnt== 0)
				{
					//printfDx("B");
					X++;
				}
				else
				{
					//printfDx("F");
					Aite->SetXY((Aite->GetX() - 1), Aite->GetY());
				}
				/*
				//‰E‚É’n–Ê‚ª‚È‚¢
				if (Bg->GetChip(0, X + 1 + AtariX[1] * ExRate - 1, Y + AtariY[0] * ExRate + 1) == -1 || Bg->GetChip(0, X + 1 + AtariX[1] * ExRate - 1, Y + AtariY[1] * ExRate - 1) == -1)
					X += 1;
				else
				{
					int Aru = 0;
					for (int j = 0; j < ((MainGame*)MG)->Enemy.size(); j++)
					{
						if (j == Itr)
							continue;
						EnemyBase* At = ((MainGame*)MG)->Enemy[j];
						if (CheckHitSpDeka(At) == 1 && X < At->GetX() && abs(Y - At->GetY()) < 14 * ExRate)
							Aru = 1;
					}
					if (Aru == 0)
						X += 1;
					else
						Aite->SetXY((Aite->GetX() - 1), Aite->GetY());
					//Aite->SetXY((Aite->GetX() - 1), Aite->GetY());
				}
				*/
			}
			
			//if (GetMoveF() == 1)
			{
				VX = 0;
				//if (MoveF == 1)
				{
					SpAnim(10, 5, 10, 4, 10, 4, 18, 12, 1);
					MigiMuki = 1;
					TurnStopCnt = 1;
				}
				Aite->SetTurnStopCnt(1);
				Aite->SetVX(0);
				//if (Aite->GetEnemyType() == 0 && Aite->GetMoveF() == 1)
				{
					Aite->SetMoveF(1);
					Aite->SetMigiMuki(0);
					Aite->SetTurnStopCnt(1);
					Aite->SpAnim(10, 13, 10, 12, 10, 12, 18, 4, 1);
				}
			}

			MoveF = 1;
		}

	}

	//KasanatteruMouse();
}

void Slime::Update()
{
	Sprite::Update();

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
		VX = 0;
		SitaVX = 0;
		//if (MoveF == 1)
		{
			SpAnim(10, 13, 10, 12, 10, 12, 18, 4, 1);
			TurnStopCnt = 1;
			HitKabeF = 1;
			MoveF = 1;
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
		VX = 0;
		SitaVX = 0;
		//if (MoveF == 1)
		{
			SpAnim(10, 5, 10, 4, 10, 4, 18, 12, 1);
			TurnStopCnt = 1;
			HitKabeF = 1;
			MoveF = 1;
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
				HitKabeF = 0;
				if (MigiMuki == 1)
				{
					SpAnim(10, 8, 10, 9, 10, 10, 10, 11, -1);
					VX = 1;
				}
				else
				{
					SpAnim(10, 0, 10, 1, 10, 2, 10, 3, -1);
					VX = -1;
				}
			}
		}
	}



	if (StandF == 0)
	{
		VY += 0.1;
		if (VY > 5)
			VY = 5;
		Y += VY;
	}


	//‰º‚É’n–Ê‚ª‚ ‚é
	if (Bg->GetChip(0, X + AtariX[0] * ExRate + 1, Y + AtariY[1] * ExRate) != -1 || Bg->GetChip(0, X + AtariX[1] * ExRate - 1, Y + AtariY[1] * ExRate) != -1)
	{
		if (StandF == 0)
		{
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
		if (StandF == 1)
		{
			StandF = 0;
			VY = 0;
		}
	}

}



void Slime::Draw()
{
	Sprite::Draw();
}

void Slime::SetBgMgr(BgMgr * Bg)
{
	this->Bg = Bg;
}

void Slime::MoveStart()
{
	MoveF = 1;
	TurnStopCnt = 0;
	//MigiMuki = 0;
	if (MigiMuki == 1)
	{
		VX = 1;
		SpAnim(10, 8, 10, 9, 10, 10, 10, 11, -1);
	}
	else
	{
		VX = -1;
		SpAnim(10, 0, 10, 1, 10, 2, 10, 3, 0);
	}
}

void Slime:: MoveStop()
{
	MoveF = 0;
	//TurnStopCnt = 0;
	//MigiMuki = 0;
	VX = 0;
	//SpAnim(10, 0, 10, 1, 10, 2, 10, 3, 0);
	SpAnimStop();
	if (MigiMuki == 1)
	{
		GrNum = 12;
	}
	else
	{
		GrNum = 4;
	}
}


Slime::Slime(int BgX, int BgY,BgMgr* Bg)
{
	EnemyType = 0;
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
	HitKabeF = 0;
	TurnStopCnt = 0;
	GrHandleData = Bank::Instance()->GetGrHandle(3);
	GrNum = 4;

	SpAnim(60 * (10 + GetRand(600) / 10.0), 4, 60 * (3 + GetRand(50) / 10.0), 16, 60 * (3 + GetRand(50) / 10.0), 17, 40, 18, 40, 19, 40, 20, 1);
	
	SetColSqr(AtariX[0], AtariY[0], AtariX[1], AtariY[1]);

}

Slime::~Slime()
{
	//printfDx("DESTRACT");
	if (MigiMuki == 0)
		EffectMgr::Instance()->SetEffect(X, Y, GrHandleData, STOP, 30, 5, 21, 60, 22, 60, 22, 60, 22, 1);
	else
		EffectMgr::Instance()->SetEffect(X, Y, GrHandleData, STOP, 30, 5, 21+8, 60, 22+8, 60, 22, 60, 22, 1);
}
