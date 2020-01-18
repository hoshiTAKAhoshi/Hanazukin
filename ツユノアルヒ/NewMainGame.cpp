#define _CRT_SECURE_NO_WARNINGS
#include "NewMainGame.h"
#include "DxLib.h"
#include "Bank.h"
#include "Slime.h"
#include "Frog.h"
#include "KaminariSama.h"
#include "Mouse.h"
#include "TkDrawString.h"
#include "Shake.h"
#include "Window.h"
#include "Boss.h"
#include "Iwa.h"
#include "EffectMgr.h"
#include <stdio.h>

void NewMainGame::Collision()
{
	if (Hito.GetNegaF() == 1)
	{
		Hito.SetVY(0);
		for (int i = 0; i < Enemy.size(); i++)
			Enemy[i]->SetVY(0);

		return;
	}
	//�G�Ɠ�������
	for (int i = 0; i < Enemy.size(); i++)
	{
		if (Hito.CheckHitSp((Sprite*)Enemy[i]))
		{
			switch (Enemy[i]->GetHitType())
			{
			case ABLE_TO_STEP_ON:
				//���ݔ���
				if (Hito.GetVY() > 0 && Hito.GetY() + 6 * EXRATE < Enemy[i]->GetY() && Enemy[i]->GetHitType() == ABLE_TO_STEP_ON)
				{
					while (Hito.CheckHitSp((Sprite*)Enemy[i]))
					{
						Hito.SetXY(Hito.GetX(), Hito.GetY() - 1);
					}
					Bank::Instance()->PlaySe(2);
					Hito.TekiFunda();
					switch (Enemy[i]->GetEnemyType())
					{
					case 0:
						delete (Slime*)Enemy[i];
						break;
					case 1:
						delete (Frog*)Enemy[i];
						break;
					case 2:
						delete (KaminariSama*)Enemy[i];
						break;
					}
					Enemy.erase(Enemy.begin() + i);
					i--;
					//Enemy[i]->SetXY(192*5, 144*5);
				}
				else//���S����
				{
					//�G�̓������~�߂�
					for (int i = Enemy.size() - 1; i >= 0; i--)
					{
						Enemy[i]->SpAnimStop();
						Enemy[i]->SetVX(0);
						Enemy[i]->SetVY(0);
					}
					Hito.SetVY(0);

					if (Hito.GetNegaF() == 0)
					{
						Bank::Instance()->PlaySe(8);
						Hito.SetNegaF(1);
						Hito.Deth();
						Shake::Instance()->Start(30, 7);


						//��蒼������
						ToReStart = 1;
						MiniButton[2]->SetActiveF(0);
						MiniButton[3]->SetActiveF(0);
						FadeLayer[0]->SetDrawRGB(255, 255, 255);
						FadeLayer[0]->SetCnt(-15);
						FadeLayer[0]->FadeInStart();

					}////printfDx("����");
				}

				break;
			case NOT_ABLE_TO_STEP_ON:
				//�G�̓������~�߂�
				for (int i = Enemy.size() - 1; i >= 0; i--)
				{
					Enemy[i]->SpAnimStop();
					Enemy[i]->SetVX(0);
					Enemy[i]->SetVY(0);
				}
				Hito.SetVY(0);

				if (Hito.GetNegaF() == 0)
				{
					Bank::Instance()->PlaySe(8);
					Hito.SetNegaF(1);
					Hito.Deth();
					Shake::Instance()->Start(30, 7);


					//��蒼������
					ToReStart = 1;
					MiniButton[2]->SetActiveF(0);
					MiniButton[3]->SetActiveF(0);
					FadeLayer[0]->SetDrawRGB(255, 255, 255);
					FadeLayer[0]->SetCnt(-15);
					FadeLayer[0]->FadeInStart();

				}////printfDx("����");

				break;
			case WARP_A:
				if (WarpF == 0)
				{
					Hito.WarpTo(WarpManB->GetX(), WarpManB->GetY());
					EffectMgr::Instance()->SetEffect(WarpManA->GetX(), WarpManA->GetY(), Bank::Instance()->GetGrHandle(24), STOP, 28, 7, 0, 7, 1, 7, 2, 7, 3, 1);
					EffectMgr::Instance()->SetEffect(WarpManB->GetX(), WarpManB->GetY(), Bank::Instance()->GetGrHandle(24), STOP, 25, 7, 4, 8, 5, 9, 6, 5, 7, 1);
					Bank::Instance()->PlaySe(17);
					WarpF = 1;
				}
				break;
			case WARP_B:
				if (WarpF == 0)
				{
					Hito.WarpTo(WarpManA->GetX(), WarpManA->GetY());
					EffectMgr::Instance()->SetEffect(WarpManB->GetX(), WarpManB->GetY(), Bank::Instance()->GetGrHandle(24), STOP, 28, 7, 0, 7, 1, 7, 2, 7, 3, 1);
					EffectMgr::Instance()->SetEffect(WarpManA->GetX(), WarpManA->GetY(), Bank::Instance()->GetGrHandle(24), STOP, 25, 7, 4, 8, 5, 9, 6, 5, 7, 1);
					Bank::Instance()->PlaySe(17);
					WarpF = 1;
				}

				break;
			}
		}
	}

	if (WarpManA!=nullptr && !(Hito.CheckHitSp(WarpManA) || Hito.CheckHitSp(WarpManB)))
	{
		WarpF = 0;
	}

	//������
	if (Hito.GetY() > 144 * 4 + 32 || Hito.GetX()<0 - 32 || Hito.GetX()>192 * 4 + 32)
	{
		//�G�̓������~�߂�
		for (int i = Enemy.size() - 1; i >= 0; i--)
		{
			Enemy[i]->SpAnimStop();
			Enemy[i]->SetVX(0);
			Enemy[i]->SetVY(0);
		}
		Hito.SetVY(0);

		if (Hito.GetNegaF() == 0)
		{
			Bank::Instance()->PlaySe(8);
			Hito.SetNegaF(1);
			Hito.SpAnimStop();
			Hito.SetVX(0);
			Shake::Instance()->Start(40, 8);


			//��蒼������
			ToReStart = 1;
			MiniButton[2]->SetActiveF(0);
			MiniButton[3]->SetActiveF(0);
			FadeLayer[0]->SetDrawRGB(255, 255, 255);
			FadeLayer[0]->SetCnt(-15);
			FadeLayer[0]->FadeInStart();
		}
	}

	//���d��
	if (KaminariMgr->CheckHitHito() == 1)
	{
		//�G�̓������~�߂�
		for (int i = Enemy.size() - 1; i >= 0; i--)
		{
			Enemy[i]->SpAnimStop();
			Enemy[i]->SetVX(0);
			Enemy[i]->SetVY(0);
		}
		Hito.SetVY(0);

		if (Hito.GetNegaF() == 0)
		{
			Bank::Instance()->PlaySe(8);
			Hito.SetNegaF(1);
			Hito.SpAnimStop();
			Hito.SetVX(0);
			Shake::Instance()->Start(40, 8);


			//��蒼������
			ToReStart = 1;
			MiniButton[2]->SetActiveF(0);
			MiniButton[3]->SetActiveF(0);
			FadeLayer[0]->SetDrawRGB(255, 255, 255);
			FadeLayer[0]->SetCnt(-15);
			FadeLayer[0]->FadeInStart();
		}

	}
}


void NewMainGame::YusyaCollision()
{
	//�G�Ɠ�������
	for (int i = 0; i < Enemy.size(); i++)
	{
		if (YusyaKun.CheckHitSp((Sprite*)Enemy[i]))
		{
			{
				//�G�̓������~�߂�
				for (int i = Enemy.size() - 1; i >= 0; i--)
				{
					Enemy[i]->SpAnimStop();
					Enemy[i]->SetVX(0);
					Enemy[i]->SetVY(0);
				}
				YusyaKun.SetVY(0);

				if (YusyaKun.GetNegaF() == 0)
				{
					Bank::Instance()->PlaySe(8);
					YusyaKun.SetNegaF(1);
					YusyaKun.SpAnimStop();
					YusyaKun.SetVX(0);
					Shake::Instance()->Start(30, 7);


					//��蒼������
					ToReStart = 1;
					MiniButton[2]->SetActiveF(0);
					MiniButton[3]->SetActiveF(0);
					FadeLayer[0]->SetDrawRGB(255, 255, 255);
					FadeLayer[0]->SetCnt(-15);
					FadeLayer[0]->FadeInStart();

				}////printfDx("����");
			}
		}
	}

}


