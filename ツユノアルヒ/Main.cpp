#include "DxLib.h"
#include "SceneMgr.h"
#include "Mouse.h"
#include "Shake.h"
#include "Resource.h"
#include "EffectMgr.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//���O�o�͂��s��Ȃ�
	SetOutApplicationLogValidFlag(FALSE);
	const char* filename = "Resource/Font/JF-Dot-MPlusH10.ttf";
	// �t�@�C���̃T�C�Y�𓾂�
	int FontFileSize = FileRead_size(filename);
	// �t�H���g�t�@�C�����J��
	int FontFileHandle = FileRead_open(filename);

	// �t�H���g�f�[�^�i�[�p�̃������̈���m��
	void *Buffer = malloc(FontFileSize);
	// �t�H���g�t�@�C�����ۂ��ƃ������ɓǂݍ���
	FileRead_read(Buffer, FontFileSize, FontFileHandle);

	// AddFontMemResourceEx�����p
	DWORD font_num = 0;

	// �������ɓǂݍ��񂾃t�H���g�f�[�^���V�X�e���ɒǉ�
	if (AddFontMemResourceEx(Buffer, FontFileSize, NULL, &font_num) != 0)
	{
	}
	else
	{
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}
	//���O�o�͂��s��Ȃ�
	SetOutApplicationLogValidFlag(FALSE);
	
	
	int flag;
	flag = MessageBox(
		NULL,
		TEXT("�t���X�N���[�����[�h�ŋN�����܂����H"),
		TEXT("�X�N���[���ݒ�"),
		MB_YESNO | MB_ICONQUESTION);
	if (flag == IDNO)
		ChangeWindowMode(TRUE);
	

	//ChangeWindowMode(TRUE);
	SetWindowText("�Ă��Ă��Ԃ�����");
	SetWindowIconID(IDI_ICON2);
	SetWindowSizeChangeEnableFlag(TRUE);
	//SetGraphMode(192 * 4, 144 * 4, 32);
	SetGraphMode(768, 576,16);
	//SetGraphMode(56 * 10, 32 * 10, 32);
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	SetFullScreenScalingMode(DX_FSSCALINGMODE_NEAREST);
	SetWindowSizeExtendRate(1);
	//ChangeFont("MS �S�V�b�N");
	//ChangeFont("JF�h�b�g���_�S�V�b�N12");
	ChangeFont("JF�h�b�gM+H10");
	//ChangeFont("�X�}�C���x�[�V�b�N");
	SetFontSize(10*4);
	SetFontThickness(0);

	DxLib_Init();	// DX���C�u��������������
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

	DxLib_End();	// DX���C�u�����I������
	return 0;
}