#include "Thumbnail.h"
#include "DxLib.h"
#include "Bank.h"
#include "Mouse.h"
#include "EffectMgr.h"
#include "Shake.h"

#define KAGIBRBR_TIME 10

Thumbnail::Thumbnail(int StageNum,int X,int Y, int ActiveF)
{
	this->StageNum = StageNum;
	this->X = X;
	this->Y = Y;
	this->ActiveF = ActiveF;
	GrHandle = Bank::Instance()->GetGrHandle(18);
	StageData = Bank::Instance()->GetStageData(0, StageNum);
	KiranHandle = Bank::Instance()->GetGrHandle(19);
	Kiran.SetGrHandleData(KiranHandle);
	Kiran.SetExRate(4);
	Kiran.SetGrNum(15);
	Kiran.SetXY(X + WAKU_WIDTH / 2, Y + WAKU_HEIGHT / 2);
	Kiran.SetDrawAlpha(200);
	Kasanatteru = 0;

	Kagi.SetGrHandleData(Bank::Instance()->GetGrHandle(20));
	Kagi.SetExRate(4);
	Kagi.SetGrNum(0);
	Kagi.SetXY(X + WAKU_WIDTH / 2, Y + WAKU_HEIGHT / 2);

	KagiClickCnt = 0;
	KagiBrbrCnt = 0;

	OsaretaF = 0;
	OsaretaCnt = 0;
	DY = 0;
}

Thumbnail::~Thumbnail()
{
}

void Thumbnail::Update()
{
	if (OsaretaF == 1)
		OsaretaF = 0;

	Kiran.Update();
	Kagi.Update();
	int mx = Mouse::Instance()->GetX();
	int my = Mouse::Instance()->GetY();

	//マウスカーソルと重なった
	if (mx >= X - 4 && mx <= X + WAKU_WIDTH + 4 && my >= Y - 4 && my <= Y + WAKU_HEIGHT + 4)
	{
		if (Kasanatteru == 0)
		{
			int t = 3;
			Kiran.SpAnim(t-1, 0, t, 1, t, 2, t, 3, t, 4, t, 5, t, 6, t, 7, t, 8, t, 9, t, 10, 1);
			Kiran.SetDrawAlpha(200);
			Kiran.SpAnimAlphaStop();
			Kasanatteru = 1;
		}
		if (Kasanatteru >= 1)
		{
			Kasanatteru++;
		}

		//クリックされた
		if (Mouse::Instance()->GetInputSyunkan() & MOUSE_INPUT_LEFT)
		{
			switch (ActiveF)
			{
			case 1://鍵かかってない
				Bank::Instance()->PlaySe(7);
				OsaretaF = 1;
				DY = 12;
				break;
			case 0://鍵がかかっているとき
				Bank::Instance()->PlaySe(10);
				Bank::Instance()->PlaySe(10);
				Bank::Instance()->PlaySe(10);
				Bank::Instance()->PlaySe(10);
				Bank::Instance()->PlaySe(10);
				Bank::Instance()->PlaySe(10);
				KagiClickCnt++;
				KagiBrbrCnt = 1;
				
				if (KagiClickCnt >= 10)
				{
					Bank::Instance()->PlaySe(6);
					FILE* fp; 
					fopen_s(&fp, "SaveData.dat", "wb");
					int tmp[1];
					tmp[0] = StageNum;
					////printfDx("tmp[0]=%d\n", tmp[0]);
					fwrite(tmp, sizeof(int), 1, fp);
					fclose(fp);

					OpenKey();
				}
				break;
			}
		}
	}
	else
	{
		if (Kasanatteru >= 1)
		{
			Kiran.SpAnimAlpha(200, 10, 0);
		}
		Kasanatteru = 0;
		KagiClickCnt = 0;

	}

	if (DY > 0)
	{
		DY -= DY / 8.0;
		Kiran.SetXY(X + WAKU_WIDTH / 2, Y + WAKU_HEIGHT / 2 + DY);
	}
	else
	{
		DY = 0;
		Kiran.SetXY(X + WAKU_WIDTH / 2, Y + WAKU_HEIGHT / 2 + DY);
	}



	//鍵ぶるぶる
	if (KagiBrbrCnt >= 1)
	{
		KagiBrbrCnt++;

		if (KagiBrbrCnt >= KAGIBRBR_TIME)
		{
			KagiBrbrCnt = 0;
			Kagi.SetXY(X + WAKU_WIDTH / 2, Y + WAKU_HEIGHT / 2);
		}
		else
		{
			if (KagiBrbrCnt == 2)
			{
				int haba = (KAGIBRBR_TIME - KagiBrbrCnt)*(0.8 + KagiClickCnt / 5.0);
				Kagi.SetXY(X + WAKU_WIDTH / 2 + haba / 2, Y + WAKU_HEIGHT / 2 + haba / 2);
			}
			else if (KagiBrbrCnt == 3)
			{
				int haba = (KAGIBRBR_TIME - KagiBrbrCnt)*(0.8 + KagiClickCnt / 5.0);
				Kagi.SetXY(X + WAKU_WIDTH / 2 - haba / 2, Y + WAKU_HEIGHT / 2 - haba / 2);
			}
			else
			{
				int haba = (KAGIBRBR_TIME - KagiBrbrCnt)*(0.8 + KagiClickCnt / 5.0);
				Kagi.SetXY(X + WAKU_WIDTH / 2 - haba / 2 + GetRand(haba), Y + WAKU_HEIGHT / 2 - haba / 2 + GetRand(haba));
			}
		}

	}

}

