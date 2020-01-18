#pragma once
#include "SceneBase.h"
#include "BgMgr.h"
#include "Player.h"
#include "Yusya.h"
//#include "Sprite.h"
#include "EnemyBase.h"
#include "StagePutter.h"
#include "Button.h"
#include "Fade.h"
#include "ThunderMgr.h"
#include "SceneMgr.h"
#include "OutLineMgr.h"
#include <vector>
#include <stdio.h>

enum GameMode { WINDOW, SELECTSTAGE, MAINGAME, CLEAR };

class MainGame :
	public SceneBase
{
public:
	void Collision();
	void YusyaCollision();
	void CheckClear();
	void MiniButtonUpdate();
	void StageSelectUpdate();
	void MainGameUpdate();
	void Update();
	void MojiUpdate();
	void MiniButtonDraw();
	void MojiDraw();
	void DrawUeNoBar();
	void Draw();
	BgMgr* GetBg();
	Player* GetHito();
	MainGame(SceneMgr* SM);
	~MainGame();
	void PutSlime(int X, int Y);
	std::vector<EnemyBase*> Enemy;
private:
	bool ToMainGame;
	bool ToSelectStage;
	bool ToReStart;
	bool ToNextStage;
	int *JimenHandle;
	int *FlowerHandle;
	char StageNameData[128][128];
	char StageName[128];
	char FlowerName[128];
	char FlowerMessage[128];
	char Moji[19] = "クリックでスタート";
	int MojiX[9];
	double MojiY[9];
	double MojiVY[9];
	int MojiCnt;
	char Moji2[13] = "クリアー！！";
	int MojiX2[6];
	double MojiY2[6];
	double MojiVY2[6];
	int MojiCnt2;
	int ClearMati;
	int StartFuchiF;
	int NowStage;
	int StageMax;
	int PlayAbleStage;
	int SerifCnt = 0;
	int EventCnt = 0;
	bool BeemF[3] = { 0,0,0 };
	int BeemX[2][2];
	int BeemY[2][2];
	int* BeemGrHandle;
	double BeemCenterX, BeemCenterY;
	int sx, sy;
	int OseCnt = 0;
	bool GuidF = 0;
	BgMgr Bg;
	Player Hito;
	Yusya YusyaKun;
	StagePutter* StageOkuyo;
	GameMode MainGameMode;
	Button* MiniButton[4];
	Fade* FadeLayer[3];
	SceneMgr* SM;
	ThunderMgr* KaminariMgr;
	OutLineMgr* KogeMgr;
	FILE* fp;// = fopen_s("SaveData.dat", "wb");

};

