#include "Bank.h"
#include "DxLib.h"


Bank::Bank()
{

	//0:�v���C���[
	LoadDivGraph("Resource/Images/Akazukin.png",
		64, 8, 8, 48, 48, ImageHandle[0]);
	//1:�n��
	LoadDivGraph("Resource/Images/Jimen.png",
		48, 4, 12, 16, 16, ImageHandle[1]);
	//2:����
	LoadDivGraph("Resource/Images/Flower.png",
		16, 4, 4, 16, 16, ImageHandle[2]);
	//3:�X���C��
	LoadDivGraph("Resource/Images/Slime.png",
		64, 8, 8, 16, 16, ImageHandle[3]);
	//4:�{�^��
	LoadDivGraph("Resource/Images/Button.png",
		64, 8, 8, 16, 16, ImageHandle[4]);
	//5:�}�E�X�|�C���^
	LoadDivGraph("Resource/Images/MousePoint.png",
		1, 1, 1, 32, 32, ImageHandle[5]);
	//6:Fade
	LoadDivGraph("Resource/Images/Fade.png",
		16, 4, 4, 16, 16, ImageHandle[6]);
	//7:������
	LoadDivGraph("Resource/Images/frog.png",
		64, 8, 8, 16, 16, ImageHandle[7]);
	//8:���݂Ȃ肳��
	LoadDivGraph("Resource/Images/Oni.png",
		64, 8, 8, 32, 32, ImageHandle[8]);
	//9:Deka�{�^��
	LoadDivGraph("Resource/Images/DekaButton.png",
		64, 8, 8, 48, 24, ImageHandle[9]);
	//10:���݂Ȃ�
	LoadDivGraph("Resource/Images/Kaminari.png",
		16, 4, 4, 16, 16, ImageHandle[10]);
	//11:����
	LoadDivGraph("Resource/Images/Koge.png",
		4, 2, 2, 32, 32, ImageHandle[11]);
	//12:�}�E�X
	LoadDivGraph("Resource/Images/Mouse.png",
		4, 2, 2, 8, 8, ImageHandle[12]);
	//13:�䂤����
	LoadDivGraph("Resource/Images/Yusya.png",
		64, 8, 8, 48, 48, ImageHandle[13]);
	//14:�{�X
	LoadDivGraph("Resource/Images/Boss.png",
		64, 8, 8, 32, 32, ImageHandle[14]);
	//15:��
	LoadDivGraph("Resource/Images/Fire.png",
		16, 4, 4, 16, 16, ImageHandle[15]);
	//16:��
	LoadDivGraph("Resource/Images/Iwa.png",
		16, 4, 4, 16, 16, ImageHandle[16]);
	//17:�r�[��
	LoadDivGraph("Resource/Images/Beem.png",
		16, 4, 4, 16, 16, ImageHandle[17]);
	//18:����������
	LoadDivGraph("Resource/Images/MiniChar.png",
		64, 8, 8, 3, 3, ImageHandle[18]);
	//19:kiran
	LoadDivGraph("Resource/Images/Kiran.png",
		16, 4, 4, 36, 27, ImageHandle[19]);
	//20:����
	LoadDivGraph("Resource/Images/Kagi.png",
		16, 4, 4, 36, 27, ImageHandle[20]);
	//21:��
	LoadDivGraph("Resource/Images/ClickEffect.png",
		16, 4, 4, 16, 16, ImageHandle[21]);
	//22:���[�v�}��A
	LoadDivGraph("Resource/Images/WarpManA.png",
		64, 8, 8, 16, 16, ImageHandle[22]);
	//23:���[�v�}��B
	LoadDivGraph("Resource/Images/WarpManB.png",
		64, 8, 8, 16, 16, ImageHandle[23]);
	//24:���[�v�G�t�F�N�g
	LoadDivGraph("Resource/Images/WarpEffect.png",
		16, 4, 4, 32, 32, ImageHandle[24]);


	SoundHandle[0] = LoadSoundMem("Resource/Sounds/���C���e�[�}.wav");
	SoundHandle[1] = LoadSoundMem("Resource/Sounds/�͂�����.wav");
	SoundHandle[2] = LoadSoundMem("Resource/Sounds/������.wav");
	SoundHandle[3] = LoadSoundMem("Resource/Sounds/jump1.wav");
	SoundHandle[4] = LoadSoundMem("Resource/Sounds/bomb1.wav");
	SoundHandle[5] = LoadSoundMem("Resource/Sounds/�҂���.wav");
	SoundHandle[6] = LoadSoundMem("Resource/Sounds/���񂽂�.wav");
	SoundHandle[7] = LoadSoundMem("Resource/Sounds/�����.wav");
	SoundHandle[8] = LoadSoundMem("Resource/Sounds/����SE.wav");
	SoundHandle[9] = LoadSoundMem("Resource/Sounds/AdrenaH.wav");
	SetLoopPosSoundMem(2690, SoundHandle[9]);
	SoundHandle[10] = LoadSoundMem("Resource/Sounds/����.wav");
	SoundHandle[11] = LoadSoundMem("Resource/Sounds/shoot.wav");
	SoundHandle[12] = LoadSoundMem("Resource/Sounds/bomb1eco.wav");
	SoundHandle[13] = LoadSoundMem("Resource/Sounds/Osanpoppi.wav");
	SoundHandle[14] = LoadSoundMem("Resource/Sounds/�r��ɐ��܂肵����.wav");
	SetLoopPosSoundMem(1875, SoundHandle[14]);
	SoundHandle[15] = LoadSoundMem("Resource/Sounds/Dhukusi.wav");
	SoundHandle[16] = LoadSoundMem("Resource/Sounds/BUBBLY CLOUDS.wav");
	SoundHandle[17] = LoadSoundMem("Resource/Sounds/������ǂ�.wav");


	const char* filename = "Resource/Font/SMILEBASIC.ttf";
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
		MiniFontHandle = CreateFontToHandle("�X�}�C���x�[�V�b�N", 32, 0, -1);
	}
	else
	{
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}



	int mode = 0;
	for (int stage = 0; stage < SD_STAGEMAX; stage++)
	{
		char FileName[64];
		sprintf_s(FileName, "StageData/%d.txt\0", stage);
		////printfDx("FileName=%s", FileName);
		int FileHandle;
		FileHandle = FileRead_open(FileName);

		//�t�@�C������������
		if (FileHandle == 0)
			continue;

		int Cnt = 0;
		int sdY = 0;

		while (FileRead_eof(FileHandle) == 0)
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
				for (int i = 0; i < SD_STRMAX; i++)
				{
					StageComponents[mode][stage].StageName[i] = temp[i];
					if (temp[i] == '\0')
						break;
				}
				Cnt = 1;
				break;
			case 1://�Ԃ̖��O
				for (int i = 0; i < SD_STRMAX; i++)
				{
					StageComponents[mode][stage].FlowerName[i] = temp[i];
					if (temp[i] == '\0')
						break;
				}
				Cnt = 2;
				break;
			case 2://�Ԍ��t
				for (int i = 0; i < SD_STRMAX; i++)
				{
					StageComponents[mode][stage].FlowerMessage[i] = temp[i];
					if (temp[i] == '\0')
						break;
				}
				Cnt = 3;
				break;
			case 3://�X�e�[�W�f�[�^
				for (int sdX = 0; sdX < 12; sdX++)
				{
					StageComponents[mode][stage].StageData[sdX+sdY*12] = temp[sdX];
				}
				sdY++;
				break;
			}

		}
	}

}

