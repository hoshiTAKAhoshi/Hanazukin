#include "Iwa.h"
#include "DxLib.h"
#include "Bank.h"
#include "Shake.h"
#include "EffectMgr.h"

void Iwa::Update()
{
	Sprite::Update();
	Y += VY;

	if (Y > 6.6*16*4)
	{
		int c = 1 + GetRand(1);
		EffectMgr::Instance()->SetEffect(X, Y, -GetRand(3)-1, -5, 0.4,Bank::Instance()->GetGrHandle(16), RAKKA, 27, 1, c, 1, c, 1, c, 1, c, 1);
		c = 1 + GetRand(1);
		EffectMgr::Instance()->SetEffect(X, Y, GetRand(3)+1, -5, 0.4,Bank::Instance()->GetGrHandle(16), RAKKA, 27, 1, c, 1, c, 1, c, 1, c, 1);
		X = -64;
		VY = 0;
		Y = -64;
		Shake::Instance()->Start(20, 6);
		Bank::Instance()->PlaySe(4);
	}
}

void Iwa::Update(SceneBase * MG, int Itr)
{
}

void Iwa::Draw()
{
	Sprite::Draw();

}

bool Iwa::KasanatteruMouse()
{
	return false;
}

void Iwa::MoveStart()
{
}

void Iwa::MoveStop()
{
	VY = 0;
}

Iwa::Iwa()
{
	EnemyType = 6;
	ExRate = 4;
	X = 5 * 16 * 4 +GetRand(2)*32*4;
	Y = -64;
	VY = 1+GetRand(10)/(double)10;
	HitType = NOT_ABLE_TO_STEP_ON;
	MoveF = 1;
	HitKabeF = 0;
	TurnStopCnt = 0;
	GrHandleData = Bank::Instance()->GetGrHandle(16);
	GrNum = 0;
	SetColSqr(AtariX[0], AtariY[0], AtariX[1], AtariY[1]);

}


Iwa::~Iwa()
{
}
