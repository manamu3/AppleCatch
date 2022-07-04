#pragma once
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int ENEMY_MAX = 8;
const int ITEM_MAX = 3;
const int MAX_INTERVAL = 3 * 60;

struct PLAYER {
	int flg;
	int x, y;
	int w, h;
	double angle;
	int count;
	int speed;
	int hp;
	int fuel;
	int bari;
	int baricnt;
	int bariup;
};

extern PLAYER g_player;

extern int g_AppleCount[4];

class HENSUU {
public:
	//�ϐ��̐錾
	int g_OldKey;    // �O��̓��̓L�[
	int g_NowKey;    // ����̓��̓L�[
	int g_KeyFlg;    // ���̓L�[���

	int g_GameState = 0;

	int g_TitleImage;
	int g_Menu, applecursor;

	int Score = 0;  // �X�R�A
	int g_Time;   //����

	int g_RankingImage;

	int g_Item[2];

	int g_WaitTime = 0;  //�҂�����
	int g_EndImage;
	int HelpImage;

	int g_Mileage; //���s����
	int g_EnemyCount1, g_EnemyCount2, g_EnemyCount3, g_EnemyCount4; //�G�J�E���g
	int g_Teki[4]; //�L�����摜�ϐ�

	int g_StageImage;
	int AppleImages[4];//�����S�̉摜

	int CharaImages[3];//�L�����摜

	int Backimg;

	int g_Car, g_Barrier;
	int g_Player[3];
	int g_Back = 0;
	int v[3] = { -1,0,1 };
};
extern HENSUU hen;