//�N���A����
void NewMainGame::CheckClear()
{
	if (Bg.GetChip(1, Hito.GetX(), Hito.GetY()) != -1)
	{
		if (Hito.GetStandF() == 1 && Hito.GetNegaF() == 0)
		{
			Bank::Instance()->PlaySe(5);
			Hito.ClearInit();
			char str[128];
			sprintfDx(str, "�w%s�x�� \n�Ăɂ��ꂽ�I�I\n�͂Ȃ��Ƃ� \n�w%s�x", FlowerName, FlowerMessage);
			/*
			if (NowStage == 0)
				sprintfDx(str, "�w%s�x�� \n�Ăɂ��ꂽ\n�͂Ȃ��Ƃ� \n�w%s�x", FlowerName, FlowerMessage);
			else
				sprintfDx(str, "�N���A�[�I�I\n\n%s \n�w%s�x", FlowerName, FlowerMessage);
			*/
			if (Hito.GetY() >= 16 * 5 * 4)
				Window::Instance()->PutWindow(0, str);
			else
				Window::Instance()->PutWindow(1, str);


			for (int i = 0; i < 6; i++)
			{
				MojiX2[i] = 192 * 2 - 30 * 4 + 10 * 4 * i;
				MojiY2[i] = -144 * 2;
			}
			MojiCnt2 = 0;

			//FadeLayer[1]->SetDrawAlpha(170);
			FadeLayer[2]->SetCnt(0);
			FadeLayer[2]->FadeInStartOsyare();

			if (PlayAbleStage < NowStage + 1)
			{
				PlayAbleStage = NowStage + 1;

				//�Z�[�u����

				fopen_s(&fp, "SaveData.dat", "wb");
				int tmp[1];
				tmp[0] = PlayAbleStage;
				////printfDx("tmp[0]=%d\n", tmp[0]);
				fwrite(tmp, sizeof(int), 1, fp);
				fclose(fp);
			}

			MainGameMode = CLEAR;
			//ClearMati = 1;
		}
	}
	/*
	if (ClearMati == 1)
	{
	//�G�̓������~�߂�
	for (int i = Enemy.size() - 1; i >= 0; i--)
	{
	Enemy[i]->SpAnimStop();
	Enemy[i]->SetVX(0);
	Enemy[i]->SetVY(0);
	}
	Hito.SpAnimStop();
	Hito.SetVX(0);
	Hito.SetVY(0);
	if (FadeLayer[1]->GetFadeInF() == -1)
	{
	for (int i = 0; i < 6; i++)
	{
	MojiX2[i] = 192 * 2 - 30 * 4 + 10 * 4 * i;
	MojiY2[i] = -144 * 2;
	}
	MojiCnt2 = 0;
	Hito.ClearInit();
	MainGameMode = CLEAR;
	}
	}
	*/
}


void NewMainGame::MiniButtonUpdate()
{
	for (int i = 0; i < 4; i++)
	{
		MiniButton[i]->Update();
	}
}

void NewMainGame::StageSelectUpdate()
{
	int mx = Mouse::Instance()->GetX();
	int my = Mouse::Instance()->GetY();

	//�X�^�[�g
	if (mx >= 0 && mx <= 768 && my >= 64 && my <= 576)
	{
		if (StartFuchiF == 0)
		{
			MojiCnt = 0;
			StartFuchiF = 1;
		}
		if ((Mouse::Instance()->GetInputSyunkan()) & MOUSE_INPUT_LEFT)
		{
			MiniButton[0]->SetActiveF(0);
			MiniButton[1]->SetActiveF(0);
			MiniButton[2]->SetActiveF(0);
			MiniButton[3]->SetActiveF(0);
			StartFuchiF = 0;
			ClearMati = 0;


			ToMainGame = 1;
		}
	}
	else
	{
		StartFuchiF = 0;
	}

	if (ToMainGame == 1)
	{
		if (FadeLayer[0]->GetCnt() == 0)
		{
			FadeLayer[1]->SetCnt(15);
			FadeLayer[1]->FadeOutStartOsyare();
			Bank::Instance()->StopBgm(1);
			if (NowStage >= 11)
			{
				//Bank::Instance()->PlayBgm(9);
			}
			else
				Bank::Instance()->PlayBgm(0);
			/*
			if (NowStage == 1)
			{
			SerifCnt = 1;
			Window::Instance()->PutWindow(0, "���̂���� �Ȃ܂��� \n�u�͂Ȃ�����v�ł��B\n�ǂ���� �͂Ȃ����񂿂��� \n���͂Ȃ� ���߂��� �悤�ł��B\n������ �߂̂܂��ɂ� ���Ȃ����� \n�Ȃ�� �Ă��܂� ���܂��B\n�ޏ��� ������ ���₦�Ă��܂�\n�^���Ȃ̂ł��傤���E�E�E \n����A����Ȃ��Ƃ� ����܂���I\n\n�Ȃ��Ȃ� �J�~�T�}�ł��� \n���Ȃ��� ������ ���邩��ł��I\n�ł́A���������ł��� �Ă��� \n�N���b�N ���Ă݂Ă��������B");
			}
			*/
			SerifCnt = 0;
			MainGameMode = MAINGAME;
		}
	}

	//�O�̃X�e�[�W
	if (MiniButton[0]->GetOsareta() == 1)
	{
		if (FadeLayer[0]->GetFadeInF() != 1)
			FadeLayer[0]->FadeInStart();
		NowStage--;
		//printfDx(StageName, "%s", StageNameData[NowStage]);
		MiniButton[1]->SetActiveF(1);
		if (NowStage == 0)
			MiniButton[0]->SetActiveF(0);
	}
	if (FadeLayer[0]->GetFadeInF() == -1)
	{
		StageOkuyo->PutStage(NowStage);
		FadeLayer[0]->FadeOutStart();

	}

	//���̃X�e�[�W
	if (MiniButton[1]->GetOsareta() == 1)
	{
		if (FadeLayer[0]->GetFadeInF() != 1)
			FadeLayer[0]->FadeInStart();
		NowStage++;
		//printfDx(StageName, "%s", StageNameData[NowStage]);
		//StageName = &StageNameData[NowStage];
		MiniButton[0]->SetActiveF(1);
		if (NowStage == StageMax || NowStage == PlayAbleStage)
			MiniButton[1]->SetActiveF(0);
	}
	if (FadeLayer[0]->GetFadeInF() == -1)
	{
		StageOkuyo->PutStage(NowStage);
		FadeLayer[0]->FadeOutStart();

	}

	//�^�C�g���ɖ߂�
	if (MiniButton[3]->GetOsareta() == 1)
	{
		SM->ChangeScene(TITLESCENE);
		MiniButton[0]->SetActiveF(0);
		MiniButton[1]->SetActiveF(0);
		MiniButton[2]->SetActiveF(0);
		MiniButton[3]->SetActiveF(0);

	}

	MojiUpdate();

}

