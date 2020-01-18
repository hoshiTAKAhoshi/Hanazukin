#define _CRT_SECURE_NO_WARNINGS
#include "MainGame.h"
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

void MainGame::Collision()
{
	//敵と当たった
	for (int i = 0; i < Enemy.size(); i++)
	{
		if (Hito.CheckHitSp((Sprite*)Enemy[i]))
		{
			//踏み判定
			if (Hito.GetVY() > 0 && Hito.GetY() + 6 * EXRATE < Enemy[i]->GetY())
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
			else
			{
				//敵の動きを止める
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
					Shake::Instance()->Start(30, 7);


					//やり直し処理
					ToReStart = 1;
					MiniButton[2]->SetActiveF(0);
					MiniButton[3]->SetActiveF(0);
					FadeLayer[0]->SetDrawRGB(255, 255, 255);
					FadeLayer[0]->SetCnt(-15);
					FadeLayer[0]->FadeInStart();

				}////printfDx("いた");
			}
		}
	}

	//落下死
	if (Hito.GetY() > 144 * 4 + 32 || Hito.GetX()<0-32 || Hito.GetX()>192*4+32)
	{
		//敵の動きを止める
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


			//やり直し処理
			ToReStart = 1;
			MiniButton[2]->SetActiveF(0);
			MiniButton[3]->SetActiveF(0);
			FadeLayer[0]->SetDrawRGB(255, 255, 255);
			FadeLayer[0]->SetCnt(-15);
			FadeLayer[0]->FadeInStart();
		}
	}

	//感電死
	if (KaminariMgr->CheckHitHito() == 1)
	{
		//敵の動きを止める
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


			//やり直し処理
			ToReStart = 1;
			MiniButton[2]->SetActiveF(0);
			MiniButton[3]->SetActiveF(0);
			FadeLayer[0]->SetDrawRGB(255, 255, 255);
			FadeLayer[0]->SetCnt(-15);
			FadeLayer[0]->FadeInStart();
		}

	}
}


void MainGame::YusyaCollision()
{
	//敵と当たった
	for (int i = 0; i < Enemy.size(); i++)
	{
		if (YusyaKun.CheckHitSp((Sprite*)Enemy[i]))
		{
			{
				//敵の動きを止める
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


					//やり直し処理
					ToReStart = 1;
					MiniButton[2]->SetActiveF(0);
					MiniButton[3]->SetActiveF(0);
					FadeLayer[0]->SetDrawRGB(255, 255, 255);
					FadeLayer[0]->SetCnt(-15);
					FadeLayer[0]->FadeInStart();

				}////printfDx("いた");
			}
		}
	}

}


