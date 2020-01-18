#include "Boss.h"
#include "Bank.h"
#include "BgMgr.h"
#include "Mouse.h"
#include "Fire.h"
#include "DxLib.h"

void Boss::Update()
{
	Sprite::Update();
}

void Boss::UpdateDai1()
{
	FireCnt++;

	switch (Hp)
	{
	case 3:
		if (FireCnt == 120)
		{
			GrNum = 3;
		}
		if (FireCnt >= 140)
		{
			Bank::Instance()->PlaySe(4);
			EB->push_back(new Fire(X - 8 * 4, Y + 8 * 4, Bg, YusyaKun));
			FireCnt = 0;
			SpAnim(10, 2, 30, 0, 30, 0, 30, 0, 1);
		}
		break;
	case 2:
		if (FireCnt == 100)
		{
			GrNum = 3;
		}
		if (FireCnt >= 120)
		{
			Bank::Instance()->PlaySe(4);
			EB->push_back(new Fire(X - 8 * 4, Y + 8 * 4, Bg, YusyaKun));
			FireCnt = 0;
			SpAnim(10, 2, 30, 0, 30, 0, 30, 0, 1);
		}

		break;
	case 1:
		if (FireCnt == 100)
		{
			GrNum = 3;
		}
		if (FireCnt == 120)
		{
			Bank::Instance()->PlaySe(4);
			EB->push_back(new Fire(X - 8 * 4, Y + 8 * 4, Bg, YusyaKun));
			SpAnim(10, 2, 30, 0, 30, 0, 30, 0, 1);
		}

		if (FireCnt == 160)
		{
			SpAnimStop();
			GrNum = 3;
		}
		if (FireCnt == 180)
		{
			Bank::Instance()->PlaySe(4);
			EB->push_back(new Fire(X - 8 * 4, Y + 8 * 4, Bg, YusyaKun));
			SpAnim(10, 2, 30, 0, 30, 0, 30, 0, 1);
		}
		if (FireCnt >= 200)
		{
			FireCnt = 0;

		}

		break;
	}
}

void Boss::Update(SceneBase * MG, int Itr)
{
}

void Boss::Draw()
{
	Sprite::Draw();
}

bool Boss::KasanatteruMouse()
{
	int mx = Mouse::Instance()->GetX();
	int my = Mouse::Instance()->GetY();

	//if (MoveF == 0 && mx > X - 8 * 4 && mx<X + 8 * 4 && my>Y - 8 * 4 && my < Y + 8 * 4)
	if (mx > X - 15 * 4 && mx<X + 15 * 4 && my>Y - 15 * 4 && my < Y + 15 * 4)
	{
		if (FuchiByougaF == 0)
			FuchiByougaF = 1;
		//ƒNƒŠƒbƒN‚³‚ê‚½
		if ((Mouse::Instance()->GetInputSyunkan() & MOUSE_INPUT_LEFT) != 0)
		{
			if (MoveF == 0)
			{
				(*Tesuu)++;
				Bank::Instance()->PlaySe(6);
				//MoveStart();
				EB->push_back(new Fire(X- 8 * 4, Y - 8 * 4, Bg,YusyaKun));
				SpAnim(10, 1, 30, 0, 30, 0, 30, 0, 1);
				FuchiByougaF = 10;
			}
			else
			{
				Bank::Instance()->PlaySe(6);
				//MoveStop();
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

void Boss::MoveStart()
{
}

void Boss::MoveStop()
{
}

Boss::Boss(int ScreenX, int ScreenY,BgMgr* Bg, std::vector<EnemyBase*>* EB, Yusya* YusyaKun)
{
	X = ScreenX;
	Y = ScreenY;
	this->Bg = Bg;
	this->EB = EB;
	this->YusyaKun = YusyaKun;
	HitType = NOT_ABLE_TO_STEP_ON;
	YusyaKun->SetBoss(this);
	Hp = 3;
	ExRate = 4;
	GrHandleData = Bank::Instance()->GetGrHandle(14);
	GrNum = 0;
	MoveF = 0;
	FireCnt = 0;
	SetColSqr(-14, -14, 14, 14);
}


Boss::~Boss()
{
}

void Boss::SetHp(int Hp)
{
	this->Hp = Hp;
}

int Boss::GetHp()
{
	return Hp;
}

void Boss::SetFireCnt(int Cnt)
{
	FireCnt = Cnt;
}
