#include "Title.h"
#include "DxLib.h"
#include "Mouse.h"
#include "Bank.h"

void Title::Update()
{
	if (Mouse::Instance()->GetInputSyunkan() & MOUSE_INPUT_LEFT)
	{
		//SM->ChangeScene(MAINGAMESCENE);
	}

	DekaButton[0]->Update();
	DekaButton[1]->Update();

	if (DekaButton[0]->GetOsareta() == 1)
	{
		DekaButton[0]->SetActiveF(0);
		DekaButton[1]->SetActiveF(0);
		SM->ChangeScene(SELECTSTAGESCENE);
	}
	if (DekaButton[1]->GetOsareta() == 1)
	{
		DekaButton[0]->SetActiveF(0);
		DekaButton[1]->SetActiveF(0);
		SM->Owaru();
	}
	//Bg.Update();
}

void Title::Draw()
{
	//”wŒi•`‰æ
	for (int y = 0; y < 144; y++)
	{
		DrawBox(0, y * 4, 192 * 4, y * 4 + 4, GetColor(80 + y * y / 150, 200 + y * y / 400, 255), 1);
	}
	AddCnt = (AddCnt++) % 255;
	////printfDx("%d\n", AddCnt);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 180);
	DrawRotaGraph(192 * 2, 144 * 2, 4, 0, GrHandle[2], 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	DrawRotaGraph(192 * 2, 144 * 2, 4, 0, GrHandle[2], 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawRotaGraph(192 * 2-4, 144 * 1.75-4, 4, 0, GrHandle[1], 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawRotaGraph(192 * 2, 144 * 1.75, 4, 0, GrHandle[0], 1);
	Bg.Draw();
	DekaButton[0]->Draw();
	DekaButton[1]->Draw();
}

Title::Title(SceneMgr* SM)
{
	Bank::Instance()->StopBgm(0);
	Bank::Instance()->StopBgm(1);
	this->SM = SM;
	GrHandle[0] = LoadGraph("Resource/Images/TitleMoji.png");
	GrHandle[1] = LoadGraph("Resource/Images/TitleMojiKage.png");
	GrHandle[2] = LoadGraph("Resource/Images/TitleHaikei.png");
	JimenHandle = Bank::Instance()->GetGrHandle(1);
	Bg.SetExRate(4);
	Bg.SetXY(0, 16*2);
	for (int x = 0; x < 12; x++)
		Bg.PutChip(0, x, 7, JimenHandle[6]);
	for (int x = 0; x < 12; x++)
		Bg.PutChip(0, x, 8, JimenHandle[10]);

	DekaButton[0] = new Button(Bank::Instance()->GetGrHandle(9), 0, 192*1.25, 144 * 2.75, 48 * 4, 18 * 4);
	DekaButton[1] = new Button(Bank::Instance()->GetGrHandle(9), 4, 192*2.75, 144 * 2.75, 48 * 4, 18 * 4);

	//PlaySoundMem(*(Bank::Instance()->GetSoundHandle(16)), DX_PLAYTYPE_BACK);
	//Bank::Instance()->PlaySe(16);
}


Title::~Title()
{
	delete SM;
	delete DekaButton[0];
	delete DekaButton[1];
}
