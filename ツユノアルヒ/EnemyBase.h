#pragma once
#include "Sprite.h"
#include "SceneBase.h"
#include "BgMgr.h"

enum EnemyHitType { ABLE_TO_STEP_ON, NOT_ABLE_TO_STEP_ON, WARP_A, WARP_B };

class EnemyBase :
	public Sprite
{
public:
	virtual bool KasanatteruMouse() = 0;
	bool CheckUp(SceneBase *MG, int Itr);
	int CheckUpLeft(SceneBase *MG, int Itr);
	int CheckUpRight(SceneBase *MG, int Itr);
	bool CheckUpGround();
	bool CheckUpGround(SceneBase * MG, int Itr);
	virtual void Update(SceneBase* MG, int Itr) = 0;
	virtual void Update() = 0;
	virtual void MoveStart() = 0;
	EnemyBase();
	~EnemyBase();
	double GetSitaVY();
	double GetSitaVX();
	void SetMoveF(bool MoveF);
	bool GetMoveF();
	void SetTurnStopCnt(int TurnStopCnt);
	int GetTurnStopCnt();
	void SetEnemyType(int Type);
	int GetEnemyType();
	bool GetMigiMuki();
	void SetMigiMuki(bool MigiMuki);
	EnemyHitType GetHitType();
	int HitKabeF;
	int SitaEnemyF;
	int SitaEnemyDX;
	EnemyBase* SitaEnemy;
	void SetTesuu(int *Tesuu);
protected:
	EnemyHitType HitType;
	BgMgr * Bg;
	int AtariX[2] = { -6,6 };
	int AtariY[2] = { -7,8 };
	int EnemyType;
	double SitaVX, SitaVY;
	bool MoveF;
	int TurnStopCnt;
	bool MigiMuki;
	int *Tesuu;

};

