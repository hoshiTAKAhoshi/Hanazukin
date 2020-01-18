#pragma once
#include "Singleton.h"
#include <vector>
#include <string>
#include <sstream>

using namespace std;

enum Type { NUN, NYU, PUTMOJI ,NYO};

class Window :
	public Singleton<Window>
{
	Window();
	friend Singleton<Window>;
public:
	//文字列を分割するコピペ関数
	vector<string> Split(const string &str, char sep);
	void PutWindow(int Iti, string Moji);
	void PutWindowDeka(int Iti, string Moji);
	void WindowNyu(int Iti, string Moji);
	void WindowNyo();
	void PutMoji(int Iti, string Moji);
	int GetWindowNow();
	int GetGyoCnt();
	//ウインドウの一連の処理が終わったかを返す
	bool Owatta();
	void kill();
	void Update();
	void Draw();
	void Init();
	//Window();
	~Window();
private:
	void ShowMouse();
	void ItiGime(int Iti);
	int ItiHozon;
	int WindowNow;
	double X[2], Y[2];
	double NyuX[2], NyuY[2];
	string HikiMoji;
	vector<string> MojiWakeru;
	string MojiHyouji[2];
	int Cnt;
	int NyuCnt;
	int MojiHyoujiCnt;
	int MojiHyoujiGyoCnt;
	int GyoCnt;
	int PutCnt;
	Type ActionType;
	bool KasanatteruMouse;
	int BackAlpha;
	double DY;
	int* MouseGrHandle;
	int MouseAnimCnt;
	bool MouseAnimF;
	bool DekaF;
};

