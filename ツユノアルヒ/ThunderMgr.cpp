#include "ThunderMgr.h"
#include "NewMainGame.h"
#include "Bank.h"
#include "Shake.h"
#include "EffectMgr.h"
#include <math.h>
#include "DxLib.h"

void ThunderMgr::Update()
{
	//雷落とす
	if (PutThunderF == 1)
	{
		if (ThunderDY <= 10)
		{
			ThunderDY += 1;
		}
		//地面レイヤー
		if (Bg->GetChip(0, FromBgX * 16 * 4, (FromBgY + ThunderDY) * 16 * 4) != -1)
		{
			printfDx("WWW");
			////printfDx("どかーん");
			PutThunderF = 2;
			Bg->PutChip(0, FromBgX, FromBgY + ThunderDY, -1);
			//消したブロックの焦げを消す
			KogeMgr->KillLine(FromBgX, FromBgY + ThunderDY);
			//上下左右をチェックしてブロックがあったら焦げ目を付ける
			if (Bg->GetChipBgZahyo(0, FromBgX, FromBgY + ThunderDY - 1) != -1)
			{
				KogeMgr->SetLine(FromBgX, FromBgY + ThunderDY - 1, DOWN);
			}
			if (Bg->GetChipBgZahyo(0, FromBgX, FromBgY + ThunderDY + 1) != -1)
			{
				KogeMgr->SetLine(FromBgX, FromBgY + ThunderDY + 1, UP);
			}
			if (Bg->GetChipBgZahyo(0, FromBgX-1, FromBgY + ThunderDY) != -1)
			{
				KogeMgr->SetLine(FromBgX-1, FromBgY + ThunderDY, RIGHT);
			}
			if (Bg->GetChipBgZahyo(0, FromBgX+1, FromBgY + ThunderDY) != -1)
			{
				KogeMgr->SetLine(FromBgX+1, FromBgY + ThunderDY, LEFT);
			}

			//崩れ
			int speed = 2 + GetRand(2);
			EffectMgr::Instance()->SetEffect((FromBgX + 0.5) * 16 * 4, ((FromBgY + 0.5) + ThunderDY) * 16 * 4, -1 - GetRand(2), -5-GetRand(4), Bank::Instance()->GetGrHandle(1), RAKKA, 90, speed, 21, speed, 22, speed, 21, speed, 22, 0);
			speed = 2 + GetRand(2); 
			EffectMgr::Instance()->SetEffect((FromBgX + 0.5) * 16 * 4, ((FromBgY + 0.5) + ThunderDY) * 16 * 4, 1 + GetRand(2), -5 - GetRand(4), Bank::Instance()->GetGrHandle(1), RAKKA, 90, speed, 21, speed, 22, speed, 21, speed, 22, 0);
			speed = 2 + GetRand(2);
			EffectMgr::Instance()->SetEffect((FromBgX + 0.5) * 16 * 4, ((FromBgY + 0.5) + ThunderDY) * 16 * 4, -3 - GetRand(2), -2 - GetRand(4), Bank::Instance()->GetGrHandle(1), RAKKA, 90, speed, 21, speed, 22, speed, 21, speed, 22, 0);
			speed = 2 + GetRand(2);
			EffectMgr::Instance()->SetEffect((FromBgX + 0.5) * 16 * 4, ((FromBgY + 0.5) + ThunderDY) * 16 * 4, 3 + GetRand(2), -2 - GetRand(4), Bank::Instance()->GetGrHandle(1), RAKKA, 90, speed, 21, speed, 22, speed, 21, speed, 22, 0);

			Shake::Instance()->Start(20, 5);
		}
		//花
		if (Bg->GetChip(1, FromBgX * 16 * 4, (FromBgY + ThunderDY) * 16 * 4) != -1)
		{
			////printfDx("どかーん");
			PutThunderF = 2;
			Bg->PutChip(1, FromBgX, FromBgY + ThunderDY, -1);
			Shake::Instance()->Start(20, 4);
		}
		int hx = (int)Hito->GetX()/(16*4);
		int hy = (int)Hito->GetY()/(16*4);
		int kx = FromBgX;// *16 * 4 + 32;
		int ky = (FromBgY + ThunderDY);// *16 * 4 + 48;
		//if (hx - 32 > kx && hx + 32 < kx && hy - 32 > ky && hy + 32 < ky)
		if(hx==kx && hy==ky)
		{
			////printfDx("どかーん");
			PutThunderF = 2;
			Shake::Instance()->Start(20, 4);
			HitHitoF = 1;
		}
	}
}

void ThunderMgr::Draw()
{
	if (PutThunderF >= 1)
	{
		for (int y = 1; y <= ThunderDY; y++)
		{
			DrawRotaGraph(FromBgX * 16 * 4+32, (FromBgY + y) * 16 * 4+32, 4, 0, ThunderGrHandle[min(4,max(0,0-y+Cnt/2))], 1);
		}
		//DrawBox(FromBgX * 16 * 4 + 32 - 4, (FromBgY + ThunderDY) * 16 * 4 + 32 - 4, FromBgX * 16 * 4 + 32 + 4, (FromBgY + ThunderDY) * 16 * 4 + 32 + 4, GetColor(255, 255, 0), 1);


		Cnt++;
		if (Cnt >= 20)
		{
			Cnt = 0;
			PutThunderF = 0;
		}
	}
}

int ThunderMgr::GetCnt()
{
	return Cnt;
}

bool ThunderMgr::CheckHitHito()
{
	return HitHitoF;
}

void ThunderMgr::SetHitHitoF(bool HitHitoF)
{
	this->HitHitoF = HitHitoF;
}

void ThunderMgr::PutThunder(int BgX,int BgY)
{
	FromBgX = BgX;
	FromBgY = BgY;
	ThunderDY = 0;
	PutThunderF = 1;
	Cnt = 0;
}

void ThunderMgr::Init()
{
	Cnt = 0;
	PutThunderF = 0;
}

ThunderMgr::ThunderMgr(SceneBase* MG, OutLineMgr* KogeMgr)
{
	PutThunderF = 0;
	ThunderDY = 0;
	HitHitoF = 0;
	this->MG = MG;
	this->Bg = ((NewMainGame*)MG)->GetBg();
	this->KogeMgr = KogeMgr;
	Hito=((NewMainGame*)MG)->GetHito();
	ThunderGrHandle = Bank::Instance()->GetGrHandle(10);
}


ThunderMgr::~ThunderMgr()
{
}
