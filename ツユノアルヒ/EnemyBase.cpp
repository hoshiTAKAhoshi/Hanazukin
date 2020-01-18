#include "EnemyBase.h"
#include "MainGame.h"
#include "DxLib.h"
#include "Mouse.h"


//1:上に地面ある
bool EnemyBase::CheckUp(SceneBase * MG, int Itr)
{
	if (CheckUpGround(MG, Itr) == true)
	{
		//printfDx("*************************");
		return true;
	}
	int ItrLeft = CheckUpLeft(MG, Itr);
	int ItrRight = CheckUpRight(MG, Itr);

	//どっちもいる
	if (ItrLeft != -1 && ItrRight != -1)
	{
		//printfDx("どっちも　");
		return CheckUp(MG, ItrLeft) + CheckUp(MG, ItrRight);
	}
	//ひだりだけ
	if (ItrLeft != -1 && ItrRight == -1)
	{
		//printfDx("ひだり　");
		return CheckUp(MG, ItrLeft);
	}
	//みぎだけ
	if (ItrLeft == -1 && ItrRight != -1)
	{
		//printfDx("みぎ　");
		return CheckUp(MG, ItrRight);
	}
	//printfDx("なにもない　");
	//上になにもない
	return false;

}

int EnemyBase::CheckUpLeft(SceneBase * MG, int Itr)
{
	EnemyBase* Jibun = ((MainGame*)MG)->Enemy[Itr];
	int CheckZahyoX = Jibun->GetX() + Jibun->AtariX[0] * 4;
	int CheckZahyoY = Jibun->GetY() + Jibun->AtariY[0] * 4-8;
	//左上に敵がいたらItrを返す
	for (int i = 0; i < ((MainGame*)MG)->Enemy.size(); i++)
	{
		if (i == Itr)
			continue;
		EnemyBase* Aite = ((MainGame*)MG)->Enemy[i];

		if (CheckZahyoX >= Aite->GetX() + AtariX[0] * 4 && CheckZahyoX <= Aite->GetX() + AtariX[1] * 4)
		{
			if (CheckZahyoY >= Aite->GetY() + AtariY[0] * 4 && CheckZahyoY <= Aite->GetY() + AtariY[1] * 4)
			{
				return i;
			}
		}
	}
	return -1;
}

int EnemyBase::CheckUpRight(SceneBase * MG, int Itr)
{
	EnemyBase* Jibun = ((MainGame*)MG)->Enemy[Itr];
	int CheckZahyoX = Jibun->GetX() + Jibun->AtariX[1] * 4;
	int CheckZahyoY = Jibun->GetY() + Jibun->AtariY[0] * 4-8;
	//右上に敵がいたらItrを返す
	for (int i = 0; i < ((MainGame*)MG)->Enemy.size(); i++)
	{
		if (i == Itr)
			continue;
		EnemyBase* Aite = ((MainGame*)MG)->Enemy[i];

		if (CheckZahyoX >= Aite->GetX() + AtariX[0] * 4 && CheckZahyoX <= Aite->GetX() + AtariX[1] * 4)
		{
			if (CheckZahyoY >= Aite->GetY() + AtariY[0] * 4 && CheckZahyoY <= Aite->GetY() + AtariY[1] * 4)
			{
				return i;
			}
		}
	}
	return -1;
}

bool EnemyBase::CheckUpGround()
{
	//上に地面があったらtrue
	if (Bg->GetChip(0, X + AtariX[0] * 4 + 1, Y + AtariY[0] * 4) != -1 || Bg->GetChip(0, X + AtariX[1] * 4 - 1, Y + AtariY[0] * 4) != -1)
		return true;
	return false;
}

bool EnemyBase::CheckUpGround(SceneBase * MG, int Itr)
{
	EnemyBase* E = ((MainGame*)MG)->Enemy[Itr];
	//上に地面があったらtrue
	if (Bg->GetChip(0, E->GetX() + E->AtariX[0] * 4 + 1, E->GetY() + E->AtariY[0] * 4) != -1 || Bg->GetChip(0, E->GetX() + E->AtariX[1] * 4 - 1, E->GetY() + E->AtariY[0] * 4) != -1)
		return true;
	return false;
}

EnemyBase::EnemyBase()
{
}


EnemyBase::~EnemyBase()
{
}

double EnemyBase::GetSitaVY()
{
	return SitaVY;
}

double EnemyBase::GetSitaVX()
{
	return SitaVX;
}

void EnemyBase::SetMoveF(bool MoveF)
{
	this->MoveF = MoveF;
}

bool EnemyBase::GetMoveF()
{
	return MoveF;
}

void EnemyBase::SetTurnStopCnt(int TurnStopCnt)
{
	this->TurnStopCnt = TurnStopCnt;
}

int EnemyBase::GetTurnStopCnt()
{
	return TurnStopCnt;
}

void EnemyBase::SetEnemyType(int Type)
{
	EnemyType = Type;
}

int EnemyBase::GetEnemyType()
{
	return EnemyType;
}

bool EnemyBase::GetMigiMuki()
{
	return MigiMuki;
}

void EnemyBase::SetMigiMuki(bool MigiMuki)
{
	this->MigiMuki = MigiMuki;
}

EnemyHitType EnemyBase::GetHitType()
{
	return HitType;
}

void EnemyBase::SetTesuu(int * Tesuu)
{
	this->Tesuu = Tesuu;
}