//クリア判定
void MainGame::CheckClear()
{
	if (Bg.GetChip(1, Hito.GetX(), Hito.GetY()) != -1)
	{
		if (Hito.GetStandF() == 1 && Hito.GetNegaF()==0)
		{
			Bank::Instance()->PlaySe(5);
			Hito.ClearInit();
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

				//セーブする

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
		//敵の動きを止める
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


void MainGame::MiniButtonUpdate()
{
	for (int i = 0; i < 4; i++)
	{
		MiniButton[i]->Update();
	}
}

void MainGame::StageSelectUpdate()
{
	int mx = Mouse::Instance()->GetX();
	int my = Mouse::Instance()->GetY();

	//スタート
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
		if (FadeLayer[0]->GetCnt()==0)
		{
			FadeLayer[1]->SetCnt(15);
			FadeLayer[1]->FadeOutStartOsyare();
			Bank::Instance()->StopBgm(1);
			if (NowStage >= 13)
			{
				//Bank::Instance()->PlayBgm(9);
			}
			else
				Bank::Instance()->PlayBgm(0);
			/*
			if (NowStage == 1)
			{
				SerifCnt = 1;
				Window::Instance()->PutWindow(0, "かのじょの なまえは \n「はなずきん」です。\nどうやら はなずきんちゃんは \nおはなを あつめたい ようです。\nしかし めのまえには あながあり \nなんと てきまで います。\n彼女は ここで 息絶えてしまう\n運命なのでしょうか・・・ \nいや、そんなことは ありません！\n\nなぜなら カミサマである \nあなたが ここに いるからです！\nでは、さっそくですが てきを \nクリック してみてください。");
			}
			*/
			SerifCnt = 0;
			MainGameMode = MAINGAME;
		}
	}

	//前のステージ
	if (MiniButton[0]->GetOsareta() == 1)
	{
		if (FadeLayer[0]->GetFadeInF() != 1)
			FadeLayer[0]->FadeInStart();
		NowStage--;
		//printfDx(StageName, "%s", StageNameData[NowStage]);
		MiniButton[1]->SetActiveF(1);
		if (NowStage == 1)
			MiniButton[0]->SetActiveF(0);
	}
	if (FadeLayer[0]->GetFadeInF() == -1)
	{
		StageOkuyo->PutStage(NowStage);
		FadeLayer[0]->FadeOutStart();

	}

	//次のステージ
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

	//タイトルに戻る
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

void MainGame::MainGameUpdate()
{
	////printfDx("%d", SerifCnt);

	//ステージ１のチュートリアル
	if (NowStage == 1)
	{
		if (SerifCnt >= 4 && SerifCnt!=5)
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

		//「クリックしてください」でスライムをクリックできるようにするため
		if (SerifCnt == 1 && Window::Instance()->GetGyoCnt() == 13)
		{
			SerifCnt = 2;
		}

		if (SerifCnt == 2 && (Enemy[0])->GetY() >= 420)
		{
			SerifCnt = 3;
			Window::Instance()->PutWindow(0, "うごきましたね！\n\nこれが あなたの ちからです。\n\nつづいて はなずきんちゃんを \nクリック してみてください。");
		}

		//「クリックしてください」ではなずきんをクリックできるようにするため
		if (SerifCnt == 3 && Window::Instance()->GetGyoCnt() == 5)
		{
			SerifCnt = 4;
		}

		if (SerifCnt == 4 && Hito.GetX()>=96+16*4)
		{
			SerifCnt = 5;
			Hito.SetFuchiByougaF(0);
			Enemy[0]->SetFuchiByougaF(0);
			Window::Instance()->PutWindow(0, "あるきだしましたね！\n\nこれで はなずきんちゃんは \nあなにおちた てきを ふんで\nおはなの ところに \nたどりつける はずです。\nこのように 「てきを あやつって」 \nはなずきんちゃんを\nおはなの ところに\nみちびいて あげてください！\nわたしから おつたえすることは \nいじょうです。\nそれでは、\nグッドラック！！！");

		}

		if (SerifCnt == 5 && Window::Instance()->GetWindowNow() <=0)
		{
			SerifCnt = 6;
		}

	}
	else if (NowStage == 5)//勇者君との初対面
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

		//最初のセリフが終わって花頭巾を動かせるようにする
		if (SerifCnt == 1 && Window::Instance()->GetWindowNow() <=0)
		{
			YusyaKun.SetGrNum(0);
			SerifCnt = 2;
		}

		//はなずきんに気づく
		if (SerifCnt == 2 && Hito.GetX() >= 16 * 4 * 4)
		{
			SerifCnt = 3;
			YusyaKun.SetGrNum(16);
			Window::Instance()->PutWindow(0, "・・・ \n！？！？\nえ、、あ、、 \nみてた・・・？\nえーと・・・   \nコホン。\nこのあたりは モンスター だらけで \nキケンだから、\nおうちに かえったほうが いいよ");
		}

		//２つ目のセリフが終わって花頭巾を動かせるようにする
		if (SerifCnt == 3&& Window::Instance()->GetWindowNow() <=0)
		{
			SerifCnt = 4;
		}

		//ねえきいてる？
		if (SerifCnt == 4 && Hito.GetX() >= 16 * 8 * 4)
		{
			SerifCnt = 5;
			YusyaKun.SetGrNum(0);
			Window::Instance()->PutWindow(0, "・・・ねえ、 \nきいてる？");
		}

		//３つ目のセリフが終わって花頭巾を動かせるようにする
		if (SerifCnt == 5 && Window::Instance()->GetWindowNow() <=0)
		{
			SerifCnt = 6;
		}


	}
	else if (NowStage == 9)
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

		//最初のセリフが終わって花頭巾を動かせるようにする
		if (SerifCnt == 1 && Window::Instance()->GetWindowNow() <=0)
		{
			SerifCnt = 2;
		}

		//はなずきんに気づく
		if (SerifCnt == 2 && Hito.GetX() >= 16 * 5.5 * 4)
		{
			Hito.MoveStop();
			SerifCnt = 3;
			YusyaKun.SetGrNum(15);
			Window::Instance()->PutWindow(0, "あ・・・ \nキミは あのときの・・・\nよく ここまで ぶじに \nたどりつけたね・・・\n・・・\n\nあの・・・ \n\nよかったら いっしょに \nやすんでかない・・・？");
		}

		//２つ目のセリフが終わって花頭巾を動かせるようにする
		if (SerifCnt == 3 && Window::Instance()->GetWindowNow() <=0)
		{
			SerifCnt = 4;
		}

		//はなずきんに気づく
		if (SerifCnt == 4 && Hito.GetX() >= 16 * 7.5 * 4)
		{
			Hito.MoveStop();
			Hito.SetGrNum(21);
			SerifCnt = 5;
			Window::Instance()->PutWindow(0, "・・・\n\nきみは ここで なにをしてるの？\n\n・・・そっか、 \nおはなを あつめてるんだ。\n・・・    \nステキだね。\n・・・ \nえ、ボク？\nボクは わるものを \nやっつけてるんだ！\nきっと このさきにある おしろに \nおやだまが いるに ちがいない。\nボクは そいつを たおして、\n\nこのせかいに へいわを \nとりもどすんだ！！！\n・・・   \nえっと・・・\nこ、こうしちゃいられない！！\n\nはやく いかないと！\n\n・・・そ、それじゃあ！");
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
	else if (NowStage == 13)
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

		//のっとられたときの処理
		if (SerifCnt == 13)
		{
			Hito.Update();

			YusyaKun.UpdateNottori();

			double hX = Hito.GetX();
			double hY = Hito.GetY();
			double yX = YusyaKun.GetX();
			double yY = YusyaKun.GetY();

			//はなずきんが剣に触れて死ぬ
			if (YusyaKun.GetNottoriCnt() >= 63 && YusyaKun.GetNottoriCnt() <= 63 + 3 + 12)
			{
				if (pow(hX - yX, 2) + pow(hY - yY, 2) < pow(8 * 4 + 20 * 4, 2))
				{
					Bank::Instance()->PlaySe(8);
					Hito.SetNegaF(1);
					Hito.SpAnimStop();
					Hito.SetVX(0);
					Shake::Instance()->Start(30, 7);


					//やり直し処理
					ToReStart = 1;
					MiniButton[2]->SetActiveF(0);
					MiniButton[3]->SetActiveF(0);
					FadeLayer[0]->SetDrawRGB(255, 255, 255);
					FadeLayer[0]->SetCnt(-15);
					FadeLayer[0]->FadeInStart();

				}
			}

			//勇者を踏みつける
			if (hX >= yX - 12*4 && hX <= yX + 12*4 && hY >= yY - 14*4 && hY <= yY - 8*4)
			{
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
			//次の部屋に進む
			if (Hito.GetX() >= 11.5 * 16 * 4 && FadeLayer[0]->GetFadeInF()==0)
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


		//岩を降らせる
		if (SerifCnt >= 11 && SerifCnt <= 14)
		{
			EventCnt++;
			if (EventCnt >= 120)
			{
				EventCnt = 0;
				Enemy.push_back(new Iwa);
			}
		}

		//さいごのへや
		if (SerifCnt == 15)
		{
			
		}

		if (SerifCnt == 1 && Window::Instance()->GetGyoCnt() == 5)
		{
			YusyaKun.SetGrNum(16);
		}


		////printfDx("[%d]", Window::Instance()->GetWindowNow());
		//最初のセリフが終わってボスのセリフ
		if (SerifCnt == 1 && Window::Instance()->GetWindowNow() == -1)
		{
			EventCnt++;
			if (EventCnt >= 30)
			{
				EventCnt = 0;
				SerifCnt = 2;
				YusyaKun.SetGrNum(0);
				Window::Instance()->PutWindow(0, "そこにいるのは だれだ！！");
			}
		}

		//ボスジャンプ初期設定
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
				Enemy[0]->SetXY(Enemy[0]->GetX()+1, 6 * 16 * 4);
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
				Window::Instance()->PutWindow(0, "でたな、おやだまめ！！\n\nこのせかいの へいわを \nみだすヤツは、\nこのボクが ゆるさない！！ \nかくごしろ！！");
			}
		}

		if (SerifCnt == 5 && Window::Instance()->GetWindowNow() == -1)
		{
			SerifCnt = 6;
			Window::Instance()->PutWindow(0, "フン、たわけ。\n\nオマエたちが ここにきたこと、\nとくと こうかい させてやるわ！");
		}

		if (SerifCnt == 6 && Window::Instance()->GetWindowNow() == -1)
		{
			SerifCnt = 7;
			Bank::Instance()->PlayBgm(9);
		}


		if (SerifCnt == 7)
		{
			if (((Boss*)Enemy[0])->GetHp() == 0 && YusyaKun.GetNegaF() == 0)
			{
				SerifCnt = 8;
				Bank::Instance()->StopBgm(9);
				Window::Instance()->PutWindow(0, "おい、オマエ。\n\nオマエだよ。がめんの むこうの \nカミサマさんよお。\nコイツらをあやつれば オレサマに \nかてるとでも おもったか？\nわらわせんな。\nそれは ムリだ。\nなぜかって？ \nそれはなあ・・・");
			}
		}

		if (SerifCnt == 8 && Window::Instance()->GetWindowNow() == 0)
		{
			SerifCnt = 9;
			Window::Instance()->PutWindowDeka(0, "オレサマも\n\n『カミサマ』\n\nだからなあ！！");
		}

		if (SerifCnt == 9 && Window::Instance()->GetWindowNow() == -1)
		{
			YusyaKun.SpAnimStop();
			YusyaKun.SetGrNum(24);
			YusyaKun.SetVY(-4);
			SerifCnt = 10;
		}

		//勇者操られる
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

		//ボス逃げる
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
					Window::Instance()->PutWindow(0, "フン、キサマひとりで　\nなにができると いうのか。\nみのほどを \nおもいしらせてやる！！！！");
				}
				else
				{
					SerifCnt = 16;
					Window::Instance()->PutWindow(0, "フン、キサマひとりで　\nなにができると いうのか。");

				}
			}
		}

		//バッドエンド
		if (YusyaKun.GetNottorareF() == 1)
		{
			if (SerifCnt == 16)
			{
				if (Window::Instance()->GetWindowNow() == -1)
				{
					Bank::Instance()->PlaySe(4);
					SerifCnt = 17;
					BeemF[0] = 1;
					BeemX[0][0] = Enemy[0]->GetX()-12;
					BeemY[0][0] = 6 * 16 * 4-2*4;
					BeemX[0][1] = Enemy[0]->GetX()-12;
					BeemY[0][1] = 7 * 16 * 4-2*4;
					Enemy[0]->SetGrNum(2);
				}
			}
			if (SerifCnt == 17)
			{
				BeemX[0][0] -= 12;
				//やられ
				if (BeemX[0][0] <= Hito.GetX())
				{
					Bank::Instance()->PlaySe(8);
					Hito.SetNegaF(1);
					Hito.SpAnimStop();
					Hito.SetVX(0);
					Shake::Instance()->Start(30, 7);


					//やり直し処理
					ToReStart = 1;
					MiniButton[2]->SetActiveF(0);
					MiniButton[3]->SetActiveF(0);
					FadeLayer[0]->SetDrawRGB(255, 255, 255);
					FadeLayer[0]->SetCnt(-15);
					FadeLayer[0]->FadeInStartOsyare();
					SerifCnt = 18;
				}
			}
		}
		else//グッドエンド
		{
			if (SerifCnt == 16 && Window::Instance()->GetWindowNow() == -1)
			{
				SerifCnt = 17;
				Window::Instance()->PutWindow(0, "ひとりじゃない！！！！！");
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
				if (YusyaKun.GetX() >= 1.5 * 16 * 4+3*4)
				{
					SerifCnt = 19;
					YusyaKun.SpAnimStop();
					YusyaKun.SetGrNum(0);
				}
			}

			if (SerifCnt == 19)
			{
				SerifCnt = 20;
				Window::Instance()->PutWindow(0, "ふたりだから なんだ。\n\n・・・ちょうどいい。\n\nまとめて しまつしてやる！！！！");
			}
			if (SerifCnt == 20 && Window::Instance()->GetGyoCnt() == 4)
			{
				Enemy[0]->SetGrNum(1);

			}
			if (SerifCnt == 20 && Window::Instance()->GetWindowNow() == -1)
			{
				SerifCnt = 21;
				Window::Instance()->PutWindow(0, "そうはさせない！！！！！\n\nこれで ととめだ！！！！");
				YusyaKun.SetGrNum(12);
				Hito.SetGrNum(23);
			}
			if (SerifCnt == 21 && Window::Instance()->GetWindowNow() == -1)
			{
				Bank::Instance()->PlaySe(4);
				SerifCnt = 22;
				BeemF[0] = 1;
				BeemX[0][0] = Enemy[0]->GetX()-4*4;
				BeemY[0][0] = 5 * 16 * 4 + 3 * 4;
				BeemX[0][1] = Enemy[0]->GetX()-4*4;
				BeemY[0][1] = 6 * 16 * 4 + 3 * 4;
				BeemF[1] = 1;
				BeemX[1][0] = 2*16*4+3*4;
				BeemY[1][0] = 5 * 16 * 4 + 3 * 4;
				BeemX[1][1] = 2*16*4+3*4;
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
				Shake::Instance()->Start(5, 3);
				BeemCenterX -= BeemCenterX/(192.0*2)+0.5;
				if (Mouse::Instance()->GetInputSyunkan() & MOUSE_INPUT_LEFT)
				{
					Bank::Instance()->PlaySe(6);
					BeemCenterX += 32;
				}

				//まけ
				if (BeemCenterX < BeemX[1][0])
				{
					Bank::Instance()->PlaySe(8);
					Hito.SetNegaF(1);
					Hito.SpAnimStop();
					Hito.SetVX(0);
					Shake::Instance()->Start(30, 7);

					//やり直し処理
					ToReStart = 1;
					MiniButton[2]->SetActiveF(0);
					MiniButton[3]->SetActiveF(0);
					FadeLayer[0]->SetDrawRGB(255, 255, 255);
					FadeLayer[0]->SetCnt(-15);
					FadeLayer[0]->FadeInStart();
					SerifCnt = 99;

				}

				//かち
				if (BeemCenterX > BeemX[0][1])
				{
					Bank::Instance()->StopBgm(9);
					Bank::Instance()->PlaySe(4);
					SerifCnt = 24;
					EventCnt = 255;
					Shake::Instance()->Start(100, 20);
					Bank::Instance()->PlaySe(4);
					Enemy[0]->SetXY(-128, - 128);
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
				EventCnt-=3;
				if (EventCnt <=3)
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
					Window::Instance()->PutWindow(0, "や、やった！！！！\n\nたおした！！！！！\n\n・・・ \nなんだか きょうのボクは \nいつもより つよかった \nきがするよ。\n・・・ \nキミの おかげかな。\nありがとう。\n\n・・・そうだ、\n\nさいごに これを \nうけとってもらえないかな。\nチューリップ。\n\nきれいに さいていたから \nキミに みせたくて。\nどう？　\nきにいって もらえたかな。\n・・・\n\nそれじゃあ、\n\nかえろっか。");
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
					Window::Instance()->PutWindow(1, "きいろの チューリップの \nはなことばは、\n『あいの めばえ』 \nだそうです。\nゆうしゃくん、とっても \nいきなことを しますね。\n・・・こうして、このせかいに \nへいわが おとずれ、\nちいさな「あい」が\nめばえたのでした。\nおしまい。\n\nさいごまで あそんでくれて \nありがとう！！");
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
	
	KaminariMgr->Update();

	Collision();
	CheckClear();

	//遷移完了
	if (ToMainGame == 1 && FadeLayer[1]->GetFadeOutF() == -1)
	{
		if (NowStage != 1)
		{
			MiniButton[2]->SetActiveF(1);
			MiniButton[3]->SetActiveF(1);
			//Hito.MoveStart();
		}

		//チュートリアル
		if (NowStage == 1)
		{
			MiniButton[2]->SetActiveF(0);
			MiniButton[3]->SetActiveF(1);
			SerifCnt = 1;
			Window::Instance()->PutWindow(0, "かのじょの なまえは \n「はなずきん」です。\nどうやら はなずきんちゃんは \nおはなを あつめたい ようです。\nしかし めのまえには あながあり \nなんと てきまで います。\n彼女は ここで 息絶えてしまう\n運命なのでしょうか・・・ \nいや、そんなことは ありません！\n\nなぜなら カミサマである \nあなたが ここに いるからです！\nでは、さっそくですが てきを \nクリック してみてください。");
		}

		//勇者君との出逢い
		if (NowStage == 5)
		{
			MiniButton[2]->SetActiveF(0);
			MiniButton[3]->SetActiveF(1);
			SerifCnt = 1;
			YusyaKun.SetGrNum(6);
			Window::Instance()->PutWindow(0, "う～ん・・・ \nさいきん このあたりで \nモンスターが たいりょうに \nはっせい してるな・・・\nいったい \nどういう ことなんだ・・・\n・・・いや、なやんでたって \nしかたないな！\nなにが おころうが ボクは \nあくと たたかう のみ！！\nこの せかいの へいわは \nボクが まもってみせる！！！");
		}

		//勇者君との休息
		if (NowStage == 9)
		{
			MiniButton[2]->SetActiveF(0);
			MiniButton[3]->SetActiveF(1);
			SerifCnt = 1;
			Window::Instance()->PutWindow(0, "くそう・・・\n\nこのボクが こんなモンスターに \nくせんするなんて・・・\nはあ・・・");
		}

		//ボス戦
		if (NowStage == 13)
		{
			Bank::Instance()->StopBgm(9);
			MiniButton[2]->SetActiveF(0);
			MiniButton[3]->SetActiveF(1);
			SerifCnt = 1;
			EventCnt = 0;
			Window::Instance()->PutWindow(0, "ここが おしろか・・・\n\nはたして おやだまは ここに \nいるのだろうか・・・\n・・・  \nえっ！？\nなんで キミが ここに！？\n\n・・・ま、いっか。\nせっかく ここまで きたなら、\nボクの カッコいい \nけんさばきを みてってよ！");
		}

		ToMainGame = 0;

	}

	//やり直す
	if (MiniButton[2]->GetOsareta() == 1 && ToReStart==0)
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
			if (NowStage == 13)
			{
				Bank::Instance()->PlayBgm(9);
				if (SerifCnt >= 12)
				{
					Enemy[0]->SetXY(2000, 2000);
					YusyaKun.NottoriInit();
					YusyaKun.SetXY(8 * 16 * 4, YusyaKun.GetY());
					SerifCnt = 12;
				}
				else
				{
					Enemy[0]->SetXY(10*16*4,6*16*4);
					SerifCnt = 7;

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
			if (NowStage == 13)
				MiniButton[2]->SetActiveF(0);

			ToReStart = 0;
		}
	}

	//ステージ選択画面に戻る
	if (MiniButton[3]->GetOsareta() == 1 && ToSelectStage==0)
	{
		ToSelectStage = 1;
		MiniButton[2]->SetActiveF(0);
		MiniButton[3]->SetActiveF(0);
		FadeLayer[0]->SetCnt(0);
		FadeLayer[0]->SetDrawRGB(0, 0, 0);
		FadeLayer[0]->FadeInStartOsyare();
		if (Window::Instance()->GetWindowNow() > 0)
			Window::Instance()->WindowNyo();
	}
	if (ToSelectStage == 1)
	{
		if (FadeLayer[0]->GetFadeInF()==-1)
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
}


void MainGame::Update()
{
	for (int i = 0; i < 3; i++)
	{
		FadeLayer[i]->Update();
	}
	MiniButtonUpdate();

	switch (MainGameMode)
	{
	case WINDOW:

		if (Window::Instance()->GetWindowNow() <=0)
		{
			FadeLayer[0]->FadeOutStartOsyare();
			Bank::Instance()->PlayBgm(1);
			MainGameMode = SELECTSTAGE;
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
			//文字が表示されている時
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

		//クリアして次のステージに
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
				ToNextStage = 1;
				FadeLayer[0]->SetDrawRGB(0, 0, 0);
				FadeLayer[0]->SetCnt(0);
				FadeLayer[0]->FadeInStartOsyare();
			}
		}
		else
		{
			StartFuchiF = 0;
		}

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


		//やり直す
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


		//ステージ選択画面に戻る
		if (MiniButton[3]->GetOsareta() == 1 && ToSelectStage == 0)
		{
			ToSelectStage = 1;
			MiniButton[2]->SetActiveF(0);
			MiniButton[3]->SetActiveF(0);
			FadeLayer[0]->SetCnt(0);
			FadeLayer[0]->SetDrawRGB(0, 0, 0);
			FadeLayer[0]->FadeInStartOsyare();
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
		break;

	}

	Window::Instance()->Update();

}

void MainGame::MojiUpdate()
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
			MojiVY[i] *=-0.5;
		}
	}
	MojiCnt++;
	if (MojiCnt >= 60 * 3)
		MojiCnt = 0;

}

void MainGame::MiniButtonDraw()
{
	for (int i = 0; i < 4; i++)
	{
		MiniButton[i]->Draw();
	}
}

void MainGame::MojiDraw()
{
	for (int i = 0; i < 9; i++)
	{
		char m[3] = { Moji[i * 2] , Moji[i * 2 + 1],'\0' };
		DrawStringFuchi(MojiX[i], MojiY[i], m, GetColor(0, 0, 0));
		DrawString(MojiX[i], MojiY[i], m, GetColor(255, 255, 255));
	}
	
}

void MainGame::DrawUeNoBar()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(0, 0, 1000, 64, GetColor(0, 0, 0), 1);
	DrawFormatString(4+32, 16+2, GetColor(0, 0, 0), "%s", StageName, FlowerName);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawFormatString(0+32, 12+2, GetColor(255, 255, 255), "%s", StageName, FlowerName);
	//DrawRotaGraph(16 * 4 * 7.5 + 32, 32, 4, 0, Bank::Instance()->GetGrHandle(4)[4], 1);
	//DrawRotaGraph(16 * 4 * 8.5 + 32, 32, 4, 0, Bank::Instance()->GetGrHandle(4)[6], 1);
	//DrawRotaGraph(16 * 4 * 9.5 + 32, 32, 4, 0, Bank::Instance()->GetGrHandle(4)[2], 1);
	//DrawRotaGraph(16 * 4 * 10.5 + 32, 32, 4, 0, Bank::Instance()->GetGrHandle(4)[0], 1);
	//DrawRotaGraph(16 * 4 * 10.5 + 32, 16 * 8 * 4+ 32, 4, 0, Bank::Instance()->GetGrHandle(4)[2], 1);


}

