#include "StagePutter.h"
#include "Bank.h"
#include "Slime.h"
#include "Frog.h"
#include "WarpMan.h"
#include "KaminariSama.h"
#include "Boss.h"
#include "EffectMgr.h"
#include "NewMainGame.h"
#include "DxLib.h"
#include <stdio.h>


int StagePutter::GetStageMax(char StageNameData[128][128])
{
	int StageMax;
	char FileName[128];
	for (int i = 1; i < 99; i++)
	{
		sprintf_s(FileName, "StageData/%d.txt\0", i);
		int FileHandle;
		FileHandle = FileRead_open(FileName);

		if (FileHandle == 0)
		{
			StageMax = i - 1;
			break;
		}

		int EndF = 0;
		while (!EndF)
		{
			char temp[256];
			FileRead_gets(temp, 256, FileHandle);
			//�R�����g����������X�L�b�v
			if (temp[0] == '\'' || temp[0] == '\0')
			{
				continue;
			}

			for (int j = 0; j < 256; j++)
			{
				StageNameData[i][j] = temp[j];
				if (temp[j] == '\0')
				{
					EndF = 1;
					break;
				}
			}
		}




		FileRead_close(FileHandle);

	}
	return StageMax;
}



void StagePutter::PutStage(int StageNum)
{
	*((NewMainGame*)MG)->GetTesuuPt()=0;

	char FileName[64];
	sprintf_s(FileName, "StageData/%d.txt\0", StageNum);
	////printfDx("FileName=%s", FileName);
	int FileHandle;
	FileHandle = FileRead_open(FileName);
	
	//�t�@�C������������
	if (FileHandle == 0)
	{
		////printfDx("�ˁ[��");
		return;
	}

	//�G��delete����
	while (!Enemy->empty())
	{
		delete Enemy->back();
		Enemy->pop_back();
	}

	//������kill
	KogeMgr->Init();

	KaminariMgr->Init();
	
	//effectkill
	EffectMgr::Instance()->Kill();

	//�E��kill
	YusyaKun->SetXY(-64, -64);
	YusyaKun->SetNegaF(0);
	BeemF[0] = 0;
	BeemF[1] = 0;
	BeemF[2] = 0;
	////printfDx("%d", FileHandle);
	int Cnt = 0;
	char StageData[10][13];
	int sdY = 0;
	
	while (FileRead_eof(FileHandle)==0)
	{

		char temp[256];
		FileRead_gets(temp, 256, FileHandle);
		//�R�����g����������X�L�b�v
		if (temp[0] == '\'' || temp[0] == '\0')
		{
			continue;
		}

		switch (Cnt)
		{
		case 0://�X�e�[�W�̖��O
			for (int i = 0; i < 256; i++)
			{
				StageName[i] = temp[i];
				if (temp[i] == '\0')
					break;
			}
			Cnt = 1;
			break;
		case 1://�Ԃ̖��O
			for (int i = 0; i < 256; i++)
			{
				FlowerName[i] = temp[i];
				if (temp[i] == '\0')
					break;
			}
			Cnt = 2;
			break;
		case 2://�Ԍ��t
			for (int i = 0; i < 256; i++)
			{
				FlowerMessage[i] = temp[i];
				if (temp[i] == '\0')
					break;
			}
			Cnt = 3;
			break;
		case 3://�X�e�[�W�f�[�^
			for (int sdX = 0; sdX < 13; sdX++)
			{
				StageData[sdY][sdX]=temp[sdX];
			}
			sdY++;
			break;
		}

	}

	int* JimenHandle = Bank::Instance()->GetGrHandle(1);
	int* FlowerHandle = Bank::Instance()->GetGrHandle(2);
	int CheckMawari;
	int MawariKami[16] = { 0,12,4,8,3,15,7,11,1,13,5,9,2,14,6,10 };
	//BG���v�b�g���悤�I�I�I
	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			Bg->PutChip(0, x, y, -1);
			Bg->PutChip(1, x, y, -1);
			Bg->PutChip(2, x, y, -1);
			//if(StageNum>=11)
				//Bg->PutChip(2, x, y, JimenHandle[18]);

			switch (StageData[y][x])
			{
			case 'E'://�n��
				CheckMawari = 0;
				if (y - 1 >= 0 && StageData[y - 1][x] == 'E')
					CheckMawari += 1;
				if (y + 1 < 9 &&StageData[y + 1][x] == 'E')
					CheckMawari += 2;
				if (x - 1 >= 0 && StageData[y][x - 1] == 'E')
					CheckMawari += 4;
				if (x + 1 < 12 && StageData[y][x + 1] == 'E')
					CheckMawari += 8;

				Bg->PutChip(0, x, y, JimenHandle[MawariKami[CheckMawari]+(StageNum>=11)*32]);
				Bg->PutChip(2, x, y, -1);
				break;
			case 'n'://���肩��
				Bg->PutChip(2, x, y, JimenHandle[16]);
				Bg->PutChip(2, x-3, y, JimenHandle[17]);
				break;
			case 'S'://��l��
				Hito->SetBgXY(x, y);
				Hito->Init();
				/*
				Hito->SetVY(0);
				Hito->SetMoveF(0);
				Hito->Stop();
				*/
				break;
			case 'Y'://�䂤����
				YusyaKun->Init();
				YusyaKun->SetBgXY(x, y);
				YusyaKun->SetGrNum(0);
				if (StageNum == 7)
				{
					YusyaKun->SetGrNum(5);
				}
				break;
			case 'G'://����
				Bg->PutChip(1, x, y, FlowerHandle[StageNum]);
				break;
			case 'a'://�X���C��
				Enemy->push_back(new Slime(x, y, Bg));
				(*Enemy)[Enemy->size() - 1]->SetTesuu(((NewMainGame*)MG)->GetTesuuPt());
				break;
			case 'f'://�J�G��
				Enemy->push_back(new Frog(x, y, Bg));
				(*Enemy)[Enemy->size() - 1]->SetTesuu(((NewMainGame*)MG)->GetTesuuPt());
				break;
			case 'z'://���l
				Enemy->push_back(new KaminariSama(x, y, Bg, KaminariMgr));
				(*Enemy)[Enemy->size() - 1]->SetTesuu(((NewMainGame*)MG)->GetTesuuPt());
				break;
			case 'O'://���[�v�}��A
				Enemy->push_back(new WarpMan(x, y, Bg, 0));
				((NewMainGame*)MG)->SetWarpManA(Enemy->at(Enemy->size()-1));
				(*Enemy)[Enemy->size() - 1]->SetTesuu(((NewMainGame*)MG)->GetTesuuPt());
				break;
			case 'Q'://���[�v�}��B
				Enemy->push_back(new WarpMan(x, y, Bg, 1));
				((NewMainGame*)MG)->SetWarpManB(Enemy->at(Enemy->size()-1));
				(*Enemy)[Enemy->size() - 1]->SetTesuu(((NewMainGame*)MG)->GetTesuuPt());
				break;
			case 'B'://�{�X
				Enemy->push_back(new Boss(x*16*4+16*4+4*16*4, y*16*4, Bg, Enemy,YusyaKun));
				(*Enemy)[Enemy->size() - 1]->SetTesuu(((NewMainGame*)MG)->GetTesuuPt());
				break;
			case 'L':
				Bg->PutChip(0, x, y-2, JimenHandle[20]);
				Bg->PutChip(0, x, y-1, JimenHandle[24]);
				Bg->PutChip(0, x, y, JimenHandle[28]);

			}
		}
	}
	FileRead_close(FileHandle);
}



StagePutter::StagePutter(BgMgr * Bg, Player * Hito, Yusya * YusyaKun, std::vector<EnemyBase*>* Enemy, ThunderMgr * KaminariMgr, OutLineMgr * KogeMgr, bool *BeemF, char * StageName, char * FlowerName, char * FlowerMessage, SceneBase* MG)
{
	this->Bg = Bg;
	this->Hito = Hito;
	this->YusyaKun = YusyaKun;
	this->Enemy = Enemy;
	this->KaminariMgr = KaminariMgr;
	this->KogeMgr = KogeMgr;
	this->BeemF = BeemF;
	this->StageName = StageName;
	this->FlowerName = FlowerName;
	this->FlowerMessage = FlowerMessage;
	this->MG = MG;
}

StagePutter::~StagePutter()
{
}
