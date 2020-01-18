#pragma once
class BgChip
{
public:
	void Draw();
	void SetXY(int X, int Y);
	int GetX();
	int GetY();
	void SetGrHandle(int GrHandle);
	int GetGrHandle();
	BgChip();
	~BgChip();
	double ExRate;
private:
	int GrHandle;
	int X;
	int Y;
};

