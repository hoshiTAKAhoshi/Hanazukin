#pragma once

class BgMgr
{
public:
	void Initialize();
	void Draw();
	void Draw(int Layer);
	void PutChip(int Layer, int X, int Y, int GrHandle);
	int GetChip(int Layer, int ScreenX, int ScreenY);
	int GetChipBgZahyo(int Layer, int BgX, int BgY);
	void SetExRate(double ExRate);
	void SetXY(int X, int Y);
	int GetX();
	int GetY();
	BgMgr();
	~BgMgr();

private:
	int BgData[3][15][20];
	int X, Y;
	double ExRate;
};

