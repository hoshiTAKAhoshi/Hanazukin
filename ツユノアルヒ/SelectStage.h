#pragma once
#include "SceneBase.h"
#include "BgMgr.h"
#include "Thumbnail.h"
#include "SceneMgr.h"
#include "Button.h"
#include <stdio.h>

//#define MINICHARDATAMAX 10

#define MINISTAGE_XMAX 4
#define MINISTAGE_YMAX 3
#define MINISTAGE_MAX MINISTAGE_XMAX*MINISTAGE_YMAX

class SelectStage :
	public SceneBase
{
public:
	SelectStage(SceneMgr* SM);
	~SelectStage();
	void Update();
	void Draw();

private:
	int* JimenHandle;
	BgMgr Bg;
	Thumbnail* StageThumbnail[MINISTAGE_MAX];
	SceneMgr* SM;
	Button* BackButton;
	FILE* fp;// = fopen_s("SaveData.dat", "wb");

};

