#pragma once

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int MAX_INTERVAL = 1 * 60;

extern int g_AppleCount[4];

class HENSUU {
public:
	//�ϐ��̐錾
	int g_OldKey;    // �O��̓��̓L�[
	int g_NowKey;    // ����̓��̓L�[
	int g_KeyFlg;    // ���̓L�[���

	int g_GameState = 0;
	int Score = 0;  // �X�R�A
	int g_Time;   //����
	int g_PauseFlg;  //�|�[�Y�t���O

	int AppleImages[4];//�����S�̉摜
	int PlayerImages[3];//�L�����摜

	int GameImage;
	int g_RankingImage;
	int EndImage;

	//SE
	int FallSE, CatchSE, PoisonSE, GetAppleSE; //Apple SE
	int MoveSE, ClickSE, CancelSE; //Button SE

	//BGM
	int GameBGM;
};
extern HENSUU hen;