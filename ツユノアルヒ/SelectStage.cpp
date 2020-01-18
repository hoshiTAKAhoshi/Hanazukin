#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "SelectStage.h"
#include "Bank.h"
#include "DxLib.h"
#include "EffectMgr.h"
#include "Window.h"

SelectStage::SelectStage(SceneMgr* SM)
{
	this->SM = SM;

	JimenHandle = Bank::Instance()->GetGrHandle(1);

	Bg.SetExRate(4);
	Bg.SetXY(0, 16 * 2);
	for (int x = 0; x < 12; x++)
		Bg.PutChip(0, x, 7, JimenHandle[6]);
	for (int x = 0; x < 12; x++)
		Bg.PutChip(0, x, 8, JimenHandle[10]);
	
	int PlayAbleStage;
	if ((fp = fopen("SaveData.dat", "rb")) == NULL)
	{
		PlayAbleStage = 0;////printfDx("ないよ");
	}
	else
	{
		fread(&PlayAbleStage, sizeof(int), 1, fp);
		fclose(fp);
	}

	int aida = 9;
	int aiday = 12;
	for (int y = 0; y < MINISTAGE_YMAX; y++)
	{
		for (int x = 0; x < MINISTAGE_XMAX; x++)
		{
			int num = x + y * (MINISTAGE_YMAX + 1);
			StageThumbnail[num] = new Thumbnail(num, (1+aida) * 4 + x * (3 * 12 * 4 + aida * 4), (15+aiday) * 4 + y * (3 * 9 * 4 + aiday * 4),PlayAbleStage>=num);
		}
	}
	BackButton = new Button(0, 16 * 4 * 10.5 + 32, 32, 14 * 4, 14 * 4);	//やめる
	Window::Instance()->kill();
	Bank::Instance()->PlayBgm(1);

}


SelectStage::~SelectStage()
{
	for (int i = 0; i < MINISTAGE_MAX; i++)
	{
		delete StageThumbnail[i];
	}
	delete BackButton;
}

void SelectStage::Update()
{
	for (int i = 0; i < MINISTAGE_MAX; i++)
	{
		StageThumbnail[i]->Update();
		//メインゲームに遷移
		if (StageThumbnail[i]->GetOsaretaF() == 1)
		{
			SM->ChangeScene(MAINGAMESCENE, 0, i);
		}
	}



	//鍵を開けた時の処理
	for (int i = MINISTAGE_MAX - 1; i >= 1; i--)
	{
		if (StageThumbnail[i]->GetActiveF() == 1)
		{
			for (int j = i - 1; j >= 1; j--)
			{
				if (StageThumbnail[j]->GetActiveF() == 0)
				{
					StageThumbnail[j]->OpenKey();
				}
				else
				{
					break;
				}
			}
		}
	}

	BackButton->Update();
	if (BackButton->GetOsareta() == 1)
	{
		BackButton->SetActiveF(0);
		SM->ChangeScene(TITLESCENE);
	}
}

void SelectStage::Draw()
{
	//背景描画
	for (int y = 0; y < 144; y++)
	{
		DrawBox(0, y * 4, 192 * 4, y * 4 + 4, GetColor(80 + y * y / 150, 200 + y * y / 400, 255), 1);
	}
	//Bg.Draw();

	for (int i = 0; i < MINISTAGE_MAX; i++)
	{
		StageThumbnail[i]->Draw();
	}

	EffectMgr::Instance()->Draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(0, 0, 1000, 64, GetColor(0, 0, 0), 1);
	DrawString(4 + 36, 16 + 2, "ステージセレクト", GetColor(0, 0, 0));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawString(0 + 36, 12 + 2,"ステージセレクト", GetColor(255, 255, 255));

	BackButton->Draw();
}
