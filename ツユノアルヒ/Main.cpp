#include "DxLib.h"
#include "SceneMgr.h"
#include "Mouse.h"
#include "Shake.h"
#include "Resource.h"
#include "EffectMgr.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//ログ出力を行わない
	SetOutApplicationLogValidFlag(FALSE);
	const char* filename = "Resource/Font/JF-Dot-MPlusH10.ttf";
	// ファイルのサイズを得る
	int FontFileSize = FileRead_size(filename);
	// フォントファイルを開く
	int FontFileHandle = FileRead_open(filename);

	// フォントデータ格納用のメモリ領域を確保
	void *Buffer = malloc(FontFileSize);
	// フォントファイルを丸ごとメモリに読み込む
	FileRead_read(Buffer, FontFileSize, FontFileHandle);

	// AddFontMemResourceEx引数用
	DWORD font_num = 0;

	// メモリに読み込んだフォントデータをシステムに追加
	if (AddFontMemResourceEx(Buffer, FontFileSize, NULL, &font_num) != 0)
	{
	}
	else
	{
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}
	//ログ出力を行わない
	SetOutApplicationLogValidFlag(FALSE);
	
	
	int flag;
	flag = MessageBox(
		NULL,
		TEXT("フルスクリーンモードで起動しますか？"),
		TEXT("スクリーン設定"),
		MB_YESNO | MB_ICONQUESTION);
	if (flag == IDNO)
		ChangeWindowMode(TRUE);
	

	//ChangeWindowMode(TRUE);
	SetWindowText("てくてく花ずきん");
	SetWindowIconID(IDI_ICON2);
	SetWindowSizeChangeEnableFlag(TRUE);
	//SetGraphMode(192 * 4, 144 * 4, 32);
	SetGraphMode(768, 576,16);
	//SetGraphMode(56 * 10, 32 * 10, 32);
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	SetFullScreenScalingMode(DX_FSSCALINGMODE_NEAREST);
	SetWindowSizeExtendRate(1);
	//ChangeFont("MS ゴシック");
	//ChangeFont("JFドット東雲ゴシック12");
	ChangeFont("JFドットM+H10");
	//ChangeFont("スマイルベーシック");
	SetFontSize(10*4);
	SetFontThickness(0);

	DxLib_Init();	// DXライブラリ初期化処理
	SetMouseDispFlag(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);

	SceneMgr TekuHanaSceneMgr(TITLESCENE);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0  && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && Mouse::Instance()->Update() == 0 && Shake::Instance()->Update() == 0)
	{
		TekuHanaSceneMgr.Update();
		if (TekuHanaSceneMgr.GetOwari() == 2)
			break;
		EffectMgr::Instance()->Update();
		TekuHanaSceneMgr.Draw();
		Mouse::Instance()->Draw();
	}

	DxLib_End();	// DXライブラリ終了処理
	return 0;
}