void NewMainGame::MainGameUpdate()
{
	////printfDx("%d", SerifCnt);

	//�X�e�[�W�P�̃`���[�g���A��
	if (NowStage == 0)
	{
		if (SerifCnt >= 4 && SerifCnt != 5)
		{
			Hito.Update();
		}
		else
		{
			//Hito.SpAnimUpdate();
			//Hito.DrawFuchiEffect();
		}

		//if (Window::Instance()->GetWindowNow() <=0 || (SerifCnt >= 2 && SerifCnt != 5))
		if (SerifCnt >= 2 && SerifCnt != 5)
		{
			for (int i = 0; i < Enemy.size(); i++)
			{
				(Enemy[i])->Update();
			}

			for (int i = Enemy.size() - 1; i >= 0; i--)
			{
				////printfDx("\n[%d]", i);
				//(Enemy[i])->Update(this, i);
				if ((Enemy[i])->KasanatteruMouse() == 1)
					break;
			}

		}
		else
		{
			//(Enemy[0])->SpAnimUpdate();
			//(Enemy[0])->DrawFuchiEffect();

		}

		//�u�N���b�N���Ă��������v�ŃX���C�����N���b�N�ł���悤�ɂ��邽��
		if (SerifCnt == 1 && Window::Instance()->GetGyoCnt() == 13)
		{
			SerifCnt = 2;
		}

		if (SerifCnt == 2 && (Enemy[0])->GetY() >= 420)
		{
			SerifCnt = 3;
			Window::Instance()->PutWindow(0, "�������܂����ˁI\n\n���ꂪ ���Ȃ��� ������ł��B\n\n�Â��� �͂Ȃ����񂿂��� \n�N���b�N ���Ă݂Ă��������B");
		}

		//�u�N���b�N���Ă��������v�ł͂Ȃ�������N���b�N�ł���悤�ɂ��邽��
		if (SerifCnt == 3 && Window::Instance()->GetGyoCnt() == 5)
		{
			SerifCnt = 4;
		}

		if (SerifCnt == 4 && Hito.GetX() >= 96 + 16 * 4)
		{
			SerifCnt = 5;
			Hito.SetFuchiByougaF(0);
			Enemy[0]->SetFuchiByougaF(0);
			Window::Instance()->PutWindow(0, "���邫�����܂����ˁI\n\n����� �͂Ȃ����񂿂��� \n���Ȃɂ����� �Ă��� �ӂ��\n���͂Ȃ� �Ƃ���� \n���ǂ���� �͂��ł��B\n���̂悤�� �u�Ă��� ������āv \n�͂Ȃ����񂿂���\n���͂Ȃ� �Ƃ����\n�݂��т��� �����Ă��������I\n�킽������ ���������邱�Ƃ� \n�����傤�ł��B\n����ł́A\n�O�b�h���b�N�I�I�I");

		}

		if (SerifCnt == 5 && Window::Instance()->GetWindowNow() <= 0)
		{
			SerifCnt = 6;
		}

	}
	else if (NowStage == 3)//�E�ҌN�Ƃ̏��Ζ�
	{
		if (SerifCnt == 2 || SerifCnt == 4 || SerifCnt == 6)
		{
			Hito.Update();
		}
		YusyaKun.Update();
		/*
		for (int i = 0; i < Enemy.size(); i++)
		{
		(Enemy[i])->Update();
		}

		for (int i = Enemy.size() - 1; i >= 0; i--)
		{
		////printfDx("\n[%d]", i);
		//(Enemy[i])->Update(this, i);
		if ((Enemy[i])->KasanatteruMouse() == 1)
		{
		for (int j = i - 1; j >= 0; j--)
		{
		(Enemy[j])->SetFuchiByougaF(0);
		}
		break;
		}
		}
		*/

		if (SerifCnt == 1 && Window::Instance()->GetGyoCnt() == 6)
		{
			YusyaKun.SetGrNum(0);
		}
		if (SerifCnt == 1 && Window::Instance()->GetGyoCnt() == 11)
		{
			YusyaKun.SetGrNum(12);
		}

		//�ŏ��̃Z���t���I����ĉԓ��Ђ𓮂�����悤�ɂ���
		if (SerifCnt == 1 && Window::Instance()->GetWindowNow() <= 0)
		{
			YusyaKun.SetGrNum(0);
			SerifCnt = 2;
		}

		//�͂Ȃ�����ɋC�Â�
		if (SerifCnt == 2 && Hito.GetX() >= 16 * 4 * 4)
		{
			SerifCnt = 3;
			YusyaKun.SetGrNum(16);
			Window::Instance()->PutWindow(0, "�E�E�E \n�I�H�I�H\n���A�A���A�A \n�݂Ă��E�E�E�H\n���[�ƁE�E�E   \n�R�z���B\n���̂������ �����X�^�[ ���炯�� \n�L�P��������A\n�������� ���������ق��� ������");
		}

		//�Q�ڂ̃Z���t���I����ĉԓ��Ђ𓮂�����悤�ɂ���
		if (SerifCnt == 3 && Window::Instance()->GetWindowNow() <= 0)
		{
			SerifCnt = 4;
		}

		//�˂������Ă�H
		if (SerifCnt == 4 && Hito.GetX() >= 16 * 8 * 4)
		{
			SerifCnt = 5;
			YusyaKun.SetGrNum(0);
			Window::Instance()->PutWindow(0, "�E�E�E�˂��A \n�����Ă�H");
		}

		//�R�ڂ̃Z���t���I����ĉԓ��Ђ𓮂�����悤�ɂ���
		if (SerifCnt == 5 && Window::Instance()->GetWindowNow() <= 0)
		{
			SerifCnt = 6;
		}


	}
	else if (NowStage == 7)
	{
		if (SerifCnt == 2 || SerifCnt == 4 || SerifCnt == 7)
		{
			Hito.Update();
		}
		YusyaKun.Update();
		/*
		for (int i = 0; i < Enemy.size(); i++)
		{
		(Enemy[i])->Update();
		}

		for (int i = Enemy.size() - 1; i >= 0; i--)
		{
		////printfDx("\n[%d]", i);
		//(Enemy[i])->Update(this, i);
		if ((Enemy[i])->KasanatteruMouse() == 1)
		{
		for (int j = i - 1; j >= 0; j--)
		{
		(Enemy[j])->SetFuchiByougaF(0);
		}
		break;
		}
		}
		*/

		//�ŏ��̃Z���t���I����ĉԓ��Ђ𓮂�����悤�ɂ���
		if (SerifCnt == 1 && Window::Instance()->GetWindowNow() <= 0)
		{
			SerifCnt = 2;
		}

		//�͂Ȃ�����ɋC�Â�
		if (SerifCnt == 2 && Hito.GetX() >= 16 * 5.5 * 4)
		{
			Hito.MoveStop();
			SerifCnt = 3;
			YusyaKun.SetGrNum(15);
			Window::Instance()->PutWindow(0, "���E�E�E \n�L�~�� ���̂Ƃ��́E�E�E\n�悭 �����܂� �Ԃ��� \n���ǂ�����ˁE�E�E\n�E�E�E\n\n���́E�E�E \n\n�悩������ ��������� \n�₷��ł��Ȃ��E�E�E�H");
		}

		//�Q�ڂ̃Z���t���I����ĉԓ��Ђ𓮂�����悤�ɂ���
		if (SerifCnt == 3 && Window::Instance()->GetWindowNow() <= 0)
		{
			SerifCnt = 4;
		}

		//�͂Ȃ�����ɋC�Â�
		if (SerifCnt == 4 && Hito.GetX() >= 16 * 7.5 * 4)
		{
			Hito.MoveStop();
			Hito.SetGrNum(21);
			SerifCnt = 5;
			Window::Instance()->PutWindow(0, "�E�E�E\n\n���݂� ������ �Ȃɂ����Ă�́H\n\n�E�E�E�������A \n���͂Ȃ� ���߂Ă�񂾁B\n�E�E�E    \n�X�e�L���ˁB\n�E�E�E \n���A�{�N�H\n�{�N�� �����̂� \n������Ă�񂾁I\n������ ���̂����ɂ��� ������� \n���₾�܂� ����� �������Ȃ��B\n�{�N�� ������ �������āA\n\n���̂������� �ւ���� \n�Ƃ���ǂ��񂾁I�I�I\n�E�E�E   \n�����ƁE�E�E\n���A���������Ⴂ���Ȃ��I�I\n\n�͂₭ �����Ȃ��ƁI\n\n�E�E�E���A���ꂶ�Ⴀ�I");
		}

		if (SerifCnt == 5)
		{
			if (Window::Instance()->GetGyoCnt() == 20)
			{
				YusyaKun.SetGrNum(0);
			}
			if (Window::Instance()->GetGyoCnt() == 24)
			{
				SerifCnt = 6;
				YusyaKun.SpAnim(10, 1, 10, 2, 10, 3, 10, 2, 0);
			}
		}
		if (SerifCnt == 6)
		{
			YusyaKun.SetXY(YusyaKun.GetX() + 4, YusyaKun.GetY());
			if (YusyaKun.GetX() > 192 * 4 + 8 * 4)
			{
				SerifCnt = 7;
				Hito.SetGrNum(0);
			}
		}

	}
	else if (NowStage == 11)
	{
		if (SerifCnt == 7)
		{
			Hito.Update();

			YusyaKun.UpdateBoss1();
			YusyaCollision();
			((Boss*)Enemy[0])->UpdateDai1();

			for (int i = 0; i < Enemy.size(); i++)
			{
				(Enemy[i])->Update();
			}

			for (int i = Enemy.size() - 1; i >= 0; i--)
			{
				////printfDx("\n[%d]", i);
				//(Enemy[i])->Update(this, i);
				if ((Enemy[i])->KasanatteruMouse() == 1)
				{
					for (int j = i - 1; j >= 0; j--)
					{
						(Enemy[j])->SetFuchiByougaF(0);
					}
					break;
				}
			}
		}

		//�̂��Ƃ�ꂽ�Ƃ��̏���
		if (SerifCnt == 13)
		{
			Hito.Update();

			YusyaKun.UpdateNottori();

			double hX = Hito.GetX();
			double hY = Hito.GetY();
			double yX = YusyaKun.GetX();
			double yY = YusyaKun.GetY();

			//�͂Ȃ����񂪌��ɐG��Ď���
			if (YusyaKun.GetNottoriCnt() >= 63 && YusyaKun.GetNottoriCnt() <= 63 + 3 + 12)
			{
				if (pow(hX - yX, 2) + pow(hY - yY, 2) < pow(8 * 4 + 20 * 4, 2))
				{
					if (Hito.GetNegaF() == 0)
						Bank::Instance()->PlaySe(8);
					Hito.SetNegaF(1);
					Hito.SpAnimStop();
					Hito.SetVX(0);
					Shake::Instance()->Start(30, 7);


					//��蒼������
					ToReStart = 1;
					MiniButton[2]->SetActiveF(0);
					MiniButton[3]->SetActiveF(0);
					FadeLayer[0]->SetDrawRGB(255, 255, 255);
					FadeLayer[0]->SetCnt(-15);
					FadeLayer[0]->FadeInStart();

				}
			}

			if (Hito.CheckHitSp(&YusyaKun) == 1 && Hito.GetNegaF() == 0 && Hito.GetStandF()==1)
			{
				if (Hito.GetNegaF() == 0)
					Bank::Instance()->PlaySe(8);
				Hito.SetNegaF(1);
				Hito.SpAnimStop();
				Hito.SetVX(0);
				Shake::Instance()->Start(30, 7);


				//��蒼������
				ToReStart = 1;
				MiniButton[2]->SetActiveF(0);
				MiniButton[3]->SetActiveF(0);
				FadeLayer[0]->SetDrawRGB(255, 255, 255);
				FadeLayer[0]->SetCnt(-15);
				FadeLayer[0]->FadeInStart();

			}


			//�E�҂𓥂݂���
			if (hX >= yX - 12 * 4 && hX <= yX + 12 * 4 && hY >= yY - 14 * 4 && hY <= yY - 8 * 4)
			{
				Bank::Instance()->PlaySe(2);
				YusyaKun.SetGrNum(31);
				Hito.TekiFunda();

				SerifCnt = 14;
			}


			//((Boss*)Enemy[0])->UpdateDai1();

			for (int i = 0; i < Enemy.size(); i++)
			{
				(Enemy[i])->Update();
			}

			for (int i = Enemy.size() - 1; i >= 0; i--)
			{
				////printfDx("\n[%d]", i);
				//(Enemy[i])->Update(this, i);
				if ((Enemy[i])->KasanatteruMouse() == 1)
				{
					for (int j = i - 1; j >= 0; j--)
					{
						(Enemy[j])->SetFuchiByougaF(0);
					}
					break;
				}
			}
		}

		if (SerifCnt == 14)
		{
			Hito.Update();
			YusyaKun.UpdateTaore();
			//���̕����ɐi��
			if (Hito.GetX() >= 11.5 * 16 * 4 && FadeLayer[0]->GetFadeInF() == 0)
			{
				FadeLayer[0]->FadeInStartOsyare();
			}

			if (FadeLayer[0]->GetFadeInF() == -1)
			{
				StageOkuyo->PutStage(100);
				FadeLayer[0]->FadeOutStartOsyare();
				SerifCnt = 15;
				Bank::Instance()->StopBgm(9);

			}

			for (int i = 0; i < Enemy.size(); i++)
			{
				(Enemy[i])->Update();
			}

			for (int i = Enemy.size() - 1; i >= 0; i--)
			{
				////printfDx("\n[%d]", i);
				//(Enemy[i])->Update(this, i);
				if ((Enemy[i])->KasanatteruMouse() == 1)
				{
					for (int j = i - 1; j >= 0; j--)
					{
						(Enemy[j])->SetFuchiByougaF(0);
					}
					break;
				}
			}

		}


		//����~�点��
		if (SerifCnt >= 11 && SerifCnt <= 14)
		{
			EventCnt++;
			if (EventCnt >= 120)
			{
				EventCnt = 0;
				Enemy.push_back(new Iwa);
			}
		}

		//�������̂ւ�
		if (SerifCnt == 15)
		{

		}

		if (SerifCnt == 1 && Window::Instance()->GetGyoCnt() == 5)
		{
			YusyaKun.SetGrNum(16);
		}


		////printfDx("[%d]", Window::Instance()->GetWindowNow());
		//�ŏ��̃Z���t���I����ă{�X�̃Z���t
		if (SerifCnt == 1 && Window::Instance()->GetWindowNow() == -1)
		{
			EventCnt++;
			if (EventCnt >= 30)
			{
				EventCnt = 0;
				SerifCnt = 2;
				YusyaKun.SetGrNum(0);
				Window::Instance()->PutWindow(0, "�����ɂ���̂� ���ꂾ�I�I");
			}
		}

		//�{�X�W�����v�����ݒ�
		if (SerifCnt == 2 && Window::Instance()->GetWindowNow() == -1)
		{

			Enemy[0]->SetVY(-8.8);
			SerifCnt = 3;

		}

		if (SerifCnt == 3)
		{
			double bX = Enemy[0]->GetX();
			double bY = Enemy[0]->GetY();
			double bVY = Enemy[0]->GetVY();

			bVY += 0.2;
			bY += bVY;
			Enemy[0]->SetVY(bVY);
			Enemy[0]->SetXY(bX - 3, bY);

			if ((int)Enemy[0]->GetY() >= 6 * 16 * 4)
			{
				Bank::Instance()->PlaySe(4);
				Enemy[0]->SetXY(Enemy[0]->GetX() + 1, 6 * 16 * 4);
				Shake::Instance()->Start(30, 8);
				SerifCnt = 4;
				EventCnt = 0;
			}
		}

		if (SerifCnt == 4)
		{
			if (EventCnt < 60)
			{
				EventCnt++;
			}
			else
			{
				SerifCnt = 5;
				Window::Instance()->PutWindow(0, "�ł��ȁA���₾�܂߁I�I\n\n���̂������� �ւ���� \n�݂������c�́A\n���̃{�N�� ��邳�Ȃ��I�I \n����������I�I");
			}
		}

		if (SerifCnt == 5 && Window::Instance()->GetWindowNow() == -1)
		{
			SerifCnt = 6;
			Window::Instance()->PutWindow(0, "�t���A���킯�B\n\n�I�}�G������ �����ɂ������ƁA\n�Ƃ��� �������� �����Ă���I");
		}

		if (SerifCnt == 6 && Window::Instance()->GetWindowNow() == -1)
		{
			SerifCnt = 7;
			Bank::Instance()->PlayBgm(9);
			YusyaKun.MoveStart();
		}


		if (SerifCnt == 7)
		{
			if (((Boss*)Enemy[0])->GetHp() == 0 && YusyaKun.GetNegaF() == 0)
			{
				SerifCnt = 8;
				Bank::Instance()->StopBgm(9);
				Window::Instance()->PutWindow(0, "�����A�I�}�G�B\n\n�I�}�G����B���߂�� �ނ����� \n�J�~�T�}����您�B\n�R�C�c��������� �I���T�}�� \n���Ă�Ƃł� �����������H\n���킹��ȁB\n����� �������B\n�Ȃ������āH \n����͂Ȃ��E�E�E");
			}
		}

		if (SerifCnt == 8 && Window::Instance()->GetWindowNow() == 0)
		{
			SerifCnt = 9;
			Window::Instance()->PutWindowDeka(0, "�I���T�}��\n\n�w�J�~�T�}�x\n\n������Ȃ��I�I");
		}

		if (SerifCnt == 9 && Window::Instance()->GetWindowNow() == -1)
		{
			YusyaKun.SpAnimStop();
			YusyaKun.SetGrNum(24);
			YusyaKun.SetVY(-4);
			SerifCnt = 10;
		}

		//�E�ґ�����
		if (SerifCnt == 10)
		{
			double bX = YusyaKun.GetX();
			double bY = YusyaKun.GetY();
			double bVY = YusyaKun.GetVY();

			bVY += 0.1;
			bY += bVY;
			YusyaKun.SetVY(bVY);
			YusyaKun.SetXY(bX - 1, bY);

			if ((int)YusyaKun.GetY() >= 6.5 * 16 * 4)
			{
				YusyaKun.SetXY(YusyaKun.GetX() + 1, 6.5 * 16 * 4);
				Shake::Instance()->Start(30, 8);
				SerifCnt = 11;
				EventCnt = 0;
			}
		}

		//�{�X������
		if (SerifCnt == 11 && Window::Instance()->GetWindowNow() == -1)
		{
			Enemy[0]->SpAnimStop();
			Enemy[0]->SetGrNum(8);
			Enemy[0]->SetVY(-8.8);
			EventCnt = 0;
			Enemy.push_back(new Iwa);
			SerifCnt = 12;
			Bank::Instance()->PlayBgm(9);
			Bank::Instance()->PlaySe(3);

		}

		if (SerifCnt == 12)
		{
			double bX = Enemy[0]->GetX();
			double bY = Enemy[0]->GetY();
			double bVY = Enemy[0]->GetVY();

			bVY += 0.2;
			bY += bVY;
			Enemy[0]->SetVY(bVY);
			Enemy[0]->SetXY(bX + 3, bY);

			if ((int)Enemy[0]->GetY() >= 6 * 16 * 4)
			{
				Enemy[0]->SetXY(Enemy[0]->GetX() + 1, 6 * 16 * 4);
				//Shake::Instance()->Start(30, 8);
				YusyaKun.NottoriInit();
				SerifCnt = 13;
				EventCnt = 0;
			}
		}

		if (SerifCnt == 15)
		{
			if (FadeLayer[0]->GetFadeOutF() == -1)
			{
				if (YusyaKun.GetNottorareF() == 1)
				{
					SerifCnt = 16;
					Window::Instance()->PutWindow(0, "�t���A�L�T�}�ЂƂ�Ł@\n�Ȃɂ��ł���� �����̂��B\n�݂̂قǂ� \n���������点�Ă��I�I�I�I");
				}
				else
				{
					SerifCnt = 16;
					Window::Instance()->PutWindow(0, "�t���A�L�T�}�ЂƂ�Ł@\n�Ȃɂ��ł���� �����̂��B");

				}
			}
		}

		//�o�b�h�G���h
		if (YusyaKun.GetNottorareF() == 1)
		{
			if (SerifCnt == 16)
			{
				if (Window::Instance()->GetWindowNow() == -1)
				{
					Bank::Instance()->PlaySe(4);
					SerifCnt = 17;
					BeemF[0] = 1;
					BeemX[0][0] = Enemy[0]->GetX() - 12;
					BeemY[0][0] = 6 * 16 * 4 - 2 * 4;
					BeemX[0][1] = Enemy[0]->GetX() - 12;
					BeemY[0][1] = 7 * 16 * 4 - 2 * 4;
					Enemy[0]->SetGrNum(2);
				}
			}
			if (SerifCnt == 17)
			{
				BeemX[0][0] -= 12;
				//����
				if (BeemX[0][0] <= Hito.GetX())
				{
					Bank::Instance()->PlaySe(8);
					Hito.SetNegaF(1);
					Hito.SpAnimStop();
					Hito.SetVX(0);
					Shake::Instance()->Start(30, 7);


					//��蒼������
					ToReStart = 1;
					MiniButton[2]->SetActiveF(0);
					MiniButton[3]->SetActiveF(0);
					FadeLayer[0]->SetDrawRGB(255, 255, 255);
					FadeLayer[0]->SetCnt(-15);
					FadeLayer[0]->FadeInStart();
					SerifCnt = 18;
				}
			}
		}
		else//�O�b�h�G���h
		{
			if (SerifCnt == 16 && Window::Instance()->GetWindowNow() == -1)
			{
				SerifCnt = 17;
				Window::Instance()->PutWindow(0, "�ЂƂ肶��Ȃ��I�I�I�I�I");
			}
			if (SerifCnt == 17 && Window::Instance()->GetWindowNow() == 0)
			{
				SerifCnt = 18;
				YusyaKun.SetXY(-8 * 4, 6.5 * 16 * 4);
				YusyaKun.SpAnim(10, 1, 10, 2, 10, 3, 10, 2, 5);
			}
			if (SerifCnt == 18)
			{
				YusyaKun.Update();
				YusyaKun.SetXY(YusyaKun.GetX() + 2, 6.5 * 16 * 4);
				if (YusyaKun.GetX() >= 1.5 * 16 * 4 + 3 * 4)
				{
					SerifCnt = 19;
					YusyaKun.SpAnimStop();
					YusyaKun.SetGrNum(0);
				}
			}

			if (SerifCnt == 19)
			{
				SerifCnt = 20;
				Window::Instance()->PutWindow(0, "�ӂ��肾���� �ǂ������B\n\n�E�E�E���傤�ǂ����B\n\n�܂Ƃ߂� ���܂��Ă��I�I�I�I");
			}
			if (SerifCnt == 20 && Window::Instance()->GetGyoCnt() == 4)
			{
				Enemy[0]->SetGrNum(1);

			}
			if (SerifCnt == 20 && Window::Instance()->GetWindowNow() == -1)
			{
				SerifCnt = 21;
				Window::Instance()->PutWindow(0, "�����͂����Ȃ��I�I�I�I�I\n\n����� �Ƃǂ߂��I�I�I�I");
				YusyaKun.SetGrNum(12);
				Hito.SetGrNum(23);
			}
			if (SerifCnt == 21 && Window::Instance()->GetWindowNow() == -1)
			{
				Bank::Instance()->PlaySe(4);
				SerifCnt = 22;
				BeemF[0] = 1;
				BeemX[0][0] = Enemy[0]->GetX() - 4 * 4;
				BeemY[0][0] = 5 * 16 * 4 + 3 * 4;
				BeemX[0][1] = Enemy[0]->GetX() - 4 * 4;
				BeemY[0][1] = 6 * 16 * 4 + 3 * 4;
				BeemF[1] = 1;
				BeemX[1][0] = 2 * 16 * 4 + 3 * 4;
				BeemY[1][0] = 5 * 16 * 4 + 3 * 4;
				BeemX[1][1] = 2 * 16 * 4 + 3 * 4;
				BeemY[1][1] = 6 * 16 * 4 + 3 * 4;
				Shake::Instance()->Start(30, 14);
				Bank::Instance()->PlayBgm(9);

			}
			if (SerifCnt == 22)
			{
				BeemX[0][0] -= 8;
				BeemX[1][1] += 8;
				if (BeemX[0][0] <= BeemX[1][1])
				{
					SerifCnt = 23;
					BeemF[2] = 1;
					BeemCenterX = BeemX[1][1];
					BeemCenterY = BeemY[1][0] + (BeemY[1][1] - BeemY[1][0]) / 2;
					Shake::Instance()->Start(30, 12);
					Bank::Instance()->PlaySe(4);

				}
			}
			if (SerifCnt == 23)
			{
				Shake::Instance()->Start(5, BeemCenterX/50);
				BeemCenterX -= BeemCenterX / (192.0 * 2) + 0.5;
				if (Mouse::Instance()->GetInputSyunkan() & MOUSE_INPUT_LEFT)
				{
					Bank::Instance()->PlaySe(6);
					BeemCenterX += 32;
				}

				//�܂�
				if (BeemCenterX < BeemX[1][0])
				{
					Bank::Instance()->PlaySe(8);
					Hito.SetNegaF(1);
					Hito.SpAnimStop();
					Hito.SetVX(0);
					Shake::Instance()->Start(30, 7);

					//��蒼������
					ToReStart = 1;
					MiniButton[2]->SetActiveF(0);
					MiniButton[3]->SetActiveF(0);
					FadeLayer[0]->SetDrawRGB(255, 255, 255);
					FadeLayer[0]->SetCnt(-15);
					FadeLayer[0]->FadeInStart();
					SerifCnt = 99;

				}

				//����
				if (BeemCenterX > BeemX[0][1])
				{
					Bank::Instance()->StopBgm(9);
					Bank::Instance()->PlaySe(12);
					SerifCnt = 24;
					EventCnt = 255;
					Shake::Instance()->Start(100, 20);
					//Bank::Instance()->PlaySe(4);
					Enemy[0]->SetXY(-128, -128);
					BeemF[0] = 0;
					BeemF[1] = 0;
					BeemF[2] = 0;
					YusyaKun.SetXY(YusyaKun.GetX() - 12, YusyaKun.GetY());
					YusyaKun.SetGrNum(0);
					Hito.SetGrNum(4);
				}


				BeemX[0][0] = BeemCenterX;
				BeemX[1][1] = BeemCenterX;
			}

			if (SerifCnt == 24)
			{
				EventCnt -= 3;
				if (EventCnt <= 3)
				{
					SerifCnt = 25;
					EventCnt = 0;
				}
			}

			if (SerifCnt == 25)
			{
				EventCnt++;
				if (EventCnt >= 60)
				{
					EventCnt = 0;
					SerifCnt = 26;
					Window::Instance()->PutWindow(0, "��A������I�I�I�I\n\n���������I�I�I�I�I\n\n�E�E�E \n�Ȃ񂾂� ���傤�̃{�N�� \n������� �悩���� \n���������B\n�E�E�E \n�L�~�� ���������ȁB\n���肪�Ƃ��B\n\n�E�E�E�������A\n\n�������� ����� \n�����Ƃ��Ă��炦�Ȃ����ȁB\n�`���[���b�v�B\n\n���ꂢ�� �����Ă������� \n�L�~�� �݂������āB\n�ǂ��H�@\n���ɂ����� ���炦�����ȁB\n�E�E�E\n\n���ꂶ�Ⴀ�A\n\n����������B");
				}
			}
			if (SerifCnt == 26)
			{
				if (Window::Instance()->GetGyoCnt() == 16)
				{
					YusyaKun.SetGrNum(14);
				}
				if (Window::Instance()->GetGyoCnt() == 20)
				{
					YusyaKun.SetGrNum(0);
					Hito.SetGrNum(28);
				}
				if (Window::Instance()->GetWindowNow() == 0)
				{
					SerifCnt = 27;
					FadeLayer[0]->SetDrawRGB(255, 255, 255);
					FadeLayer[0]->SetCnt(0);
					FadeLayer[0]->FadeInStartOsyare();
					EventCnt = 0;
				}
			}
			if (SerifCnt == 27)
			{
				EventCnt++;
				if (EventCnt >= 60)
				{
					SerifCnt = 28;
					Window::Instance()->PutWindow(1, "�s���N�� �`���[���b�v�� \n�͂Ȃ��Ƃ΂́A\n�w������ �߂΂��x \n�������ł��B\n�Ȃ񂾂� �Ƃ��Ă� \n�قق��܂����ł��ˁB\n�E�E�E�������āA���̂������� \n�ւ��킪 ���Ƃ���A\n�������ȁu�����v��\n�߂΂����̂ł����B\n�����܂��B\n\n�������܂� ������ł���� \n���肪�Ƃ��I�I");
				}
			}

			if (SerifCnt == 28 && Window::Instance()->GetWindowNow() == -1)
			{
				SM->ChangeScene(TITLESCENE);
			}

		}




		////printfDx("%d", (int)Enemy[0]->GetY());
	}
	else
	{
		Hito.Update();

		for (int i = 0; i < Enemy.size(); i++)
		{
			(Enemy[i])->Update();
		}


		if (Hito.KasanatteruMouse() == 1)
		{
			for (int i = Enemy.size()-1; i >= 0; i--)
			{
				(Enemy[i])->SetFuchiByougaF(0);
			}
		}
		else
		{
			for (int i = Enemy.size() - 1; i >= 0; i--)
			{
				////printfDx("\n[%d]", i);
				//(Enemy[i])->Update(this, i);
				if ((Enemy[i])->KasanatteruMouse() == 1)
				{
					for (int j = i - 1; j >= 0; j--)
					{
						(Enemy[j])->SetFuchiByougaF(0);
					}
					break;
				}
			}
		}
	}

	KaminariMgr->Update();

	Collision();
	CheckClear();

	//�J�ڊ���
	if (FadeLayer[0]->GetFadeOutF() == -1)
	{
		//�`���[�g���A��
		if (NowStage == 0)
		{
			MiniButton[2]->SetActiveF(0);
			MiniButton[3]->SetActiveF(1);
			SerifCnt = 1;
			Window::Instance()->PutWindow(0, "���̂���� �Ȃ܂��� \n�u�͂Ȃ�����v�ł��B\n�ǂ���� �͂Ȃ����񂿂��� \n���͂Ȃ� ���߂��� �悤�ł��B\n������ �߂̂܂��ɂ� ���Ȃ����� \n�Ȃ�� �Ă��܂� ���܂��B\n�ޏ��� ������ ���₦�Ă��܂�\n�^���Ȃ̂ł��傤���E�E�E \n����A����Ȃ��Ƃ� ����܂���I\n\n�Ȃ��Ȃ� �J�~�T�}�ł��� \n���Ȃ��� ������ ���邩��ł��I\n�ł́A���������ł��� �Ă��� \n�N���b�N ���Ă݂Ă��������B");
		}

	}
	if (SM->FadeLayer->GetFadeOutF() == -1)
		{
		if (NowStage != 0)
		{
			MiniButton[2]->SetActiveF(1);
			MiniButton[3]->SetActiveF(1);
			//Hito.MoveStart();
		}


		//�E�ҌN�Ƃ̏o����
		if (NowStage == 3)
		{
			MiniButton[2]->SetActiveF(0);
			MiniButton[3]->SetActiveF(1);
			SerifCnt = 1;
			YusyaKun.SetGrNum(6);
			Window::Instance()->PutWindow(0, "���`��E�E�E \n�������� ���̂������ \n�����X�^�[�� ������傤�� \n�͂����� ���Ă�ȁE�E�E\n�������� \n�ǂ����� ���ƂȂ񂾁E�E�E\n�E�E�E����A�Ȃ��ł����� \n�������Ȃ��ȁI\n�Ȃɂ� �����낤�� �{�N�� \n������ �������� �̂݁I�I\n���� �������� �ւ���� \n�{�N�� �܂����Ă݂���I�I�I");
		}

		//�E�ҌN�Ƃ̋x��
		if (NowStage == 7)
		{
			MiniButton[2]->SetActiveF(0);
			MiniButton[3]->SetActiveF(1);
			SerifCnt = 1;
			Window::Instance()->PutWindow(0, "�������E�E�E\n\n���̃{�N�� ����ȃ����X�^�[�� \n�����񂷂�Ȃ�āE�E�E\n�͂��E�E�E");
		}

		//�{�X��
		if (NowStage == 11)
		{
			Bank::Instance()->StopBgm(9);
			MiniButton[2]->SetActiveF(0);
			MiniButton[3]->SetActiveF(1);
			SerifCnt = 1;
			EventCnt = 0;
			Window::Instance()->PutWindow(0, "������ �����납�E�E�E\n\n�͂����� ���₾�܂� ������ \n����̂��낤���E�E�E\n�E�E�E  \n�����I�H\n�Ȃ�� �L�~�� �����ɁI�H\n\n�E�E�E�܁A�������B\n�������� �����܂� �����Ȃ�A\n�{�N�� �J�b�R���� \n���񂳂΂��� �݂Ă��Ă�I");
		}

		ToMainGame = 0;

	}

	//��蒼��
	if (MiniButton[2]->GetOsareta() == 1 && ToReStart == 0)
	{
		ToReStart = 1;
		MiniButton[2]->SetActiveF(0);
		MiniButton[3]->SetActiveF(0);
		FadeLayer[0]->SetDrawRGB(255, 255, 255);
		FadeLayer[0]->FadeInStart();
	}
	if (ToReStart == 1)
	{
		if (FadeLayer[0]->GetCnt() == 15)
		{

			StageOkuyo->PutStage(NowStage);
			if (NowStage == 11)
			{
				Bank::Instance()->PlayBgm(9);
				if (SerifCnt >= 12)
				{
					Enemy[0]->SetXY(2000, 2000);
					YusyaKun.NottoriInit();
					YusyaKun.SetXY(4 * 16 * 4, YusyaKun.GetY());
					SerifCnt = 12;
				}
				else
				{
					Enemy[0]->SetXY(10 * 16 * 4, 6 * 16 * 4);
					SerifCnt = 7;
					YusyaKun.MoveStart();

				}
			}
			ClearMati = 0;
			Hito.SetNegaF(0);
			KaminariMgr->SetHitHitoF(0);
			FadeLayer[0]->FadeOutStart();
		}
		if (FadeLayer[0]->GetFadeOutF() == -1)
		{
			MiniButton[2]->SetActiveF(1);
			MiniButton[3]->SetActiveF(1);
			if (NowStage == 11)
				MiniButton[2]->SetActiveF(0);

			ToReStart = 0;
		}
	}

	//�X�e�[�W�I����ʂɖ߂�
	if (MiniButton[3]->GetOsareta() == 1 && ToSelectStage == 0)
	{

		//ToSelectStage = 1;
		MiniButton[2]->SetActiveF(0);
		MiniButton[3]->SetActiveF(0);
		SM->ChangeScene(SELECTSTAGESCENE);
		//FadeLayer[0]->SetCnt(0);
		//FadeLayer[0]->SetDrawRGB(0, 0, 0);
		//FadeLayer[0]->FadeInStartOsyare();
		if (Window::Instance()->GetWindowNow() > 0)
			Window::Instance()->WindowNyo();
	}
	/*
	if (ToSelectStage == 1)
	{
		if (FadeLayer[0]->GetFadeInF() == -1)
		{
			StageOkuyo->PutStage(NowStage);
			ToSelectStage = 0;
			FadeLayer[1]->SetCnt(15);
			FadeLayer[0]->SetCnt(15);
			FadeLayer[0]->FadeOutStartOsyare();
			if (NowStage != 1)
				MiniButton[0]->SetActiveF(1);
			if (NowStage != StageMax && NowStage != PlayAbleStage)
				MiniButton[1]->SetActiveF(1);
			MiniButton[3]->SetActiveF(1);
			ToSelectStage = 0;
			Bank::Instance()->StopBgm(0);
			Bank::Instance()->PlayBgm(1);
			MainGameMode = SELECTSTAGE;
		}
	}
	*/
}


