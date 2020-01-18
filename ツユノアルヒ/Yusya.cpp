#include "Yusya.h"
#include "Bank.h"
#include "Mouse.h"
#include "Shake.h"
#include "Boss.h"
#include "DxLib.h"

void Yusya::Move()
{
	X += VX;
	if (FuttobiF == 1)
	{
		VY += 0.1;
		Y += VY;
		if (Y >= 6.5 * 16 * 4)
		{
			Y = 6.5 * 16 * 4;
			FuttobiF = 0;
		}
	}
}

void Yusya::MoveStart()
{
	MoveF = 1;
	VX = 1;
	SpAnim(20, 1, 20, 2, 20, 3, 20, 2, 0);
}

void Yusya::Atack()
{
	AtackCnt = 1;
	VX = 0;
	SpAnim(6, 8, 6, 9, 10, 10, 6, 0, 1);

}

void Yusya::UpdateBoss1()
{
	Sprite::Update();
	int mx = Mouse::Instance()->GetX();
	int my = Mouse::Instance()->GetY();

	if (mx > 2*16 * ExRate && mx<X + 24 * ExRate &&my>Y - 16 * ExRate && my < Y + 32 * ExRate)
	{
		if ((FuchiByougaF == 0 || FuchiByougaF==-2)&& AtackCnt==0)
			FuchiByougaF = 1;
		//クリックされた
		if ((Mouse::Instance()->GetInputSyunkan()  & MOUSE_INPUT_LEFT) != 0)
		{
			if (MoveF == 0)
			{
				////printfDx("うごけ");
				Bank::Instance()->PlaySe(6);
				MoveStart();
				FuchiByougaF = 10;
			}
			else
			{
				////printfDx("とまれ");
				if (AtackCnt == 0)
				{
					Bank::Instance()->PlaySe(6);
					Bank::Instance()->PlaySe(15);
					Atack();
					FuchiByougaF = -1;
				}
				
			}
		}
	}
	else
	{
		FuchiByougaF = 0;
	}
	Move();
	if (AtackCnt > 0)
	{
		AtackCnt++;
		if (AtackCnt >= 30)
		{
			if (FuttobiF == 0)
			{
				SpAnim(20, 1, 20, 2, 20, 3, 20, 2, 0);
				VX = 1;
				AtackCnt = 0;
			}
		}
	}


	//ボスと剣の当たり判定
	if (AtackCnt == 7)
	{
		if (X >= 7.8 * 16 * 4)
		{
			int bHp = ((Boss*)BossKun)->GetHp();
			if (bHp > 1)
			{
				VX = -4;
				VY = -4.4;
				FuttobiF = 1;
				Shake::Instance()->Start(30, 10);
				Bank::Instance()->PlaySe(4);
				((Boss*)BossKun)->SpAnimColor(255, 0, 0, 30, 255, 255, 255);
			}
			else
			{
				Gekiha = 1;
			}
			((Boss*)BossKun)->SetHp(bHp - 1);
			((Boss*)BossKun)->SetFireCnt(-60);
			((Boss*)BossKun)->SetGrNum(0);

			//printfDx("atari[[%d]]", ((Boss*)BossKun)->GetHp());
		}
	}

	//ボスとの当たり判定
	if (X >= 8.8 * 16 * 4)
	{
		//printfDx("MISS");

	}

}

void Yusya::NottoriInit()
{
	NottoriCnt = 0;
	SpAnim(20, 25, 20, 26, 20, 27, 20, 26, 0);
	VX = -1;
	NottorareF = 1;
}

void Yusya::UpdateNottori()
{
	Sprite::Update();
	X += VX;
	if (X <= 2.5 * 16 * 4-2*4)
	{
		VX = 0;
		X = 2.5 * 16 * 4-2*4;
	}
	NottoriCnt++;
	if (NottoriCnt == 60)
	{
		SpAnim(6, 28, 6, 29, 10, 30, 6, 24, 1);
		Bank::Instance()->PlaySe(15);
	}
	if (NottoriCnt == 60+23)
	{
		SpAnim(20, 25, 20, 26, 20, 27, 20, 26, 0);
	}
	if (NottoriCnt == 180)
	{
		NottoriCnt = 0;
	}
}

void Yusya::UpdateTaore()
{
	int mx = Mouse::Instance()->GetX();
	int my = Mouse::Instance()->GetY();

	if (mx > X - 8 * ExRate && mx<X + 8 * ExRate &&my>Y - 8 * ExRate && my < Y + 8 * ExRate)
	{
		if ((FuchiByougaF == 0 || FuchiByougaF == -2)&& NottorareF==1)
			FuchiByougaF = 1;
		//クリックされた
		if ((Mouse::Instance()->GetInputSyunkan()  & MOUSE_INPUT_LEFT) != 0)
		{
			if (NottorareF==1)
			{
				////printfDx("うごけ");
				Bank::Instance()->PlaySe(6);
				GrNum = 31 - 8;
				NottorareF = 0;
				FuchiByougaF = -1;
			}
		}
	}
	else
	{
		FuchiByougaF = 0;
	}

}

void Yusya::Update()
{
	Sprite::Update();

}

void Yusya::Draw()
{
	Sprite::Draw();
}

void Yusya::SetBgMgr(BgMgr * Bg)
{
	this->Bg = Bg;
}

void Yusya::SetBgXY(int BgX, int BgY)
{
	X = BgX * 16 * ExRate + 8 * ExRate + Bg->GetX();
	Y = BgY * 16 * ExRate + 8 * ExRate + Bg->GetY();
}

void Yusya::SetBoss(EnemyBase * BossKun)
{
	this->BossKun = BossKun;
}

int Yusya::GetAtackCnt()
{
	return AtackCnt;
}

int Yusya::GetGekiha()
{
	return Gekiha;
}

int Yusya::GetNottoriCnt()
{
	return NottoriCnt;
}

bool Yusya::GetNottorareF()
{
	return NottorareF;
}

void Yusya::Init()
{
	GrNum = 0;
	SpAnimStop();
	VX = 0;
	VY = 0;
	MoveF = 0;
	AtackCnt = 0;
	FuttobiF = 0;
	Gekiha = 0;
}

Yusya::Yusya()
{
	ExRate = 4;
	GrHandleData = Bank::Instance()->GetGrHandle(13);
	GrNum = 0;
	X = -64;
	Y = -64;
	VX = 0;
	MoveF = 0;
	AtackCnt = 0;
	SetColSqr(-5, -7, 5, 7);

}


Yusya::~Yusya()
{
}
