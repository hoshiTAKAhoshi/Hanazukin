#include "Player.h"
#include "Bank.h"
#include "Mouse.h"
#include "DxLib.h"
#include <array>

#define WALK_SPEED 16

void Player::TekiFunda()
{
	VY = -7;
	//VX *= 1.2;
	StandF = 0;
}

void Player::Stop()
{
	StandF = 0;
	MigiMuki = 1;
	VX = 0;
	SpAnim(6 * 60, 0, 8, 9, 8, 0, 8, 9, 0);
	TurnStopCnt = 0;
	ChakuChiCnt = 0;

}

void Player::Move()
{
	if (ChakuChiCnt == 0)
		X += VX;

	
	//右に地面がある
	if (Bg->GetChip(0, X + AtariX[1] * ExRate - 1, Y + AtariY[0] * ExRate + 1) != -1 || Bg->GetChip(0, X + AtariX[1] * ExRate - 1, Y + AtariY[1] * ExRate - 1) != -1)
	{
		X -= 1;
		if (StandF == 1)
		{
			VX = 0;
			ChakuChiCnt = 0;
			SpAnim(10, 8, 10, 0, 10, 0, 18, 4, 1);
			MigiMuki = 0;
			TurnStopCnt = 1;
		}
	}

	//左に地面がある
	if (Bg->GetChip(0, X + AtariX[0] * ExRate, Y + AtariY[0] * ExRate + 1) != -1 || Bg->GetChip(0, X + AtariX[0] * ExRate, Y + AtariY[1] * ExRate - 1) != -1)
	{
		X += 1;
		if (StandF == 1)
		{
			VX = 0;
			ChakuChiCnt = 0;
			SpAnim(10, 12, 10, 4, 10, 4, 18, 0, 1);
			MigiMuki = 1;
			TurnStopCnt = 1;
		}
	}
	
	if (TurnStopCnt > 0)
	{
		TurnStopCnt++;
		if (TurnStopCnt>=50)
		{
			TurnStopCnt = 0;
			if (MigiMuki == 1)
			{
				SpAnim(WALK_SPEED, 1, WALK_SPEED, 2, WALK_SPEED, 3, WALK_SPEED, 2, -1);
				VX = 1;
			}
			else
			{
				SpAnim(WALK_SPEED, 5, WALK_SPEED, 6, WALK_SPEED, 7, WALK_SPEED, 6, -1);
				VX = -1;
			}
		}
	}



	if (StandF == 0)
	{
		Gravity = GetGravity(VY);

		VY += Gravity;
		if (VY <= 0)
		{
			SpAnimStop();
			if (MigiMuki == 1)
				SetGrNum(27);
			else
				SetGrNum(27+4);
		}
		else
		{
			if (GetSpAnimF() == 0)
			{
				if (MigiMuki == 1)
					SpAnim(8,10,8,11,8,10,8,11,0);
				else
					SpAnim(8, 14, 8, 15, 8, 14, 8, 15, 0);
			}
		}
		if (VY > 5)
			VY = 5;
		Y += VY;
	}


	//下に地面がある
	if (Bg->GetChip(0, X + AtariX[0] * ExRate+1, Y + AtariY[1] * ExRate) != -1 || Bg->GetChip(0, X + AtariX[1] * ExRate-1, Y + AtariY[1] * ExRate) != -1)
	{
		if (StandF == 0)
		{
			StandF = 1;
			if (MoveF == 0)
			{
				SpAnimStop();
				if (MigiMuki == 1)
					SetGrNum(0);
				else
					SetGrNum(0 + 4);
			}
			else
			{
				ChakuChiCnt = 1;
				//VX = 0;
				SpAnimStop();
				if (MigiMuki == 1)
					SetGrNum(18);
				else
					SetGrNum(18 + 4);

			}
			
			Y = (int)Y;
			//めり込み防止
			while (Bg->GetChip(0, X + AtariX[0] * ExRate+1, Y + AtariY[1] * ExRate) != -1 || Bg->GetChip(0, X + AtariX[1] * ExRate-1, Y + AtariY[1] * ExRate) != -1)
			{
				Y--;
			}
			Y++;
		}
		//TekiFunda();
	}
	else
	{
		if (StandF == 1)
		{
			StandF = 0;
			VY = 0;
			ChakuChiCnt = 0;
			SpAnimStop();
		}
	}

	if (ChakuChiCnt > 0)
	{
		ChakuChiCnt++;
		if (ChakuChiCnt >= 10)
		{
			if (MigiMuki == 1)
				SetGrNum(2);
			else
				SetGrNum(2 + 4);
		}
		if (ChakuChiCnt >= 26)
		{
			ChakuChiCnt = 0;
			if (MigiMuki == 1)
			{
				SpAnim(WALK_SPEED, 1, WALK_SPEED, 2, WALK_SPEED, 3, WALK_SPEED, 2,  -1);
				VX = 1;
			}
			else
			{
				SpAnim(WALK_SPEED, 5, WALK_SPEED, 6, WALK_SPEED, 7, WALK_SPEED, 6,  -1);
				VX = -1;
			}
		}
	}


	//上に地面がある
	if (Bg->GetChip(0, X + AtariX[0] * ExRate + 1, Y + AtariY[0] * ExRate) != -1 || Bg->GetChip(0, X + AtariX[1] * ExRate - 1, Y + AtariY[0] * ExRate) != -1)
	{
		VY = 0;
		while (Bg->GetChip(0, X + AtariX[0] * ExRate + 1, Y + AtariY[0] * ExRate) != -1 || Bg->GetChip(0, X + AtariX[1] * ExRate - 1, Y + AtariY[0] * ExRate) != -1)
		{
			Y++;
		}
	}
}