void MainGame::Draw()
{
	//背景描画
	for (int y = 0; y < 144; y++)
	{
		DrawBox(0, y * 4, 192 * 4, y * 4 + 4, GetColor(80+y*y/150, 200+y*y/400, 255), 1);
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
				DrawBox(0+i, 64+i, 768-i, 576-i, GetColor(255, 255, 0), 0);
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
		YusyaKun.Draw();
		Hito.Draw();
		for (int i = 0; i < Enemy.size(); i++)
		{
			Enemy[i]->Draw();
		}
		EffectMgr::Instance()->Draw();

		sx = Shake::Instance()->GetX();
		sy = Shake::Instance()->GetY();

		if (BeemF[0] == 1)
		{
			DrawExtendGraph(BeemX[0][0]+sx, BeemY[0][0]+sy, BeemX[0][1]+sx, BeemY[0][1]+sy, BeemGrHandle[5], 1);
			DrawRotaGraph(BeemX[0][1]+sx, BeemY[0][0] + (BeemY[0][1] - BeemY[0][0]) / 2+sy, 4, 0, BeemGrHandle[4], 1);
		}
		if (BeemF[1] == 1)
		{
			DrawExtendGraph(BeemX[1][0]+sx, BeemY[1][0]+sy, BeemX[1][1]+sx, BeemY[1][1]+sy, BeemGrHandle[1], 1);
			DrawRotaGraph(BeemX[1][0]+sx, BeemY[1][0] + (BeemY[1][1] - BeemY[1][0]) / 2+sy, 4, 0, BeemGrHandle[0], 1);
			OseCnt++;
			DrawRotaGraph(192 * 2, 128 * 2 + ((OseCnt / 5) % 2)*0, 4, 0, BeemGrHandle[8+(OseCnt/5)%2], 1);
		}
		if (BeemF[2] == 1)
		{
			DrawRotaGraph(BeemCenterX+sx, BeemCenterY+sy, 4, 0, BeemGrHandle[12], 1);
		}


		if (SerifCnt == 24)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, EventCnt);
			DrawBox(0, 0, 192 * 4, 144 * 4, GetColor(255, 255, 255), 1);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		KaminariMgr->Draw();
		FadeLayer[1]->Draw();
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
		DrawString(16 * 4, 2 * 16 * 4 - 1 * 4, "とつぜんですが、いまから", GetColor(255, 255, 255));
		DrawString(16 * 4, 2 * 16 * 4 + 3 * 4, "\nあなたは「カミサマ」です。", GetColor(255, 255, 255));
		DrawString(16 * 4, 3 * 16 * 4-6, "あなたは「カミサマ」です。", GetColor(255, 255, 255));
		//DrawExtendString(16 * 4, 2 * 16 * 4 - 1 * 4, 2, 2, "カミだからだ！！", GetColor(255, 255, 255));
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
		FadeLayer[1]->Draw();
		FadeLayer[0]->Draw();
		DrawUeNoBar();
		MiniButtonDraw();


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
			DrawString(140,300,"↓ウインドウをクリック",GetColor(200,200,200));
		}

		break;
	}

	Window::Instance()->Draw();
}

