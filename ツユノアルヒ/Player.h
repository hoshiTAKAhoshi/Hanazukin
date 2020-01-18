#pragma once
#include "Sprite.h"
#include "BgMgr.h"

typedef struct
{
	double X, Y;
}position;

class Player :
	public Sprite
{
public:
	void TekiFunda();
	void Stop();
	void Move();
	void SetMoveF(bool MoveF);
	void MoveStart();
	void MoveStop();
	void Deth();
	void ClearInit();
	void ClearUpdate();
	double GetGravity(double vy);
	void Update();
	void Draw();
	bool GetStandF();
	void SetBgMgr(BgMgr* Bg);
	void SetBgXY(int BgX, int BgY);
	void Init();
	void WarpTo(double X, double Y);
	bool KasanatteruMouse();
	void SetTesuu(int *Tesuu);
	Player();
	~Player();
private:
	BgMgr *Bg;
	bool MigiMuki;
	bool StandF;
	int TurnStopCnt;
	int ClearJumpCnt;
	int ChakuChiCnt;
	bool MoveF;
	int AtariX[2] = { -4,4 };
	int AtariY[2] = { -6,8 };
	int *Tesuu;
	double Gravity=0.1;
	//int AtariUe[2][2] = { {-6 * 4,-8 * 4},{6 * 8,8 * 4} };
};

