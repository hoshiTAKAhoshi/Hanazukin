#include "KaminariSama.h"
#include "Bank.h"
#include "Mouse.h"
#include "DxLib.h"

bool KaminariSama::KasanatteruMouse()
{
	int mx = Mouse::Instance()->GetX();
	int my = Mouse::Instance()->GetY();

	if (mx > X - 8 * 4 && mx<X + 8 * 4 && my>Y - 8 * 4 && my < Y + 8 * 4)
	{

		if (MoveF == 1)
		{
			int y;
			for (y = 0; y < 144 * 4; y += 16 * 4)
			{
				if (Bg->GetChip(0, X, Y + y) != -1)
					break;
			}
			KowasuGaidoX = (int)X / 64 * 64+32;
			KowasuGaidoY = (int)(Y + y) / 64 * 64+32;
			KowasuGaido = 1;
		}
		if (FuchiByougaF == 0)
			FuchiByougaF = 1;
		//クリックされた
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
				//if (KaminariMgr->GetCnt() == 0)
				{
					(*Tesuu)++;
					KaminariNow = 1;
					Bank::Instance()->PlaySe(4);
					KaminariMgr->PutThunder(X / 64, Y / 64);
					FuchiByougaF = -1;
					if (MigiMuki == 0)
						SpAnim(4, 8, 4, 9, 4, 10, 4, 11, 1);
					else
						SpAnim(4, 24, 4, 25, 4, 26, 4, 27, 1);

				}
			}
		}
		if (KaminariMgr->GetCnt() == 19)
		{
			FuchiByougaF = 1;
		}
		return 1;

	}
	else
	{
		KowasuGaido = 0;
		FuchiByougaF = 0;
	}


	return 0;
}

