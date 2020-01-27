#pragma once
#include "Sprite.h"
#include "EnemyBase.h"
#include "SceneBase.h"
class WarpMan :
	public EnemyBase
{
public:
	WarpMan(int BgX, int BgY, BgMgr * Bg, int Type);
	~WarpMan();
	bool KasanatteruMouse();
	void Update(SceneBase * MG, int Itr);
	void Update();
	void Draw();
	void SetBgMgr(BgMgr * Bg);
	void MoveStart();
	void MoveStop();
private:
	bool StandF;
	double gravity;
	double GetGravity(double vy);
	bool JitabataF;
};

