#include "SceneMgr.h"
#include "Title.h"
#include "SelectStage.h"
#include "NewMainGame.h"
#include "DxLib.h"
#include "Window.h"


void SceneMgr::Draw()
{
	ImaScene->Draw();
	FadeLayer->Draw();
	Window::Instance()->Draw();
	////printfDx("%d", ChangeSceneF);
}

void SceneMgr::Update()
{
	ImaScene->Update();
	FadeLayer->Update();
	//フェードインが終わってシーンを変える
	if (ChangeSceneF == 1 && FadeLayer->GetFadeInF() == -1)
	{
		/*
		switch (ImaScene)
		{
		case TITLESCENE:
			delete (Title*)ImaScene;
			break;
		case SELECTSTAGESCENE:
			delete (SelectStage*)ImaScene;
			break;
		case MAINGAMESCENE:
			delete (NewMainGame*)ImaScene;
			break;
		}
		*/

		delete ImaScene;

		switch (NextScene)
		{
		case TITLESCENE:
			ImaScene = new Title(this);
			break;
		case SELECTSTAGESCENE:
			ImaScene = new SelectStage(this);
			break;
		case MAINGAMESCENE:
			ImaScene = new NewMainGame(this, Mode, StageNum);
			break;
		}
		NowScene = NextScene;
		ChangeSceneF = false;
		FadeLayer->FadeOutStartOsyare();

	}
	//おわる
	if (OwariF == 1 && FadeLayer->GetFadeInF() == -1)
	{
		//delete ImaScene;
		OwariF = 2;
	}

}

void SceneMgr::ChangeScene(Scene NextScene)
{
	this->NextScene = NextScene;
	ChangeSceneF = true;
	FadeLayer->FadeInStartOsyare();
}

void SceneMgr::ChangeScene(Scene NextScene,int Mode,int StageNum)
{
	this->NextScene = NextScene;
	ChangeSceneF = true;
	FadeLayer->FadeInStartOsyare();
	this->Mode = Mode;
	this->StageNum = StageNum;
}

void SceneMgr::Owaru()
{
	FadeLayer->FadeInStartOsyare();
	OwariF = 1;
}

int SceneMgr::GetOwari()
{
	return OwariF;
}


SceneMgr::SceneMgr(Scene FirstScene)
{
	NowScene = FirstScene;
	switch (FirstScene)
	{
	case TITLESCENE:
		ImaScene = new Title(this);
		break;
	case SELECTSTAGESCENE:
		ImaScene = new SelectStage(this);
		break;
	case MAINGAMESCENE:
		ImaScene = new NewMainGame(this, 0, 1);
		break;
	}

	FadeLayer = new Fade(0, 255, 0, 0, 0);
	FadeLayer->SetCnt(15);
	FadeLayer->FadeOutStartOsyare();
	OwariF = 0;

}

SceneMgr::~SceneMgr()
{
}
