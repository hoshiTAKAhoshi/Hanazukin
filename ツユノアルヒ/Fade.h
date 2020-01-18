#pragma once
#include "Sprite.h"

class Fade
{
public:
	void SetCnt(int Cnt);
	void SetDrawRGB(int R, int G, int B);
	void SetDrawAlpha(int DrawAlpha);
	int GetCnt();
	int GetFadeInF();
	int GetFadeOutF();
	void FadeInStart();
	void FadeInStartOsyare();
	void FadeOutStart();
	void FadeOutStartOsyare();
	void Update();
	void Draw();
	Fade(int StartY, int DrawAlpha, int R, int G, int B);
	~Fade();

private:
	int FadeInF;
	int FadeOutF;
	int StartY;
	double ExRate;
	int Cnt;
	int* GrHandleData;
	Sprite Chip[9][12];
};

