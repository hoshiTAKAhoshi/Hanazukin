#include "Window.h"
#include "DxLib.h"
#include "Mouse.h"
#include "Bank.h"
#include "Shake.h"


vector<string> Window::Split(const string & str, char sep)
{
	vector<std::string> v;
	stringstream ss(str);
	string buffer;
	while (getline(ss, buffer, sep)) {
		v.push_back(buffer);
	}
	return v;
}

void Window::ItiGime(int Iti)
{
	ItiHozon = Iti;
	if (Iti == 0)
	{
		X[0] = 0 + 8 * 4;
		Y[0] = 1.5 * 16 * 4;
		X[1] = 192 * 4 - 8 * 4;
		Y[1] = 4 * 16 * 4;
	}
	else
	{
		X[0] = 0 + 8 * 4;
		Y[0] = 6 * 16 * 4;
		X[1] = 192 * 4 - 8 * 4;
		Y[1] = 8.5 * 16 * 4;

	}

}


void Window::PutWindow(int Iti, string Moji)
{
	DekaF = 0;
	HikiMoji = Moji;
	MojiHyoujiCnt = 0;
	GyoCnt = 0;
	MojiHyoujiGyoCnt = 0;
	PutCnt = 0;
	ItiGime(Iti);
	if (WindowNow <= 0)
	{
		WindowNow = 1;
		WindowNyu(Iti, Moji);
	}
	else
	{
		PutMoji(Iti, Moji);
	}
}
void Window::PutWindowDeka(int Iti, string Moji)
{
	DekaF = 1;
	HikiMoji = Moji;
	MojiHyoujiCnt = 0;
	GyoCnt = 0;
	MojiHyoujiGyoCnt = 0;
	PutCnt = 0;
	ItiGime(Iti);
	Shake::Instance()->Start(30, 12);
	Bank::Instance()->PlaySe(4);
	PutMoji(Iti, Moji);
}

void Window::WindowNyu(int Iti, string Moji)
{
	ActionType = NYU;
	WindowNow = 1;
	NyuCnt = 0;
	ItiGime(Iti);
}

void Window::WindowNyo()
{
	ActionType = NYO;
	WindowNow = 0;
	NyuCnt = 16;

}

void Window::PutMoji(int Iti, string Moji)
{
	ActionType = PUTMOJI;
	WindowNow = 1;
	MojiHyoujiCnt = 0;
	GyoCnt = 0;
	MojiHyoujiGyoCnt = 0;
	PutCnt = 0;

	ItiGime(Iti);

	//行ごとに分ける
	MojiWakeru = Split(Moji, '\n');

	//奇数行だったら偶数行にする
	if (MojiWakeru.size() % 2 == 1)
	{
		MojiWakeru.push_back("\0");
	}
	
	//ウインドウに表示する文字列。最初は空。
	MojiHyouji[0] = "\0";
	MojiHyouji[1] = "\0";
}

int Window::GetWindowNow()
{
	return WindowNow;
}

int Window::GetGyoCnt()
{
	return GyoCnt;
}

bool Window::Owatta()
{
	return false;
}

void Window::kill()
{
	ActionType = NUN;
	WindowNow = -1;
}

