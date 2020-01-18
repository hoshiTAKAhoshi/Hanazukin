#pragma once
#include "Singleton.h"
#include <vector>

#define SD_MODEMAX 2
#define SD_STAGEMAX 13
#define SD_XMAX 12
#define SD_YMAX 9
#define SD_STRMAX 128

typedef struct
{
	char StageData[SD_YMAX*SD_XMAX];
	char StageName[SD_STRMAX];
	char FlowerName[SD_STRMAX];
	char FlowerMessage[SD_STRMAX];
} StageComponent;

class Bank :public Singleton<Bank>
{
	Bank();
	friend Singleton<Bank>;
public:
	void PlaySe(int Num);
	void PlayBgm(int Num);
	void StopBgm(int Num);
	int* GetGrHandle(int Num);
	int* GetSoundHandle(int Num);
	int GetMiniFontHandle();
	char* GetStageData(int Mode, int StageNum);

private:
	int ImageHandle[32][64];
	int SoundHandle[18];
	int MiniFontHandle;
	StageComponent StageComponents[SD_MODEMAX][SD_STAGEMAX];
	/*
	char StageData[SD_MODEMAX][SD_STAGEMAX][SD_YMAX*SD_XMAX];
	char StageName[SD_MODEMAX][SD_STAGEMAX][SD_STRMAX];
	char FlowerName[SD_MODEMAX][SD_STAGEMAX][SD_STRMAX];
	char FlowerMessage[SD_MODEMAX][SD_STAGEMAX][SD_STRMAX];
	*/
};

