#pragma once
#include "SceneBase.h"
#include "Fade.h"

enum Scene { TITLESCENE, SELECTSTAGESCENE, MAINGAMESCENE, OWARI };

class SceneMgr
{
public:
	void Draw();
	void Update();
	void ChangeScene(Scene NextScene);
	void ChangeScene(Scene NextScene, int Mode, int StageNum);
	void Owaru();
	int GetOwari();
	SceneMgr(Scene FirstScene);
	~SceneMgr();
	Fade* FadeLayer;
private:
	SceneBase * ImaScene;
	Scene NowScene;
	Scene NextScene;
	int ChangeSceneCnt;
	bool ChangeSceneF = 0;
	int OwariF;
	int Mode, StageNum;
};

