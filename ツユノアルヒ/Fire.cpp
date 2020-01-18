#include "Fire.h"
#include "Bank.h"


void Fire::Update()
{
	Sprite::Update();
	X += VX;

	//‚¯‚ñ‚ðU‚Á‚Ä‚¢‚éŠÔ
	if (YusyaKun->GetAtackCnt() >= 4 && YusyaKun->GetAtackCnt() <= 8 + 16)
	{
		if (YusyaKun->GetX() + 8 * 4 <= X && YusyaKun->GetX() + (8 + 16) * 4 >= X)
		{
			Y = -64;
		}
	}
}

void Fire::Update(SceneBase * MG, int Itr)
{

}

void Fire::Draw()
{
	Sprite::Draw();
}

bool Fire::KasanatteruMouse()
{
	return false;
}

void Fire::MoveStart()
{
}

void Fire::MoveStop()
{
	VX = 0;

}

Fire::Fire(int X, int Y, BgMgr * Bg, Yusya * YusyaKun)
{
	EnemyType = 5;
	ExRate = EXRATE;
	this->X = X;// *16 * ExRate + 8 * ExRate + Bg->GetX();
	this->Y = Y;// *16 * ExRate + 8 * ExRate + Bg->GetY();
	this->Bg = Bg;
	this->YusyaKun = YusyaKun;
	HitType = NOT_ABLE_TO_STEP_ON;
	VX = -4;
	MoveF = 1;
	HitKabeF = 0;
	TurnStopCnt = 0;
	GrHandleData = Bank::Instance()->GetGrHandle(15);
	GrNum = 0;
	SetColSqr(AtariX[0], AtariY[0], AtariX[1], AtariY[1]);

}


Fire::~Fire()
{
}