void Window::Update()
{
	switch (ActionType)
	{
	case NUN:

		break;
	case NYU:
		NyuX[0] = X[0] + pow(16 - NyuCnt, 2);
		NyuY[0] = Y[0] + pow(16 - NyuCnt, 2) / 4;
		NyuX[1] = X[1] - pow(16 - NyuCnt, 2);
		NyuY[1] = Y[1] - pow(16 - NyuCnt, 2) / 4;

		if (NyuCnt++ >= 16)
		{
			PutMoji(ItiHozon,HikiMoji);
		}
		break;
	case NYO:
		NyuX[0] = X[0] + pow(16 - NyuCnt, 2);
		NyuY[0] = Y[0] + pow(16 - NyuCnt, 2) / 4;
		NyuX[1] = X[1] - pow(16 - NyuCnt, 2);
		NyuY[1] = Y[1] - pow(16 - NyuCnt, 2) / 4;

		if (NyuCnt < 0)
		{
			NyuX[0] = NyuY[0] = NyuX[1] = NyuY[1] = -16;
			WindowNow = -1;
			ActionType = NUN;
		}
		NyuCnt--;
		break;
	case PUTMOJI:


		int _mx = Mouse::Instance()->GetX();
		int _my = Mouse::Instance()->GetY();

		//if (_mx >= X[0] && _my >= Y[0] && _mx <= X[1] && _my <= Y[1])
		if(_my>=-16*4)
		{
			KasanatteruMouse = 1;
		}
		else
		{
			KasanatteruMouse = 0;
		}


		//1文字ずつ表示する文字を増やす
		if (MojiHyoujiCnt < MojiWakeru[GyoCnt].size())
		{
			if (PutCnt > 2)
			{
				//2バイト文字
				if (GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &MojiWakeru[GyoCnt][MojiHyoujiCnt]) == 2)
				{
					MojiHyouji[MojiHyoujiGyoCnt] += MojiWakeru[GyoCnt][MojiHyoujiCnt];
					MojiHyoujiCnt++;
				}
				if (MojiWakeru[GyoCnt][MojiHyoujiCnt] != ' ')
					Bank::Instance()->PlaySe(10);
				MojiHyouji[MojiHyoujiGyoCnt] += MojiWakeru[GyoCnt][MojiHyoujiCnt];
				MojiHyoujiCnt++;
				PutCnt = 0;
			}
			else
			{
				PutCnt++;
			}
			//文字を表示中にクリックされたら文字を最後まで一気に表示する
			if (KasanatteruMouse == 1 && Mouse::Instance()->GetInputSyunkan() != 0)
			{
				Bank::Instance()->PlaySe(10);
				ShowMouse();
				//BackAlpha = 255;
				DY = 6;
				//上の行を表示途中
				if (MojiHyoujiGyoCnt == 0)
				{
					MojiHyouji[MojiHyoujiGyoCnt] = MojiWakeru[GyoCnt];
					GyoCnt++;
					MojiHyoujiGyoCnt = 1;
					MojiHyouji[MojiHyoujiGyoCnt] = MojiWakeru[GyoCnt];
					MojiHyoujiCnt = MojiWakeru[GyoCnt].size();
				}
				else//下の行を表示途中
				{
					MojiHyouji[MojiHyoujiGyoCnt] = MojiWakeru[GyoCnt];
					MojiHyoujiCnt = MojiWakeru[GyoCnt].size();
				}

			}
		}
		else//1行表示し終わった
		{
			if (GyoCnt < MojiWakeru.size() - 1)
			{
				//上の行を表示し終わった
				if (MojiHyoujiGyoCnt == 0)
				{
					MojiHyoujiGyoCnt = 1;
					MojiHyoujiCnt = 0;
					GyoCnt++;
				}
				else//下の行を表示し終わった
				{
					ShowMouse();
					//クリックして次のページに進む
					if (KasanatteruMouse == 1 && Mouse::Instance()->GetInputSyunkan() != 0)
					{
						Bank::Instance()->PlaySe(7);
						if (DekaF == 1)
						{
							Bank::Instance()->PlaySe(4);
							Shake::Instance()->Start(30 + GyoCnt * 5, 12 + GyoCnt * 5);
						}
						MojiHyouji[0] = "\0";
						MojiHyouji[1] = "\0";

						MojiHyoujiGyoCnt = 0;
						MojiHyoujiCnt = 0;
						GyoCnt++;
						PutCnt = 0;
						//BackAlpha = 255;
						DY = 6;
						MouseAnimF = 0;
					}
				}
			}
			else//全部表示し終わった
			{
				ShowMouse();
				//クリックしてウインドウを閉じる
				if (KasanatteruMouse == 1 && Mouse::Instance()->GetInputSyunkan() != 0)
				{
					Bank::Instance()->PlaySe(7);

					//BackAlpha = 255;
					DY = 6;
					MouseAnimF = 0;
					WindowNow = 0;
					WindowNyo();
				}
			}
		}
		////printfDx("%d", MojiWakeru.size());
		break;
	}

	/*
	if (BackAlpha > 200)
	{
		BackAlpha-=5;
	}
	else
	{
		BackAlpha = 200;
	}
	*/
	if (DY > 0)
	{
		DY-=DY/8.0;
	}
	else
	{
		DY = 0;
	}

	if (MouseAnimF == 1)
	{
		MouseAnimCnt++;
		//if (MouseAnimCnt >= 60)
			//MouseAnimCnt = 0;
	}
}

