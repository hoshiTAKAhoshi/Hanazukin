#pragma once
#include "Sprite.h"
class Button :
	public Sprite
{
public:
	bool GetOsareta();
	void SetActiveF(bool ActiveF);
	void Update();
	void Draw();
	Button(int GrHandleBase, int X, int Y, int Width, int Height);
	Button(int * GrHandleData, int GrHandleBase, int X, int Y, int Width, int Height);
	~Button();
private:
	bool Osareta;
	bool OsaretaP;
	bool ActiveF;
	int GrHandleBase;
	int Width, Height;
};