void Thumbnail::Draw()
{
	//ワク
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	for (int i = 0; i < 4; i++)
	{
		DrawBox(X-1-i, Y-1-i+DY, X + MINICHAR_WIDTH * MINICHAR_XMAX*4+1+i, Y + MINICHAR_WIDTH * MINICHAR_YMAX*4+1+i + DY, GetColor(0, 0, 0), 0);
	}

	switch (ActiveF)
	{
	case 1:
		//はいけい
		if (StageNum != 11)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			DrawBox(X, Y + DY, X + WAKU_WIDTH, Y + WAKU_HEIGHT + DY, GetColor(255, 255, 255), 1);
		}
		else
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			DrawBox(X, Y + DY, X + WAKU_WIDTH, Y + WAKU_HEIGHT + DY, GetColor(0, 0, 100), 1);
		}
		//ちっちゃいマップ
		for (int i = 1; i >= 0; i--)
		{
			//影の時
			if (i == 1)
			{
				SetDrawBright(0, 0, 0);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 30);
			}
			else
			{
				SetDrawBright(255, 255, 255);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			}

			for (int y = 0; y < 9; y++)
			{
				for (int x = 0; x < 12; x++)
				{
					for (int c = 0; ItoC[c] != '\0'; c++)
					{
						if (ItoC[c] == StageData[x + y * 12])
						{
							if (StageData[x + y * 12] == 'E' && y > 0)
							{
								if (StageNum != 11)
								{
									if (StageData[x + (y - 1) * 12] == 'E')
										DrawRotaGraph(i * 4 + 1.5 * 4 + X + x * 3 * 4, i * 4 + 1.5 * 4 + Y + y * 3 * 4 + DY, 4, 0, GrHandle[c + 1 + i * 32], 1);
									else
										DrawRotaGraph(i * 4 + 1.5 * 4 + X + x * 3 * 4, i * 4 + 1.5 * 4 + Y + y * 3 * 4 + DY, 4, 0, GrHandle[c + i * 32], 1);
								}
								else
									DrawRotaGraph(i * 4 + 1.5 * 4 + X + x * 3 * 4, i * 4 + 1.5 * 4 + Y + y * 3 * 4 + DY, 4, 0, GrHandle[10-y%2 + i * 32], 1);

							}
							else
							{
								DrawRotaGraph(i * 4 + 1.5 * 4 + X + x * 3 * 4, i * 4 + 1.5 * 4 + Y + y * 3 * 4 + DY, 4, 0, GrHandle[c + i * 32], 1);
							}
						}
					}
				}
			}
		}
		break;
	case 0:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawBox(X, Y, X + WAKU_WIDTH, Y + WAKU_HEIGHT, GetColor(0, 55, 55), 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		Kagi.Draw();
		//DrawRotaGraph(X + WAKU_WIDTH / 2, Y + WAKU_HEIGHT / 2, 4, 0, KiranHandle[14], 1);
		break;
	}

	//上のバー
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 30);
	DrawBox(X, Y, X + 12 *3* 4, Y + 4, GetColor(0, 0, 0), 1);
	DrawBox(X, Y+4, X + 4, Y + 9 *3* 4, GetColor(0, 0, 0), 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	Kiran.Draw();

	//かさなってるワク
	if (Kasanatteru >= 1)
	{
		for (int i = 0; i < 4; i++)
		{
			DrawBox(X - 5 - i, Y - 5 - i + DY, X + MINICHAR_WIDTH * MINICHAR_XMAX * 4 + 5 + i, Y + MINICHAR_WIDTH * MINICHAR_YMAX * 4 + 5 + i + DY, GetColor(250, 240, 0), 0);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, max(0,150-Kasanatteru*7));
		DrawBox(X, Y + DY, X + WAKU_WIDTH, Y + WAKU_HEIGHT + DY, GetColor(255, 255, 255), 1);

	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	//DrawFormatString(X, Y, GetColor(0, 0, 0), "%d", StageNum);
}

void Thumbnail::OpenKey()
{
	ActiveF = 1;
	int grnum = GetRand(1) * 2 + 1;
	int vx = (grnum - 2) * 3;
	EffectMgr::Instance()->SetEffect(X + WAKU_WIDTH / 2, Y + WAKU_HEIGHT / 2, vx, -5.5, 0.3, Bank::Instance()->GetGrHandle(20), RAKKA, 40, 6, grnum, 4, 15, 6, grnum, 4, 15, 5);
	int t = 3;
	Kiran.SpAnim(t - 1, 0, t, 1, t, 2, t, 3, t, 4, t, 5, t, 6, t, 7, t, 8, t, 9, t, 10, 1);
	Kiran.SetDrawAlpha(200);
	Kiran.SpAnimAlphaStop();

}

void Thumbnail::SetActiveF(int ActiveF)
{
	this->ActiveF = ActiveF;
}

int Thumbnail::GetActiveF()
{
	return ActiveF;
}

int Thumbnail::GetOsaretaF()
{
	return OsaretaF;
}
