#pragma once

enum Dire { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };

class OutLineMgr
{
public:
	void Update();
	void Draw();
	void KillLine(int X, int Y);
	void SetLine(int X, int Y, Dire Direction);
	void Init();
	OutLineMgr();
	~OutLineMgr();
private:
	int OutLineData[9][12][4];//[y][x][ã‰º¶‰E•ûŒü]
	int* GrHandleData;
};

