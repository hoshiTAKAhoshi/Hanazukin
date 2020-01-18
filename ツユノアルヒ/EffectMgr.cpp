#include "EffectMgr.h"



EffectMgr::EffectMgr()
{
}


void EffectMgr::Update()
{
	for (int i = 0; i < EffectList.size(); i++)
	{
		EffectList[i]->Update();
		CntList[i]++;
		if (ETList[i] == RAKKA)
		{
			double x = EffectList[i]->GetX();
			double y = EffectList[i]->GetY();
			double vx = EffectList[i]->GetVX();
			double vy = EffectList[i]->GetVY();
			double ay = EffectList[i]->GetAY();

			x += vx;
			vy += ay;
			EffectList[i]->SetVY(vy);

			y += vy;
			EffectList[i]->SetXY(x, y);
		}
		if(CntList[i]>=KillCntList[i])
		{
			delete EffectList[i];
			EffectList.erase(EffectList.begin() + i);
			CntList.erase(CntList.begin() + i);
			KillCntList.erase(KillCntList.begin() + i);
			ETList.erase(ETList.begin() + i);
			i--;
		}
	}
}

void EffectMgr::Draw()
{
	for (int i = 0; i < EffectList.size(); i++)
	{
		EffectList[i]->Draw();
	}

}

void EffectMgr::SetEffect(int X, int Y, int* GrHandleData, EffectType ET, int KillCnt,int T1, int C1, int T2, int C2, int T3, int C3, int T4, int C4, int LoopNum)
{
	EffectList.push_back(new Sprite);
	EffectList[EffectList.size() - 1]->SetXY(X, Y);
	EffectList[EffectList.size() - 1]->SetGrHandleData(GrHandleData);
	EffectList[EffectList.size() - 1]->SetExRate(4);
	EffectList[EffectList.size() - 1]->SpAnim(T1, C1, T2, C2, T3, C3, T4, C4, LoopNum);
	this->KillCntList.push_back(KillCnt);
	this->CntList.push_back(0);
	this->ETList.push_back(ET);
}

void EffectMgr::SetEffect(int X, int Y, double VX, double VY, int * GrHandleData, EffectType ET, int KillCnt, int T1, int C1, int T2, int C2, int T3, int C3, int T4, int C4, int LoopNum)
{
	this->SetEffect(X, Y, GrHandleData, ET, KillCnt, T1, C1, T2, C2, T3, C3, T4, C4, LoopNum);
	EffectList[EffectList.size() - 1]->SetVX(VX);
	EffectList[EffectList.size() - 1]->SetVY(VY);
	EffectList[EffectList.size() - 1]->SetAY(0.5);

}
void EffectMgr::SetEffect(int X, int Y, double VX, double VY, double AY,int * GrHandleData, EffectType ET, int KillCnt, int T1, int C1, int T2, int C2, int T3, int C3, int T4, int C4, int LoopNum)
{
	this->SetEffect(X, Y, GrHandleData, ET, KillCnt, T1, C1, T2, C2, T3, C3, T4, C4, LoopNum);
	EffectList[EffectList.size() - 1]->SetVX(VX);
	EffectList[EffectList.size() - 1]->SetVY(VY);
	EffectList[EffectList.size() - 1]->SetAY(AY);

}

void EffectMgr::Kill()
{
	while (!EffectList.empty())
	{
		delete EffectList[0];
		EffectList.erase(EffectList.begin());
		CntList.erase(CntList.begin());
		KillCntList.erase(KillCntList.begin());
		ETList.erase(ETList.begin());
	}

}

EffectMgr::~EffectMgr()
{
	while (!EffectList.empty())
	{
		delete EffectList[0];
		EffectList.erase(EffectList.begin());
		CntList.erase(CntList.begin());
		KillCntList.erase(KillCntList.begin());
		ETList.erase(ETList.begin());
	}
}
