#pragma once
#include "EnemyBase.h"
#include "ThunderMgr.h"

class KaminariSama :
	public EnemyBase
{
public:
	bool KasanatteruMouse();
	void Update();
	void Update(SceneBase *MG, int Itr);
	//void Update2(SceneBase * MG, int Itr);
	void Draw();
	void SetBgMgr(BgMgr* Bg);
	void MoveStart();
	void MoveStop();
	KaminariSama(int BgX, int BgY, BgMgr* Bg,ThunderMgr* KaminariMgr);
	~KaminariSama();
private:
	bool KowasuGaido;
	int KowasuGaidoX;
	int KowasuGaidoY;
	bool KaminariNow;
	bool StandF;
	int* KaminariGrHandle;
	int KowasuCnt;
	ThunderMgr* KaminariMgr;
};