void NewMainGame::Update()
{
	for (int i = 0; i < 3; i++)
	{
		FadeLayer[i]->Update();
	}
	MiniButtonUpdate();

	switch (MainGameMode)
	{
	case WINDOW:

		if (Window::Instance()->GetWindowNow() <= 0)
		{
			FadeLayer[0]->SetCnt(15);
			FadeLayer[0]->FadeOutStartOsyare();
			if (NowStage != 11)
			{
				if (NowStage >= 3 && NowStage <= 6)
					Bank::Instance()->PlayBgm(13);
				else if (NowStage >= 8 && NowStage <= 10)
					Bank::Instance()->PlayBgm(14);
				else
					Bank::Instance()->PlayBgm(0);

			}
			MainGameMode = MAINGAME;
		}

		break;
	case SELECTSTAGE:
		StageSelectUpdate();
		break;
	case MAINGAME:
		MainGameUpdate();
		break;
	case CLEAR:
		Hito.ClearUpdate();

		MojiCnt2++;

		if (MojiY2[min(MojiCnt2 / 5, 5)] < 0)
		{
			MojiY2[min(MojiCnt2 / 5, 5)] = 298;
			MojiVY2[min(MojiCnt2 / 5, 5)] = -2.5;
		}

		for (int i = 0; i < 6; i++)
		{
			//�������\������Ă��鎞
			if (MojiY2[i] > 0)
			{
				MojiVY2[i] += 0.2;
				MojiY2[i] += MojiVY2[i];
				if (MojiY2[i] >= 298)
				{
					MojiY2[i] = 298;
					MojiVY2[i] *= -0.5;
				}

			}
		}
		int mx = Mouse::Instance()->GetX();
		int my = Mouse::Instance()->GetY();

		//�N���A���Ď��̃X�e�[�W��
		if (mx >= 0 && mx <= 768 && my >= 64 && my <= 576)
		{
			if (StartFuchiF == 0)
			{
				MojiCnt = 0;
				StartFuchiF = 1;
			}
			//if ((Mouse::Instance()->GetInputSyunkan()) & MOUSE_INPUT_LEFT)
			if (Window::Instance()->GetWindowNow()==-1)
			{
				MiniButton[0]->SetActiveF(0);
				MiniButton[1]->SetActiveF(0);
				MiniButton[2]->SetActiveF(0);
				MiniButton[3]->SetActiveF(0);
				//SM->ChangeScene(SELECTSTAGESCENE);
				SM->ChangeScene(MAINGAMESCENE, 0, NowStage + 1);

				//StartFuchiF = 0;
				//ToNextStage = 1;
				//FadeLayer[0]->SetDrawRGB(0, 0, 0);
				//FadeLayer[0]->SetCnt(0);
				//FadeLayer[0]->FadeInStartOsyare();
			}
		}
		else
		{
			StartFuchiF = 0;
		}
		/*
		if (ToNextStage == 1 && FadeLayer[0]->GetFadeInF() == -1)
		{
			if (NowStage < StageMax)
				NowStage++;
			StageOkuyo->PutStage(NowStage);
			FadeLayer[1]->SetCnt(15);
			FadeLayer[2]->SetCnt(0);
			FadeLayer[0]->FadeOutStartOsyare();
			if (NowStage != 1)
				MiniButton[0]->SetActiveF(1);
			if (NowStage != StageMax && NowStage != PlayAbleStage)
				MiniButton[1]->SetActiveF(1);
			MiniButton[3]->SetActiveF(1);
			ToNextStage = 0;
			Bank::Instance()->StopBgm(0);
			Bank::Instance()->PlayBgm(1);

			MainGameMode = SELECTSTAGE;

		}
		*/

		//��蒼��
		if (MiniButton[2]->GetOsareta() == 1 && ToReStart == 0)
		{
			Window::Instance()->WindowNyo();
			ToReStart = 1;
			MiniButton[2]->SetActiveF(0);
			MiniButton[3]->SetActiveF(0);
			FadeLayer[0]->SetDrawRGB(255, 255, 255);
			FadeLayer[0]->FadeInStart();
		}
		if (ToReStart == 1)
		{
			if (FadeLayer[0]->GetFadeInF() == -1)
			{
				StageOkuyo->PutStage(NowStage);
				FadeLayer[2]->SetCnt(0);
				ClearMati = 0;
				Hito.SetNegaF(0);
				FadeLayer[0]->FadeOutStart();
				ToReStart = 0;
				MiniButton[2]->SetActiveF(1);
				MiniButton[3]->SetActiveF(1);

				MainGameMode = MAINGAME;
			}
		}


		//�X�e�[�W�I����ʂɖ߂�
		if (MiniButton[3]->GetOsareta() == 1 && ToSelectStage == 0)
		{
			Window::Instance()->WindowNyo();
			//ToSelectStage = 1;
			MiniButton[2]->SetActiveF(0);
			MiniButton[3]->SetActiveF(0);
			SM->ChangeScene(SELECTSTAGESCENE);
			/*
			FadeLayer[0]->SetCnt(0);
			FadeLayer[0]->SetDrawRGB(0, 0, 0);
			FadeLayer[0]->FadeInStartOsyare();
			*/
		}
		if (ToSelectStage == 1)
		{
			if (FadeLayer[0]->GetFadeInF() == -1)
			{
				StageOkuyo->PutStage(NowStage);
				ToSelectStage = 0;
				FadeLayer[1]->SetCnt(15);
				FadeLayer[0]->SetCnt(15);
				FadeLayer[0]->FadeOutStartOsyare();
				if (NowStage != 0)
					MiniButton[0]->SetActiveF(1);
				if (NowStage != StageMax && NowStage != PlayAbleStage)
					MiniButton[1]->SetActiveF(1);
				MiniButton[3]->SetActiveF(1);
				ToSelectStage = 0;
				Bank::Instance()->StopBgm(0);
				Bank::Instance()->PlayBgm(1);

				SM->ChangeScene(MAINGAMESCENE, 0, NowStage + 1);
				//MainGameMode = SELECTSTAGE;
			}
		}
		break;

	}

	Window::Instance()->Update();

}