void KaminariSama::Update()
{
	Sprite::Update();

	X += (VX + SitaVX);

	//右に地面がある
	if (Bg->GetChip(0, X + AtariX[1] * ExRate - 1, Y + AtariY[0] * ExRate + 1) != -1 || Bg->GetChip(0, X + AtariX[1] * ExRate - 1, Y + AtariY[1] * ExRate - 1) != -1)
	{
		//めり込み防止
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
			SpAnim(10, 19, 10, 20, 10, 16, 18, 16, 1);
			TurnStopCnt = 1;
			HitKabeF = 1;
			MoveF = 1;
		}
	}


	if (X > 192 * 4-32)
	{
		X = 192 * 4 - 32;
		MigiMuki = 0;
		VX = 0;
		SitaVX = 0;
		//if (MoveF == 1)
		{
			SpAnim(10, 19, 10, 20, 10, 16, 18, 16, 1);
			TurnStopCnt = 1;
			HitKabeF = 1;
			MoveF = 1;
		}

	}


	//左に地面がある
	if (Bg->GetChip(0, X + AtariX[0] * ExRate, Y + AtariY[0] * ExRate + 1) != -1 || Bg->GetChip(0, X + AtariX[0] * ExRate, Y + AtariY[1] * ExRate - 1) != -1)
	{
		//めり込み防止
		while (Bg->GetChip(0, X + AtariX[0] * ExRate, Y + AtariY[0] * ExRate + 1) != -1 || Bg->GetChip(0, X + AtariX[0] * ExRate, Y + AtariY[1] * ExRate - 1) != -1)
		{
			X++;
		}
		MigiMuki = 1;
		VX = 0;
		SitaVX = 0;
		//if (MoveF == 1)
		{
			SpAnim(10, 3, 10, 4, 10, 0, 18, 0, 1);
			TurnStopCnt = 1;
			HitKabeF = 1;
			MoveF = 1;
		}
	}


	if (X < 0+32)
	{
		X = 0+32;
		MigiMuki = 1;
		VX = 0;
		SitaVX = 0;
		//if (MoveF == 1)
		{
			SpAnim(10, 3, 10, 4, 10, 0, 18, 0, 1);
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
					VX = 1;
					SpAnim(10, 16, 10, 17, 10, 18, 10, 19, 10, 20, -1);
				}
				else
				{
					VX = -1;
					SpAnim(10, 0, 10, 1, 10, 2, 10, 3, 10, 4, 0);
				}
			}
		}
	}


	/*
	if (StandF == 0)
	{
		VY += 0.1;
		if (VY > 5)
			VY = 5;
		Y += VY;
	}
	*/


	//下に地面がある
	if (Bg->GetChip(0, X + AtariX[0] * ExRate + 1, Y + AtariY[1] * ExRate) != -1 || Bg->GetChip(0, X + AtariX[1] * ExRate - 1, Y + AtariY[1] * ExRate) != -1)
	{
		if (StandF == 0)
		{
			StandF = 1;
			Y = (int)Y;
			//めり込み防止
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
	//ドッカンモーションが終わって通常アニメに戻る
	if (KaminariNow == 1 && GetSpAnimF() == 0)
	{
		if (MigiMuki == 1)
		{
			SpAnim(10, 16, 10, 17, 10, 18, 10, 19, 10, 20, -1);
		}
		else
		{
			SpAnim(10, 0, 10, 1, 10, 2, 10, 3, 10, 4, 0);
		}

	}

	int mx = Mouse::Instance()->GetX();
	int my = Mouse::Instance()->GetY();
	if (mx > X - 8 * 4 && mx<X + 8 * 4 && my>Y - 8 * 4 && my < Y + 8 * 4)
	{
	}
	else
	{
		KowasuGaido = 0;
		FuchiByougaF = 0;
	}

}

void KaminariSama::Update(SceneBase * MG, int Itr)
{
}

void KaminariSama::Draw()
{
	Sprite::Draw();
	if (KowasuGaido == 1)
	{
		KowasuCnt++;
		DrawRotaGraph(KowasuGaidoX, KowasuGaidoY, 4, 0, KaminariGrHandle[12+(KowasuCnt/20)%2], 1);
		//DrawBox(KowasuGaidoX - 9 * 4, KowasuGaidoY - 9 * 4, KowasuGaidoX + 9 * 4, KowasuGaidoY + 9 * 4, GetColor(255, 255, 255), 0);
		//DrawBox(KowasuGaidoX - 9 * 4+1, KowasuGaidoY - 9 * 4+1, KowasuGaidoX + 9 * 4-1, KowasuGaidoY + 9 * 4-1, GetColor(255, 255, 255), 0);
		//DrawBox(KowasuGaidoX - 9 * 4+2, KowasuGaidoY - 9 * 4+2, KowasuGaidoX + 9 * 4-2, KowasuGaidoY + 9 * 4-2, GetColor(255, 255, 255), 0);
		//DrawBox(KowasuGaidoX - 9 * 4+3, KowasuGaidoY - 9 * 4+3, KowasuGaidoX + 9 * 4-3, KowasuGaidoY + 9 * 4-3, GetColor(255, 255, 255), 0);
	}
}

void KaminariSama::SetBgMgr(BgMgr * Bg)
{
	this->Bg = Bg;

}

void KaminariSama::MoveStart()
{
	MoveF = 1;
	TurnStopCnt = 0;
	//MigiMuki = 0;
	if (MigiMuki == 1)
	{
		VX = 1;
		SpAnim(10, 16, 10, 17, 10, 18, 10, 19,10,20, -1);
	}
	else
	{
		VX = -1;
		SpAnim(10, 0, 10, 1, 10, 2, 10, 3, 10,4,0);
	}

}

void KaminariSama::MoveStop()
{
}

KaminariSama::KaminariSama(int BgX, int BgY, BgMgr * Bg, ThunderMgr* KaminariMgr)
{
	EnemyType = 2;
	ExRate = EXRATE;
	X = BgX * 16 * ExRate + 8 * ExRate + Bg->GetX();
	Y = BgY * 16 * ExRate + 8 * ExRate + Bg->GetY();
	this->KaminariMgr = KaminariMgr;
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
	KaminariNow = 0;
	KowasuCnt = 0;
	GrHandleData = Bank::Instance()->GetGrHandle(8);
	KaminariGrHandle = Bank::Instance()->GetGrHandle(10);
	GrNum = 0;

	//SpAnim(60 * (10 + GetRand(600) / 10.0), 4, 60 * (3 + GetRand(50) / 10.0), 16, 60 * (3 + GetRand(50) / 10.0), 17, 40, 18, 40, 19, 40, 20, 1);

	SetColSqr(AtariX[0], AtariY[0], AtariX[1], AtariY[1]);


}

KaminariSama::~KaminariSama()
{
}
