#pragma once
#include "EnemyBase.h"
#include "BgMgr.h"
#include "Yusya.h"

class Fire :
	public EnemyBase
{
public:
	void Update();
	void Update(SceneBase *MG, int Itr);
	void Draw();
	bool KasanatteruMouse();
	void MoveStart();
	void MoveStop();
	Fire(int X,int Y,BgMgr* Bg, Yusya * YusyaKun);
	~Fire();
private:
	Yusya * YusyaKun;
};