void Player::SetMoveF(bool MoveF)
{
	this->MoveF = MoveF;
}

void Player::MoveStart()
{
	MoveF = 1;
	if (MigiMuki == 1)
	{
		SpAnim(WALK_SPEED, 1, WALK_SPEED, 2, WALK_SPEED, 3, WALK_SPEED, 2, -1);
		VX = 1;
	}
	else
	{
		SpAnim(WALK_SPEED, 5, WALK_SPEED, 6, WALK_SPEED, 7, WALK_SPEED, 6, -1);
		VX = -1;
	}
	//FuchiByougaF = -1;

}

void Player::MoveStop()
{
	MoveF = 0;
	VX = 0;
	TurnStopCnt=0;
	ChakuChiCnt = 0;
	SpAnimStop();
	if (MigiMuki == 1)
	{
		GrNum = 0;
	}
	else
	{
		GrNum = 4;
	}

}

void Player::Deth()
{
	VX = 0;
	VY = 0;
	TurnStopCnt = 0;
	ChakuChiCnt = 0;
	SpAnimStop();

}


void Player::ClearInit()
{
	StandF = 0;
	ClearJumpCnt = 0;
	FuchiByougaF = 0;
	VX = 0;
	VY = -2.5;
	Y += VY;
	if (MigiMuki == 1)
	{
		GrNum = 16;
	}
	else
	{
		GrNum = 20;
	}

}
//クリア時にぴょんぴょんする
void Player::ClearUpdate()
{
	if (StandF == 0)
	{
		VY += 0.1;
		if (VY > 5)
			VY = 5;
		Y += VY;
	}

	if (VY > 1)
	{
		if (MigiMuki == 1)
		{
			GrNum = 0;
		}
		else
		{
			GrNum = 4;
		}

	}
	//下に地面がある
	if (Bg->GetChip(0, X + AtariX[0] * ExRate + 1, Y + AtariY[1] * ExRate) != -1 || Bg->GetChip(0, X + AtariX[1] * ExRate - 1, Y + AtariY[1] * ExRate) != -1)
	{

		if (StandF == 0)
		{
			StandF = 1;
			Y = (int)Y;
			//めり込み防止
			while (Bg->GetChip(0, X + AtariX[0] * ExRate + 1, Y + AtariY[1] * ExRate) != -1 || Bg->GetChip(0, X + AtariX[1] * ExRate - 1, Y + AtariY[1] * ExRate) != -1)
			{
				Y--;
			}
			Y++;
		}
		ClearJumpCnt++;
		//if (ClearJumpCnt < 2)
		{
			VY = -2.5;
			StandF = 0;
			if (MigiMuki == 1)
			{
				GrNum = 16;
			}
			else
			{
				GrNum = 20;
			}

		}

	}
	else
	{
		StandF = 0;
	}
	//上に地面がある
	if (Bg->GetChip(0, X + AtariX[0] * ExRate + 1, Y + AtariY[0] * ExRate) != -1 || Bg->GetChip(0, X + AtariX[1] * ExRate - 1, Y + AtariY[0] * ExRate) != -1)
	{
		VY = 0;
		while (Bg->GetChip(0, X + AtariX[0] * ExRate + 1, Y + AtariY[0] * ExRate) != -1 || Bg->GetChip(0, X + AtariX[1] * ExRate - 1, Y + AtariY[0] * ExRate) != -1)
		{
			Y++;
		}
	}

}

double Player::GetGravity(double vy)
{
	std::array<double,8> treshold{-99,    -6.5,    -4,    -2.5,    0,    1,    2,    99};
	double gValue[] = {               0.1,     0.55,   0.1,   0.06,  0.06,  0.08,  0.1 };
	//return 0.1;
	for (int i =0;i<(treshold.size()) - 1;i++)
	{
		if (vy>=treshold[i] && vy<treshold[i + 1])
			return gValue[i];
	}
	return 0.1;
	
}

