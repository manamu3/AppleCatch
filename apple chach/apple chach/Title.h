#pragma once

class TITLE {
public:
	int g_TitleImage;//�^�C�g���摜
	int TitleBGM;//�^�C�g����BGM
	int applecursor;//�^�C�g���̃J�[�\���摜
	int Player2;
	int Player3;

private:
	int PlayerY = 0;
	int PlayerX = 0;
	int Time = 0;
	int Time2 = 0;

public:
	void DrawGameTitle(void);

private:
	void DrawPlayer();
};

extern TITLE title;