#pragma once
//#define G 1
#define EXRATE 4

class Sprite
{
private:
	int SpAnimColorR[2];
	int SpAnimColorG[2];
	int SpAnimColorB[2];
	int SpAnimColorTime;
	int SpAnimColorCnt;
	int SpAnimColorF;
	
	int SpAnimF;
	int SpAnimGrHandle[16];
	int SpAnimTime[16];
	int SpAnimTimeSum;
	int SpAnimTimeCnt;
	int SpAnimLoop;
	int SpAnimLoopCnt;
	int SpAnimNum;

	int DrawR, DrawG, DrawB;

	int SpAnimAlphaF;
	int SpAnimAlphaValue[2];
	int SpAnimAlphaTime;
	int SpAnimAlphaCnt;

	//int DrawAlpha;

	int ColSqr[4];
protected:
	double X, Y;
	double VX, VY;
	double AX, AY;
	int R;
	int GrHandle;
	int GrNum;
	double ExRate;
	double Angle;
	int *GrHandleData;
	int FuchiByougaF;
	int FuchiEffectF;
	int FuchiEffectCnt;
	double FuchiEffectX;
	double FuchiEffectV;
	int DrawAlpha;
	bool NegaF;
public:
	void SetXY(double X, double Y);
	double GetX();
	double GetY();
	void SetVX(double VX);
	void SetVY(double VY);
	double GetVX();
	double GetVY();
	void SetAX(double AX);
	void SetAY(double AY);
	double GetAX();
	double GetAY();
	void SetR(int R) { this->R = R; };
	int GetR() { return R; };
	void SetDrawRGB(int R, int G, int B);
	void SetGrHandle(int GrHandle);
	void SetGrHandleData(int* GrHandleData);
	void SetGrNum(int GrNum);
	void SetAngle(double Rad);
	void SetExRate(double ExRate);
	void SetDrawAlpha(int DrawAlpha);
	double GetAngle();
	void SetColSqr(int X1, int Y1, int X2, int Y2);
	void GetColSqr(int *X1, int *Y1, int *X2, int *Y2);
	bool CheckHitSp(Sprite* Sp);
	bool CheckHitSpDeka(Sprite * Sp);
	void SpAnim(int T1, int C1, int T2, int C2, int T3, int C3, int T4, int C4, int LoopNum);
	void SpAnim(int T1, int C1, int T2, int C2, int T3, int C3, int T4, int C4, int T5, int C5, int T6, int C6, int LoopNum);
	void SpAnim(int T1, int C1, int T2, int C2, int T3, int C3, int T4, int C4, int T5, int C5, int LoopNum);
	void SpAnim(int T1, int C1, int T2, int C2, int T3, int C3, int T4, int C4, int T5, int C5, int T6, int C6, int T7, int C7, int T8, int C8, int LoopNum);
	void SpAnim(int T1, int C1, int T2, int C2, int T3, int C3, int T4, int C4, int T5, int C5, int T6, int C6, int T7, int C7, int T8, int C8, int T9, int C9, int T10, int C10, int T11, int C11, int LoopNum);
	void SpAnimStop();
	void SpAnimUpdate();
	int GetSpAnimF();
	void SpAnimColor(int R1, int G1, int B1, int Time, int R2, int G2, int B2);
	void SpAnimColorUpdate();
	void SpAnimAlpha(int Value1, int Time, int Value2);
	void SpAnimAlphaStop();
	void SpAnimAlphaUpdate();
	void DrawFuchi();
	void DrawFuchiEffect();
	int GetFuchiByougaF();
	void SetFuchiByougaF(int FuchiByougaF);
	void SetNegaF(bool NegaF);
	bool GetNegaF();
	virtual void Update();
	virtual void Draw();
	Sprite();
	~Sprite();
};
