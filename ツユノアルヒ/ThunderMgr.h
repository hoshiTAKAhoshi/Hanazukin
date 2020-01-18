#pragma once
#include "BgMgr.h"
#include "Player.h"
#include "SceneBase.h"
#include "OutLineMgr.h"

class ThunderMgr
{
public:
	void Update();
	void Draw();
	int GetCnt();
	bool CheckHitHito();
	void SetHitHitoF(bool HitHitoF);
	void PutThunder(int BgX, int BgY);
	void Init();
	ThunderMgr(SceneBase* MG, OutLineMgr* KogeMgr);
	~ThunderMgr();
private:
	SceneBase * MG;
	BgMgr * Bg;
	Player* Hito;
	OutLineMgr* KogeMgr;
	bool HitHitoF;
	int PutThunderF;
	int FromBgX;
	int FromBgY;
	double ThunderDY;
	int* ThunderGrHandle;
	int Cnt;
};