void NewMainGame::MojiUpdate()
{
	for (int i = 0; i < 9; i++)
	{
		if (MojiCnt == i * 4)
		{
			MojiVY[i] = -2.5;
		}
		MojiVY[i] += 0.2;
		MojiY[i] += MojiVY[i];
		if (MojiY[i] >= 298)
		{
			MojiY[i] = 298;
			MojiVY[i] *= -0.5;
		}
	}
	MojiCnt++;
	if (MojiCnt >= 60 * 3)
		MojiCnt = 0;

}

void NewMainGame::MiniButtonDraw()
{
	for (int i = 0; i < 4; i++)
	{
		MiniButton[i]->Draw();
	}
}

void NewMainGame::MojiDraw()
{
	for (int i = 0; i < 9; i++)
	{
		char m[3] = { Moji[i * 2] , Moji[i * 2 + 1],'\0' };
		DrawStringFuchi(MojiX[i], MojiY[i], m, GetColor(0, 0, 0));
		DrawString(MojiX[i], MojiY[i], m, GetColor(255, 255, 255));
	}

}

void NewMainGame::DrawUeNoBar()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(0, 0, 1000, 64, GetColor(0, 0, 0), 1);
	DrawFormatString(4 + 32, 16 + 2, GetColor(0, 0, 0), "%s", StageName, FlowerName);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawFormatString(0 + 32, 12 + 2, GetColor(255, 255, 255), "%s", StageName, FlowerName);
	//DrawRotaGraph(16 * 4 * 7.5 + 32, 32, 4, 0, Bank::Instance()->GetGrHandle(4)[4], 1);
	//DrawRotaGraph(16 * 4 * 8.5 + 32, 32, 4, 0, Bank::Instance()->GetGrHandle(4)[6], 1);
	//DrawRotaGraph(16 * 4 * 9.5 + 32, 32, 4, 0, Bank::Instance()->GetGrHandle(4)[2], 1);
	//DrawRotaGraph(16 * 4 * 10.5 + 32, 32, 4, 0, Bank::Instance()->GetGrHandle(4)[0], 1);
	//DrawRotaGraph(16 * 4 * 10.5 + 32, 16 * 8 * 4+ 32, 4, 0, Bank::Instance()->GetGrHandle(4)[2], 1);


}

