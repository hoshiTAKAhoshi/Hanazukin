#pragma once
#include "Singleton.h"
class Shake :
	public Singleton<Shake>
{
	Shake();
	friend Singleton<Shake>;
public:
	int Update();
	void Start(int ShakeTime, int ShakeHaba);
	int GetX();
	int GetY();
	~Shake();

private:
	bool ShakeF;
	int ShakeTime;
	int ShakeHaba;
	int Cnt;
	int X, Y;
	int Haba;
};

