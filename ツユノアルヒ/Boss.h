#pragma once
#include "EnemyBase.h"
#include "Yusya.h"
#include <vector>

class Boss :
	public EnemyBase
{
public:
	void Update();
	void UpdateDai1();
	void Update(SceneBase *MG, int Itr);
	void Draw();
	bool KasanatteruMouse();
	void MoveStart();
	void MoveStop();
	Boss(int ScreenX, int ScreenY, BgMgr * Bg, std::vector<EnemyBase*>* EB,Yusya* YusyaKun);
	~Boss();
	void SetHp(int Hp);
	int GetHp();
	void SetFireCnt(int Cnt);

private:
	std::vector<EnemyBase*>* EB;
	Yusya* YusyaKun;
	int Hp;
	int FireCnt;
};

