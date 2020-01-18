#pragma once
#include "Singleton.h"
#include "Sprite.h"
#include <vector>

enum EffectType{STOP,RAKKA,GENSUI};

class EffectMgr :public Singleton<EffectMgr>
{
	EffectMgr();
	friend Singleton<EffectMgr>;
public:
	void Update();
	void Draw();
	void SetEffect(int X, int Y, int* GrHandleData, EffectType ET, int KillCnt, int T1, int C1, int T2, int C2, int T3, int C3, int T4, int C4, int LoopNum);
	void SetEffect(int X, int Y, double VX,double VY,int* GrHandleData, EffectType ET, int KillCnt, int T1, int C1, int T2, int C2, int T3, int C3, int T4, int C4, int LoopNum);
	void SetEffect(int X, int Y, double VX, double VY, double AY, int * GrHandleData, EffectType ET, int KillCnt, int T1, int C1, int T2, int C2, int T3, int C3, int T4, int C4, int LoopNum);
	void Kill();
	~EffectMgr();
private:
	std::vector<Sprite*> EffectList;
	std::vector<int> KillCntList;
	std::vector<int> CntList;
	std::vector<EffectType> ETList;
};