void NewMainGame::Draw()
{
	//�w�i�`��
	for (int y = 0; y < 144; y++)
	{
		if (NowStage < 11)
			DrawBox(0, y * 4, 192 * 4, y * 4 + 4, GetColor(80 + y * y / 150, 200 + y * y / 400, 255), 1);
		else
			DrawBox(0, y * 4, 192 * 4, y * 4 + 4, GetColor(0+y*y/150,50 + y * y / 600,100), 1);
	}
	/*
	if (NowStage >= 16)
	{
	DrawBox(0, 0, 192 * 4, 144 * 4, GetColor(150, 100, 100), 1);
	}
	*/
	switch (MainGameMode)
	{
	case SELECTSTAGE:
		//DrawBox(0, 0, 768, 576, GetColor(100, 200, 255), 1);


		Bg.Draw();
		KogeMgr->Draw();
		YusyaKun.Draw();
		Hito.Draw();
		for (int i = 0; i < Enemy.size(); i++)
		{
			Enemy[i]->Draw();
		}
		EffectMgr::Instance()->Draw();

		FadeLayer[1]->Draw();
		FadeLayer[0]->Draw();
		if (StartFuchiF == 1)
		{
			for (int i = 0; i < 4; i++)
				DrawBox(0 + i, 64 + i, 768 - i, 576 - i, GetColor(255, 255, 0), 0);
		}
		DrawUeNoBar();
		MojiDraw();
		MiniButtonDraw();
		break;
	case MAINGAME:
		//DrawBox(0, 0, 768, 576, GetColor(100, 200, 255), 1);

		/*
		for (int i = 0; i < 10; i++)
		{
		DrawLine(0, i * 16 * 4, 1000, i * 16 * 4, GetColor(50, 50, 150));
		DrawLine(i * 16 * 4, 0, i * 16 * 4, 1000,GetColor(50, 50, 150));
		}
		*/
		Bg.Draw();
		KogeMgr->Draw();
		for (int i = 0; i < Enemy.size(); i++)
		{
			Enemy[i]->Draw();
		}
		YusyaKun.Draw();
		Hito.Draw();
		EffectMgr::Instance()->Draw();

		sx = Shake::Instance()->GetX();
		sy = Shake::Instance()->GetY();

		if (BeemF[0] == 1)
		{
			DrawExtendGraph(BeemX[0][0] + sx, BeemY[0][0] + sy, BeemX[0][1] + sx, BeemY[0][1] + sy, BeemGrHandle[5], 1);
			DrawRotaGraph(BeemX[0][1] + sx, BeemY[0][0] + (BeemY[0][1] - BeemY[0][0]) / 2 + sy, 4, 0, BeemGrHandle[4], 1);
		}
		if (BeemF[1] == 1)
		{
			DrawExtendGraph(BeemX[1][0] + sx, BeemY[1][0] + sy, BeemX[1][1] + sx, BeemY[1][1] + sy, BeemGrHandle[1], 1);
			DrawRotaGraph(BeemX[1][0] + sx, BeemY[1][0] + (BeemY[1][1] - BeemY[1][0]) / 2 + sy, 4, 0, BeemGrHandle[0], 1);
			OseCnt++;
			DrawRotaGraph(192 * 2, 128 * 2 + ((OseCnt / 5) % 2) * 0, 4, 0, BeemGrHandle[8 + (OseCnt / 5) % 2], 1);
		}
		if (BeemF[2] == 1)
		{
			DrawRotaGraph(BeemCenterX + sx, BeemCenterY + sy, 4, 0, BeemGrHandle[12], 1);
		}


		if (SerifCnt == 24)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, EventCnt);
			DrawBox(0, 0, 192 * 4, 144 * 4, GetColor(255, 255, 255), 1);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		KaminariMgr->Draw();
		//FadeLayer[1]->Draw();
		FadeLayer[0]->Draw();
		DrawUeNoBar();
		MiniButtonDraw();

		/*
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0 + 8 * 4, 1.5 * 16 * 4, 192 * 4 - 8 * 4, 4 * 16 * 4, GetColor(0, 0, 0), 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawBox(0 + 8 * 4, 1.5 * 16 * 4, 192 * 4 - 8 * 4, 4 * 16 * 4, GetColor(255, 255, 255), 0);
		DrawBox(0 + 8 * 4+1, 1.5 * 16 * 4+1, 192 * 4 - 8 * 4-1, 4 * 16 * 4-1, GetColor(255, 255, 255), 0);
		DrawBox(0 + 8 * 4+2, 1.5 * 16 * 4+2, 192 * 4 - 8 * 4-2, 4 * 16 * 4-2, GetColor(255, 255, 255), 0);
		DrawBox(0 + 8 * 4+3, 1.5 * 16 * 4+3, 192 * 4 - 8 * 4-3, 4 * 16 * 4-3, GetColor(255, 255, 255), 0);
		DrawString(16 * 4, 2 * 16 * 4 - 1 * 4, "�Ƃ���ł����A���܂���", GetColor(255, 255, 255));
		DrawString(16 * 4, 2 * 16 * 4 + 3 * 4, "\n���Ȃ��́u�J�~�T�}�v�ł��B", GetColor(255, 255, 255));
		DrawString(16 * 4, 3 * 16 * 4-6, "���Ȃ��́u�J�~�T�}�v�ł��B", GetColor(255, 255, 255));
		//DrawExtendString(16 * 4, 2 * 16 * 4 - 1 * 4, 2, 2, "�J�~�����炾�I�I", GetColor(255, 255, 255));
		*/

		break;
	case CLEAR:
		//DrawBox(0, 0, 768, 576, GetColor(100, 200, 255), 1);
		Bg.Draw();
		KogeMgr->Draw();
		for (int i = 0; i < Enemy.size(); i++)
		{
			Enemy[i]->Draw();
		}
		EffectMgr::Instance()->Draw();
		FadeLayer[2]->Draw();
		Bg.Draw(1);
		YusyaKun.Draw();
		Hito.Draw();
		/*
		for (int i = 0; i < 6; i++)
		{
			char m[3] = { Moji2[i * 2] , Moji2[i * 2 + 1],'\0' };
			DrawStringFuchi(MojiX2[i], MojiY2[i], m, GetColor(0, 0, 0));
			DrawString(MojiX2[i], MojiY2[i], m, GetColor(255, 255, 255));
		}
		
		if (StartFuchiF == 1)
		{
			for (int i = 0; i < 4; i++)
				DrawBox(0 + i, 64 + i, 768 - i, 576 - i, GetColor(255, 255, 0), 0);
		}
		*/
		//FadeLayer[1]->Draw();
		FadeLayer[0]->Draw();
		DrawUeNoBar();
		MiniButtonDraw();

		//DrawFormatStringToHandle(40, 200, GetColor(255, 255, 255), Bank::Instance()->GetMiniFontHandle(), "�N���b�N���� ��������:3");

		break;

	case WINDOW:

		DrawUeNoBar();
		MiniButtonDraw();
		FadeLayer[1]->Draw();
		FadeLayer[0]->Draw();

		if (Mouse::Instance()->GetInputSyunkan() & MOUSE_INPUT_LEFT)
		{
			if (Mouse::Instance()->GetY() < 6 * 16 * 4)
			{
				GuidF = 1;
			}
			else
			{
				GuidF = 0;
			}
		}
		if (GuidF == 1)
		{
			//DrawString(140, 300, "���E�C���h�E���N���b�N", GetColor(200, 200, 200));
		}

		break;
	}

	Window::Instance()->Draw();
	//clsDx();
	//printfDx("%d", Tesuu);
	for (int y = -1; y < 2; y++)
		for (int x = -1; x < 2; x++)
			DrawFormatString(768+2 - 58+x*4, 576 - 12 * 4+y*4+2, GetColor(255, 255, 255), "%02d", Tesuu);
	DrawFormatString(768 - 58+2, 576 - 12 * 4+2, GetColor(75, 75, 75), "%02d", Tesuu);
}
 
