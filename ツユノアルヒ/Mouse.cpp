#include "Mouse.h"
#include "DxLib.h"
#include "Bank.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "EffectMgr.h"

Mouse::Mouse()
{
	State = 0;
	PastState = 0;
	ReturnState = 0;
	HReturnState = 0;
	ClickEffect.SetGrHandleData(Bank::Instance()->GetGrHandle(21));
	ClickEffect.SetGrNum(15);
	ClickEffect.SetExRate(4);
}

int Mouse::Update()
{
	GetMousePoint(&mx, &my);


	PastState = State;
	State = GetMouseInput();

	ReturnState = 0;

	//âüÇµÇΩèuä‘
	for (int i = 0; i <= 3; i++)
	{
		int mask = 1 << i;
		if ((PastState & mask) == 0 && (State & mask) != 0)
			ReturnState = ReturnState | mask;
	}
	////printfDx("%d", ReturnState);

	HReturnState = 0;

	//òbÇµÇΩèuä‘
	for (int i = 0; i <= 3; i++)
	{
		int mask = 1 << i;
		if ((PastState & mask) != 0 && (State & mask) == 0)
			HReturnState = HReturnState | mask;
	}

	if (GetInputSyunkan()& MOUSE_INPUT_LEFT)
	{
		int t = 3;
		ClickEffect.SpAnim(3, 1, 4, 2, 5, 3,99,15, 1);
		ClickEffect.SpAnimAlpha(255, t * 5, 100);
		ClickEffect.SetXY(mx, my);
	}
	ClickEffect.Update();
	return 0;
}

int Mouse::GetInputSyunkan()
{
	return ReturnState;
}

int Mouse::GetInputHanasu()
{
	return HReturnState;
}

void Mouse::Draw()
{
	ClickEffect.Draw();
	//DrawRotaGraph(mx + 2, my + 2, 4, 0, Bank::Instance()->GetGrHandle(5)[0], 1);
}

int Mouse::GetX()
{
	return mx;
}

int Mouse::GetY()
{
	return my;
}