void Window::Draw()
{
	switch (ActionType)
	{
	case NUN:

		break;
	case NYU:
		//ウインドウ描画
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200 - (16 - NyuCnt) * 4);
		DrawBox(NyuX[0], NyuY[0], NyuX[1], NyuY[1], GetColor(0, 0, 0), 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		for (int i = 0; i < 4; i++)
			DrawBox(NyuX[0] + i, NyuY[0] + i, NyuX[1] - i, NyuY[1] - i, GetColor(255, 255, 255), 0);

		break;
	case NYO:
		//ウインドウ描画
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200 - (16 - NyuCnt) * 4);
		DrawBox(NyuX[0] + 4, NyuY[0]+4 +DY, NyuX[1]-4, NyuY[1]-4 + DY, GetColor(0, 0, 0), 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (16 - NyuCnt) * 4);
		for (int i = 0; i < 4; i++)
			DrawBox(NyuX[0] + i, NyuY[0] + i + DY, NyuX[1] - i, NyuY[1] - i + DY, GetColor(255, 255, 255), 0);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		break;
	case PUTMOJI:
		//ウインドウ描画
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(X[0], Y[0] + DY, X[1], Y[1] + DY, GetColor(0, 0, 0), 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		for (int i = 0; i < 4; i++)
			DrawBox(X[0] + i, Y[0] + i + DY, X[1] - i, Y[1] - i + DY, GetColor(255, 255, 255), 0);
		
		//文字
		DrawExtendString(X[0] + 8 * 4+DekaF*12, Y[0] + 8 * 4 - 4 + DY + DekaF * 12,1+DekaF,1 + DekaF, MojiHyouji[0].c_str(), GetColor(255, 255, 255));
		DrawExtendString(X[0] + 8 * 4, Y[0] + 24 * 4 - 6 + DY,1 + DekaF,1 + DekaF, MojiHyouji[1].c_str(), GetColor(255, 255, 255));

		//黄色い枠
		if (KasanatteruMouse == 1)
		{
			//for (int i = 0; i < 4; i++)
				//DrawBox(0 + i, 64 + i, 768 - i, 576 - i, GetColor(255, 255, 0), 0);

			//for (int i = 0; i < 4; i++)
				//DrawBox(X[0]+i, Y[0]+i + DY, X[1]-i, Y[1]-i + DY, GetColor(255, 255, 0), 0);
		}


		//マウス
		if (MouseAnimF == 1)
		{
			DrawRotaGraph(X[1] - 12 * 4, Y[1] - 11 * 4+(((MouseAnimCnt / 30) % 2)==1)*4, 4, 0, MouseGrHandle[(MouseAnimCnt / 30)%2], 1);
		}
		break;
	}
}

void Window::Init()
{
	ActionType = NUN;
	//BackAlpha = 200;
}

Window::Window()
{
	Init();
	KasanatteruMouse = 0;
	MouseGrHandle = Bank::Instance()->GetGrHandle(12);
	MouseAnimCnt = 0;
	MouseAnimF = 0;
	WindowNow = -1;
	DekaF = 0;
}

Window::~Window()
{
}

void Window::ShowMouse()
{
	if (MouseAnimF == 0)
	{
		MouseAnimCnt = 0;
		MouseAnimF = 1;
	}
}

