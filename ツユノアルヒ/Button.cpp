#include "Button.h"
#include "Mouse.h"
#include "Bank.h"
#include "DxLib.h"

bool Button::GetOsareta()
{
	return Osareta;
}

void Button::SetActiveF(bool ActiveF)
{
	if (ActiveF == 0)
	{
		//SpAnim(2, GrHandleBase + 1, 2, GrHandleBase+2, 2, GrHandleBase+2, 2, GrHandleBase+2, 1);
		DrawAlpha = 60;
	}
	else
	{
		//if (this->ActiveF == 0)
			//SpAnim(2, GrHandleBase + 2, 2, GrHandleBase+3, 2, GrHandleBase, 2, GrHandleBase, 1);
		DrawAlpha = 255;
	}
	this->ActiveF = ActiveF;
}

void Button::Update()
{
	Sprite::Update();
	if (Osareta == 1)
		Osareta = 0;
	OsaretaP = Osareta;

	if (ActiveF == 1)
	{
		int mx = Mouse::Instance()->GetX();
		int my = Mouse::Instance()->GetY();

		if (mx > X - Width / 2 && mx<X + Width / 2 && my>Y - Height / 2 && my < Y + Height / 2)
		{
			if (FuchiByougaF == 0)
				FuchiByougaF = 1;
			if (Mouse::Instance()->GetInputSyunkan() & MOUSE_INPUT_LEFT)
			{
				FuchiByougaF = 1;
				Bank::Instance()->PlaySe(7);
				Osareta = 1;
				//GrNum = GrHandleBase+1;
				SpAnim(2, GrHandleBase + 1, 2, GrHandleBase + 2, 2, GrHandleBase + 3, 2, GrHandleBase, 1);
			}
			if (Mouse::Instance()->GetInputHanasu() & MOUSE_INPUT_LEFT)
			{
				//GrNum = GrHandleBase;
			}


		}
		else
		{
			FuchiByougaF = 0;
			GrNum = GrHandleBase;
		}
	}
	else
	{
		FuchiByougaF = 0;
	}
}

void Button::Draw()
{
	Sprite::Draw();
}

Button::Button(int GrHandleBase, int X, int Y, int Width, int Height)
{
	this->GrHandleBase = GrHandleBase;
	this->X = X;
	this->Y = Y;
	this->Width = Width;
	this->Height = Height;
	GrHandleData = Bank::Instance()->GetGrHandle(4);
	GrNum = GrHandleBase;
	ExRate = 4;
	Osareta = 0;
	OsaretaP = 0;
	ActiveF = 1;
}

Button::Button(int* GrHandleData,int GrHandleBase, int X, int Y, int Width, int Height)
{
	this->GrHandleBase = GrHandleBase;
	this->X = X;
	this->Y = Y;
	this->Width = Width;
	this->Height = Height;
	this->GrHandleData = GrHandleData;
	GrNum = GrHandleBase;
	ExRate = 4;
	Osareta = 0;
	OsaretaP = 0;
	ActiveF = 1;
}


Button::~Button()
{
}
