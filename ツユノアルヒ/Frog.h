#pragma once
#include "EnemyBase.h"

class Frog :
	public EnemyBase
{
public:
	bool KasanatteruMouse();
	void Update(SceneBase *MG, int Itr);
	void Update();
	void Draw();
	void SetBgMgr(BgMgr* Bg);
	void MoveStart();
	Frog(int BgX, int BgY, BgMgr* Bg);
	~Frog();
private:
	bool StandF;
};