void Bank::PlaySe(int Num)
{
	PlaySoundMem(SoundHandle[Num], DX_PLAYTYPE_BACK);
}

void Bank::PlayBgm(int Num)
{
	if (CheckSoundMem(SoundHandle[Num]) == 1)
		return;
	StopSoundMem(SoundHandle[0]);
	StopSoundMem(SoundHandle[1]);
	StopSoundMem(SoundHandle[9]);
	StopSoundMem(SoundHandle[13]);
	StopSoundMem(SoundHandle[14]);
	StopSoundMem(SoundHandle[16]);

	PlaySoundMem(SoundHandle[Num], DX_PLAYTYPE_LOOP);
}

void Bank::StopBgm(int Num)
{
	StopSoundMem(SoundHandle[Num]);
	
	StopSoundMem(SoundHandle[0]);
	StopSoundMem(SoundHandle[1]);
	StopSoundMem(SoundHandle[9]);
	StopSoundMem(SoundHandle[13]);
	StopSoundMem(SoundHandle[14]);
	StopSoundMem(SoundHandle[16]);

}



int * Bank::GetGrHandle(int Num)
{
	return ImageHandle[Num];
}

int * Bank::GetSoundHandle(int Num)
{
	return &SoundHandle[Num];
}

int Bank::GetMiniFontHandle()
{
	return MiniFontHandle;
}

char* Bank::GetStageData(int Mode, int StageNum)
{
	return StageComponents[Mode][StageNum].StageData;
}