BgMgr * NewMainGame::GetBg()
{
	return &Bg;
}

Player * NewMainGame::GetHito()
{
	return &Hito;
}

NewMainGame::NewMainGame(SceneMgr* SM,int Mode,int StageNum)
{

	//�Z�[�u�f�[�^�ǂݍ���
	/*int FileHandle;
	FileHandle = FileRead_open("SaveData.dat");

	//�t�@�C������������
	if (FileHandle == 0)
	{
	PlayAbleStage = 1;
	}
	else//�t�@�C����������
	{
	FileRead_scanf(FileHandle, "%d", &PlayAbleStage);
	FileRead_close(FileHandle);
	//printfDx("[[[%d]]]", PlayAbleStage);
	}
	*/
	//if ((fp = fopen("Data.dat", "rb")) != NULL)

	if ((fp = fopen("SaveData.dat", "rb")) == NULL)
	{
		PlayAbleStage = 0;////printfDx("�Ȃ���");
	}
	else
	{
		fread(&PlayAbleStage, sizeof(int), 1, fp);
		////printfDx("[[[%d]]]", PlayAbleStage);
		fclose(fp);
		//fclose(fp);
		////printfDx("�����%d",i);
	}

	//PlayAbleStage = 13;

	//Bank::Instance()->StopBgm(0);
	//Bank::Instance()->PlayBgm(1);

	this->SM = SM;
	JimenHandle = Bank::Instance()->GetGrHandle(1);
	FlowerHandle = Bank::Instance()->GetGrHandle(2);
	BeemGrHandle = Bank::Instance()->GetGrHandle(17);
	KogeMgr = new OutLineMgr;
	KaminariMgr = new ThunderMgr(this, KogeMgr);
	Bg.SetExRate(4);
	Bg.SetXY(0, 0);
	Hito.SetBgMgr(&Bg);
	Hito.SetTesuu(&Tesuu);
	YusyaKun.SetBgMgr(&Bg);
	StartFuchiF = 0;
	StageOkuyo = new StagePutter(&Bg, &Hito, &YusyaKun, &Enemy, KaminariMgr, KogeMgr, BeemF, StageName, FlowerName, FlowerMessage, this);
	StageMax = StageOkuyo->GetStageMax(StageNameData);
	////printfDx("%d\n", StageMax);

	for (int i = 0; i < 9; i++)
	{
		MojiX[i] = 204 + i * 40;
		MojiY[i] = 296 + 2;
		MojiVY[i] = 0;
	}
	MojiCnt = 0;

	FadeLayer[0] = new Fade(0, 255, 0, 0, 0);
	FadeLayer[1] = new Fade(1, 50, 0, 0, 0);
	FadeLayer[2] = new Fade(1, 125, 255, 255, 255);
	FadeLayer[0]->SetCnt(0);
	//FadeLayer[0]->FadeOutStartOsyare();
	FadeLayer[1]->SetCnt(15);
	FadeLayer[2]->SetCnt(0);

	MiniButton[0] = new Button(8, 16 * 4 * 7.5 + 32, -320, 14 * 4, 14 * 4);	//�O�̃X�e�[�W
	MiniButton[1] = new Button(12, 16 * 4 * 8.5 + 32, -320, 14 * 4, 14 * 4);	//���̃X�e�[�W
	MiniButton[2] = new Button(4, 16 * 4 * 9.5 + 32, 32, 14 * 4, 14 * 4);	//��蒼��
	MiniButton[3] = new Button(0, 16 * 4 * 10.5 + 32, 32, 14 * 4, 14 * 4);	//��߂�

	MiniButton[0]->SetActiveF(0);
	MiniButton[1]->SetActiveF(1);
	if (PlayAbleStage == 1)
		MiniButton[1]->SetActiveF(0);
	MiniButton[2]->SetActiveF(0);
	MiniButton[3]->SetActiveF(0);

	NowStage = StageNum;

	StageOkuyo->PutStage(NowStage);
	ToMainGame = 1;
	ToSelectStage = 0;
	ToReStart = 0;
	ToNextStage = 16;
	SerifCnt = 0;

	if (NowStage == 0)
	{
		FadeLayer[0]->SetCnt(15);
		Bank::Instance()->StopBgm(1);
		Window::Instance()->PutWindow(1, "����ɂ��́I \n\n�����ƁE�E�E \n\n�Ƃ���ł����A���Ȃ��� \n���܂���w�J�~�T�}�x�ł��B\n�E�E�E���ǂ낫�܂������H\n\n�������傤�ԁB �Ȃɂ� ����ς�\n���邱�Ƃ� ����܂���B\n�E�E�E����H\n\n�������� ���܂��Ă��� \n����Ȃ̂��� ����悤�ł��B \n�w�J�~�T�}�x�̂������ ������ \n�������� �����܂��傤�I");
	}
	if (NowStage == 11)
		Bank::Instance()->StopBgm(1);
	MainGameMode = WINDOW;
	//MainGameMode = MAINGAME;
}


NewMainGame::~NewMainGame()
{
	for (int i = 0; i < 4; i++)
	{
		delete MiniButton[i];
	}
	delete KogeMgr;
	delete KaminariMgr;
	for (int i = 0; i < 3; i++)
	{
		delete FadeLayer[i];
	}
	delete StageOkuyo;
	Window::Instance()->kill();
}

void NewMainGame::PutSlime(int X, int Y)
{
	Enemy.push_back(new Slime(X, Y, &Bg));

}

void NewMainGame::SetWarpManA(EnemyBase * WarpManA)
{
	this->WarpManA = WarpManA;
}

void NewMainGame::SetWarpManB(EnemyBase * WarpManB)
{
	this->WarpManB = WarpManB;
}

int * NewMainGame::GetTesuuPt()
{
	return &Tesuu;
}
