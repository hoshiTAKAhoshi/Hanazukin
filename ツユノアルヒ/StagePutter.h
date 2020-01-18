#pragma once
#include "BgMgr.h"
#include "Player.h"
#include "Yusya.h"
#include "SceneBase.h"
//#include "Sprite.h"
#include "EnemyBase.h"
#include "ThunderMgr.h"
#include "OutLineMgr.h"
#include <vector>

class StagePutter
{
public:
	//ステージ数を調べる
	//int GetStageMax(char * StageNameData);
	int GetStageMax(char StageNameData[128][128]);
	void PutStage(int StageNum);
	StagePutter(BgMgr * Bg,Player * Hito,Yusya * YusyaKun, std::vector<EnemyBase*>* Enemy,ThunderMgr * KaminariMgr,OutLineMgr* KogeMgr,bool *BeemF,char * StageName,char * FlowerName,char * FlowerMessage, SceneBase* MG);
	~StagePutter();
private:
	BgMgr * Bg;
	Player * Hito;
	Yusya* YusyaKun;
	std::vector<EnemyBase*>* Enemy;
	ThunderMgr * KaminariMgr;
	OutLineMgr* KogeMgr;
	char * StageName;
	char * FlowerName;
	char * FlowerMessage;
	bool* BeemF;
	SceneBase* MG;
};

