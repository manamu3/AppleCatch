#pragma once

class HENSUU {
public:
	//�ϐ��̐錾
	int g_OldKey;
	int g_NowKey;
	int g_KeyFlg;

	int g_GameState = 0;

	int g_TitleImage;
	int g_Menu, g_Cone;

	int g_Score = 0;
	int g_Time = 0;

	int g_RankingImage;

	int g_Item[2];

	int g_WaitTime = 0;  //�҂�����
	int g_EndImage;

	int g_Mileage; //���s����
	int g_EnemyCount1, g_EnemyCount2, g_EnemyCount3, g_EnemyCount4; //�G�J�E���g
	int g_Teki[4]; //�L�����摜�ϐ�

	int g_StageImage;
	int AppleImages[4];

	int g_Car, g_Barrier;
	int g_Back = 0;
	int v[3] = { -1,0,1 };
};
extern HENSUU hen;