BgMgr * MainGame::GetBg()
{
	return &Bg;
}

Player * MainGame::GetHito()
{
	return &Hito;
}

MainGame::MainGame(SceneMgr* SM)
{

	//セーブデータ読み込み
	/*int FileHandle;
	FileHandle = FileRead_open("SaveData.dat");

	//ファイルが無かった
	if (FileHandle == 0)
	{
		PlayAbleStage = 1;
	}
	else//ファイルがあった
	{
		FileRead_scanf(FileHandle, "%d", &PlayAbleStage);
		FileRead_close(FileHandle);
		//printfDx("[[[%d]]]", PlayAbleStage);
	}
	*/
	//if ((fp = fopen("Data.dat", "rb")) != NULL)

	if ((fp=fopen("SaveData.dat", "rb")) == NULL)
	{
		PlayAbleStage = 1;////printfDx("ないよ");
	}
	else
	{
		fread(&PlayAbleStage, sizeof(int), 1, fp);
		////printfDx("[[[%d]]]", PlayAbleStage);
		fclose(fp);
		//fclose(fp);
		////printfDx("あるよ%d",i);
	}
	
	//PlayAbleStage = 13;

	//Bank::Instance()->StopBgm(0);
	//Bank::Instance()->PlayBgm(1);

	this->SM = SM;
	JimenHandle = Bank::Instance()->GetGrHandle(1);
	FlowerHandle = Bank::Instance()->GetGrHandle(2);
	BeemGrHandle = Bank::Instance()->GetGrHandle(17);
	KogeMgr = new OutLineMgr;
	KaminariMgr = new ThunderMgr(this,KogeMgr);
	Bg.SetExRate(4);
	Bg.SetXY(0, 0);	
	Hito.SetBgMgr(&Bg);
	YusyaKun.SetBgMgr(&Bg);
	StartFuchiF = 0;
	StageOkuyo = new StagePutter(&Bg, &Hito, &YusyaKun, &Enemy, KaminariMgr, KogeMgr,BeemF, StageName, FlowerName, FlowerMessage,this);
	StageMax = StageOkuyo->GetStageMax(StageNameData);
	////printfDx("%d\n", StageMax);

	for (int i = 0; i < 9; i++)
	{
		MojiX[i] = 204 + i * 40;
		MojiY[i] = 296+2;
		MojiVY[i] = 0;
	}
	MojiCnt = 0;

	FadeLayer[0] = new Fade(0, 255,0,0,0);
	FadeLayer[1] = new Fade(1, 50, 0, 0, 0);
	FadeLayer[2] = new Fade(1, 125, 255, 255, 255);
	FadeLayer[0]->SetCnt(15);
	//FadeLayer[0]->FadeOutStartOsyare();
	FadeLayer[1]->SetCnt(15);
	FadeLayer[2]->SetCnt(0);
	
	MiniButton[0] = new Button(8, 16 * 4 * 7.5 + 32, 32, 14 * 4, 14 * 4);	//前のステージ
	MiniButton[1] = new Button(12, 16 * 4 * 8.5 + 32, 32, 14 * 4, 14 * 4);	//次のステージ
	MiniButton[2] = new Button(4, 16 * 4 * 9.5 + 32, 32, 14 * 4, 14 * 4);	//やり直し
	MiniButton[3] = new Button(0, 16 * 4 * 10.5 + 32, 32, 14 * 4, 14 * 4);	//やめる

	MiniButton[0]->SetActiveF(0);
	MiniButton[1]->SetActiveF(1);
	if(PlayAbleStage==1)
		MiniButton[1]->SetActiveF(0);
	MiniButton[2]->SetActiveF(0);
	
	NowStage = 1;

	StageOkuyo->PutStage(NowStage);
	ToMainGame = 0;
	ToSelectStage = 0;
	ToReStart = 0;
	ToNextStage = 16;

	//Window::Instance()->PutWindow(1,"こんにちは！ \n\nえっと・・・ \n\nとつぜんですが、あなたは \nいまから『カミサマ』です。\n・・・おどろきましたか？\n\nだいじょうぶ。 なにも しんぱい\nすることは ありません。\n・・・おや？\n\nあそこに こまっている \nおんなのこが いるようです。 \n『カミサマ』のちからを つかって \nたすけて あげましょう！");

	MainGameMode = WINDOW;
}


MainGame::~MainGame()
{
	for (int i = 0; i < 4; i++)
	{
		delete MiniButton[i];
	}
}

void MainGame::PutSlime(int X, int Y)
{
	Enemy.push_back(new Slime(X, Y, &Bg));

}