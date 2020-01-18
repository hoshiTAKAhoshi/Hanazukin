#pragma once
#include "Sprite.h"
#include "EnemyBase.h"
#include "SceneBase.h"

class Slime :
	public EnemyBase
{
public:
	bool KasanatteruMouse();
	void Update();
	void Update(SceneBase *MG,int Itr);
	//void Update2(SceneBase * MG, int Itr);
	void Draw();
	void SetBgMgr(BgMgr* Bg);
	void MoveStart();
	void MoveStop();
	Slime(int BgX, int BgY,BgMgr* Bg);
	~Slime();
private:
	bool StandF;
};