void Player::Update()
{
	int mx = Mouse::Instance()->GetX();
	int my = Mouse::Instance()->GetY();

	if (mx > X - 8 * ExRate && mx<X + 8 * ExRate &&my>Y - 8 * ExRate && my < Y + 8 * ExRate)
	{
		if (FuchiByougaF == 0)
			FuchiByougaF = 1;
		//クリックされた
		if ((Mouse::Instance()->GetInputSyunkan()  & MOUSE_INPUT_LEFT) != 0)
		{
			if (MoveF == 0)
			{
				//printfDx("qqq");
				(*Tesuu)++;
				////printfDx("うごけ");
				Bank::Instance()->PlaySe(6);
				MoveStart();
				FuchiByougaF = 10;
			}
			else
			{
				//printfDx("qqq");
				(*Tesuu)++;
				////printfDx("とまれ");
				Bank::Instance()->PlaySe(6);
				MoveStop();
				FuchiByougaF = 10;
			}
		}
	}
	else
	{
		FuchiByougaF = 0;
	}
	Sprite::Update();
	Move();
}



void Player::Draw()
{
	Sprite::Draw();
	//DrawString(2, 6, "FINAL", GetColor(255, 255, 255));
	//DrawString(2, 18, "\nブルーファンフラワー\n花言葉「たびにでよう」\n( )     ☆    ☆", GetColor(255, 255, 255));
	/*
	int C = GetColor(50*0.7, 100*0.7, 125*0.7);
	DrawString(12 + 4, 64 * 2 + 4, "\nブルーファンフラワー\n花言葉「旅に出よう」", C);
	DrawString(12 + 4, 64 * 2 - 4, "\nブルーファンフラワー\n花言葉「旅に出よう」", C);
	DrawString(12 + 4, 64 * 2 + 0, "\nブルーファンフラワー\n花言葉「旅に出よう」", C);
	DrawString(12 + 0, 64 * 2 + 4, "\nブルーファンフラワー\n花言葉「旅に出よう」", C);
	DrawString(12 + 0, 64 * 2 - 4, "\nブルーファンフラワー\n花言葉「旅に出よう」", C);
	DrawString(12 + 0, 64 * 2 + 0, "\nブルーファンフラワー\n花言葉「旅に出よう」", C);
	DrawString(12 - 4, 64 * 2 + 4, "\nブルーファンフラワー\n花言葉「旅に出よう」", C);
	DrawString(12 - 4, 64 * 2 - 4, "\nブルーファンフラワー\n花言葉「旅に出よう」", C);
	DrawString(12 - 4, 64 * 2 + 0, "\nブルーファンフラワー\n花言葉「旅に出よう」", C);
	*/
	//DrawString(12, 64*2, "\nブルーファンフラワー\n花言葉「旅に出よう」", GetColor(255, 255, 255));
	//DrawString(2, 22, "\n\n\n C 2018 　TAKA　", GetColor(255, 255, 255));
}

bool Player::GetStandF()
{
	return StandF;
}

void Player::SetBgMgr(BgMgr * Bg)
{
	this->Bg = Bg;
}

void Player::SetBgXY(int BgX,int BgY)
{
	X = BgX * 16 * ExRate + 8 * ExRate + Bg->GetX();
	Y = BgY * 16 * ExRate + 8 * ExRate + Bg->GetY();
}

void Player::Init()
{
	ChakuChiCnt = 0;
	StandF = 1;
	MoveF = 0;
	MigiMuki = 1;
	VX = 0;
	VY = 0;
	GrNum = 0;
	SpAnim(6 * 60, 0, 8, 9, 8, 0, 8, 9, 0);
	TurnStopCnt = 0;
	ClearJumpCnt = 0;

}

void Player::WarpTo(double X, double Y)
{
	this->X = X;
	this->Y = Y;
}

bool Player::KasanatteruMouse()
{
	int mx = Mouse::Instance()->GetX();
	int my = Mouse::Instance()->GetY();

	if (mx > X - 8 * ExRate && mx<X + 8 * ExRate &&my>Y - 8 * ExRate && my < Y + 8 * ExRate)
	{
		return true;
	}
	return false;
}

void Player::SetTesuu(int * Tesuu)
{
	this->Tesuu = Tesuu;
}

Player::Player()
{
	ChakuChiCnt = 0;
	ExRate = 4;
	StandF = 0;
	MoveF = 0;
	MigiMuki = 1;
	VX = 0;
	//VX = 1;
	//X =-1 * 16 * ExRate;
	//Y =5 * 16 * ExRate;
	//VY = -2;
	GrHandleData = Bank::Instance()->GetGrHandle(0);
	GrNum = 0;
	SpAnim(6*60, 0, 8, 9, 8, 0, 8, 9, 0);
	TurnStopCnt = 0;
	ClearJumpCnt = 0;
	SetColSqr(AtariX[0], AtariY[0], AtariX[1], AtariY[1]);
}


Player::~Player()
{
}
