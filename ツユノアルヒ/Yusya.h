#pragma once
#include "Sprite.h"
#include "EnemyBase.h"
#include "BgMgr.h"

class Yusya :
	public Sprite
{
public:
	void Move();
	void MoveStart();
	void Atack();
	void UpdateBoss1();
	void NottoriInit();
	void UpdateNottori();
	void UpdateTaore();
	void Update();
	void Draw();
	void SetBgMgr(BgMgr * Bg);
	void SetBgXY(int BgX, int BgY);
	void SetBoss(EnemyBase* Boss);
	int GetAtackCnt();
	int GetGekiha();
	int GetNottoriCnt();
	bool GetNottorareF();
	void Init();
	Yusya();
	~Yusya();
private:
	BgMgr * Bg;
	EnemyBase* BossKun;
	bool MoveF;
	int AtackCnt;
	bool FuttobiF = 0;
	int Gekiha;
	int NottoriCnt = 0;
	bool NottorareF = 0;
	int AtariX[2] = { -4,4 };
	int AtariY[2] = { -6,8 };
};

