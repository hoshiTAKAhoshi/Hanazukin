#pragma once
#include "SceneBase.h"
#include "SceneMgr.h"
#include "BgMgr.h"
#include "Button.h"

class Title :
	public SceneBase
{
public:
	void Update();
	void Draw();
	Title(SceneMgr* SM);
	~Title();
private:
	int GrHandle[3];
	int AddCnt = 0;
	SceneMgr* SM;
	int *JimenHandle;
	BgMgr Bg;
	Button* DekaButton[2];
};

