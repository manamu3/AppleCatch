#pragma once

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int MAX_INTERVAL = 1 * 60;

extern int g_AppleCount[4];

class Variable {
public:
	//�ϐ��̐錾
	int g_GameState = 0;
	int Score = 0;  // �X�R�A
	int g_Time;   //����

	int AppleImages[4];//�����S�̉摜
	int PlayerImages[3];//�L�����摜

	int GameImage;

	//BGM
	int GameBGM;
};
extern Variable var;