#pragma once
#include "BgChip.h"
#define LAYERYSIZE 15
#define LAYERXSIZE 20

class BgLayer
{
public:
	void Draw();
	BgLayer();
	~BgLayer();
	double ExRate;
	BgChip BgChips[LAYERYSIZE][LAYERXSIZE];
};

