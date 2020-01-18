#include "BgLayer.h"



void BgLayer::Draw()
{
	for (int y = 0; y < LAYERYSIZE; y++)
	{
		for (int x = 0; x < LAYERXSIZE; x++)
		{
			BgChips[y][x].Draw();
		}
	}

}

BgLayer::BgLayer()
{
	ExRate = 4;
	for (int y = 0; y < LAYERYSIZE; y++)
	{
		for (int x = 0; x < LAYERXSIZE; x++)
		{
			BgChips[y][x].SetXY((8 * ExRate) + x * (16 * ExRate), (8 * ExRate) + y * (16 * ExRate));
			BgChips[y][x].SetGrHandle(-1);
		}
	}
}


BgLayer::~BgLayer()
{
}
