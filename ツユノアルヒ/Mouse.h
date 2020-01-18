#pragma once
#include "Singleton.h"
#include <string>
#include "Sprite.h"

class Mouse :public Singleton<Mouse>
{
	Mouse();
	friend Singleton<Mouse>;
public:
	int Update();
	//マウスのボタンが押された瞬間を取得
	int GetInputSyunkan();
	int GetInputHanasu();
	void Draw();
	int GetX();
	int GetY();
private:
	int mx, my;
	int State;
	int PastState;
	int ReturnState;
	int HReturnState;
	Sprite ClickEffect;
};