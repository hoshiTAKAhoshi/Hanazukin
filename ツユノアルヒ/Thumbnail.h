#pragma once
#include "Sprite.h"

#define MINICHAR_WIDTH 3
#define MINICHAR_XMAX 12
#define MINICHAR_YMAX 9

#define WAKU_WIDTH MINICHAR_WIDTH*MINICHAR_XMAX*4
#define WAKU_HEIGHT MINICHAR_WIDTH*MINICHAR_YMAX*4

//enum IToC{E=0,S,G,a,f,z};

class Thumbnail
{
public:
	Thumbnail(int StageNum, int X, int Y,int ActiveF);
	~Thumbnail();
	void Update();
	void Draw();
	void OpenKey();
	void SetActiveF(int ActiveF);
	int GetActiveF();
	int GetOsaretaF();
private:
	int StageNum;
	int X, Y;
	int* GrHandle;
	int* KiranHandle;
	int GrMap[9][12];
	char* StageData;
	char ItoC[16] = "EeSGafzYn,,QO\0";
	Sprite Kiran;
	int Kasanatteru;
	int ActiveF;
	Sprite Kagi;
	int KagiClickCnt;
	int KagiBrbrCnt;
	int OsaretaF;
	int OsaretaCnt;
	double DY;
};
