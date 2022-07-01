#include<DxLib.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"apple.h"
#include"hensuu.h"

#define  RANKING_DATA  5

APPLE apple[APPLE_MAX];
HENSUU hen;

//�萔�̐錾
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//const int ENEMY_MAX = 8;
//const int ITEM_MAX = 3;

//���@�̏����l
const int PLAYER_POS_X = SCREEN_WIDTH / 2;
const int PLAYER_POS_Y = SCREEN_HEIGHT - 100;
const int PLAYER_WIDTH = 63;
const int PLAYER_HEIGHT = 120;
const int PLAYER_SPEED = 5;
const int PLAYER_HP = 1000;
const int PLAYER_FUEL = 20000;
const int PLAYER_BARRIER = 3;
const int PLAYER_BARRIERUP = 10;

//���@�̍\����
//struct PLAYER {
//	int flg;
//	int x, y;
//	int w, h;
//	double angle;
//	int count;
//	int speed;
//	int hp;
//	int fuel;
//	int bari;
//	int baricnt;
//	int bariup;
//};

//���@
PLAYER g_player;

//�G�@�̍\����
struct ENEMY {
	int flg;
	int type;
	int img;
	int x, y, w, h;
	int speed;
	int point;
	int cnt;
};

//�G�@
struct ENEMY g_enemy[ENEMY_MAX];
struct ENEMY g_enemy00 = { TRUE,0,0,0,-50,63,120,0,1 };
struct ENEMY g_enemyCn = { TRUE,4,0,0,-50,18,18,0,1 };

struct ENEMY g_item[ITEM_MAX];
struct ENEMY g_item00 = { TRUE,0,0,0,-50,50,50,0,1 };

//�����L���O�f�[�^�i�\���́j
struct RankingData {
	int no;
	char name[11];
	long score;
};

//�����L���O�f�[�^�ϐ��錾
struct RankingData  g_Ranking[RANKING_DATA];

//�֐��̃v���g�^�C�v�錾
void GameInit(void);
void GameMain(void);

void DrawGameTitle(void);
void DrawGameOver(void);
void DrawEnd(void);
void DrawHelp(void);

void DrawRanking(void);
void InputRanking(void);
void SortRanking(void);
int SaveRanking(void);
int ReadRanking(void);

//void ItemControl();
//int CreateItem();

void EnemyControl(); //�G�@����
int CreateEnemy(); //�G�@��������

//void BackScrool();//�w�i�摜�X�N���[������

int LoadImages();
void PlayerControl();

int HitBoxPlayer(PLAYER* p, ENEMY* e);  //�����蔻��

int nextTime;
int g_AppleCount[4];
//�v���O�����J�n
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow)
{
	SetMainWindowText("Drive & Avoid");   //�^�C�g����ݒ�
	ChangeWindowMode(TRUE);
	SetWindowSize(640, 480);
	if (DxLib_Init() == -1)return-1;
	SetDrawScreen(DX_SCREEN_BACK);
	if (LoadImages() == -1)return-1;
	if (ReadRanking() == -1)return-1;

	//�Q�[�����[�v
	while (ProcessMessage() == 0 && hen.g_GameState != 99 && !(hen.g_KeyFlg & PAD_INPUT_START))
	{
		hen.g_OldKey = hen.g_NowKey;
		hen.g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		hen.g_KeyFlg = hen.g_NowKey & ~hen.g_OldKey;

		ClearDrawScreen();

		switch (hen.g_GameState) {
		case 0:DrawGameTitle();
			break;
		case 1:GameInit();
			break;
		case 2:DrawRanking();
			break;
		case 3:DrawHelp();
			break;
		case 4:DrawEnd();
			break;
		case 5:GameMain();
			break;
		case 6:DrawGameOver();
			break;
		case 7:InputRanking();
			break;
		}
		ScreenFlip();
	}
	DxLib_End();

	return 0;
}

//�Q�[���^�C�g���\��
void DrawGameTitle(void) {
	static int MenuNo = 0;

	//���j���[�J�[�\���ړ�����
	if (hen.g_KeyFlg & PAD_INPUT_DOWN) {
		if (++MenuNo > 3)MenuNo = 0;
	}if (hen.g_KeyFlg & PAD_INPUT_UP) {
		if (--MenuNo < 0)MenuNo = 3;
	}

	//Z�L�[�Ń��j���[�I��
	if (hen.g_KeyFlg & PAD_INPUT_A)hen.g_GameState = MenuNo + 1;

	//�^�C�g���摜�\��
	DrawGraph(0, 0, hen.g_TitleImage, FALSE);

	//���j���[
	DrawGraph(120, 200, hen.g_Menu, TRUE);

	//���j���[�J�[�\��
	DrawRotaGraph(90, 220 + MenuNo * 40, 0.7f, M_PI / 2, hen.g_Cone, TRUE);
}

//�Q�[����������
void GameInit(void) {
	//�X�R�A�̏�����
	hen.Score = 0;

	//���s������������
	hen.g_Mileage = 0;

	//�G�P����������̏����l
	hen.g_EnemyCount1 = 0;
	hen.g_EnemyCount2 = 0;
	hen.g_EnemyCount3 = 0;
	hen.g_EnemyCount4 = 0;

	//�v���C���[�̏����ݒ�
	g_player.flg = TRUE;
	g_player.x = PLAYER_POS_X;
	g_player.y = PLAYER_POS_Y;
	g_player.w = PLAYER_WIDTH;
	g_player.h = PLAYER_HEIGHT;
	g_player.angle = 0.0;
	g_player.count = 0;
	g_player.speed = PLAYER_SPEED;
	g_player.hp = PLAYER_HP;
	g_player.fuel = PLAYER_FUEL;
	g_player.bari = PLAYER_BARRIER;
	g_player.bariup = PLAYER_BARRIERUP;

	//�G�l�~�[�̏����ݒ�
	for (int i = 0; i < APPLE_MAX; i++) {
		apple[i].flg = FALSE;
	}
	//�A�C�e���̏����ݒ�
	for (int i = 0; i < ITEM_MAX; i++) {
		g_item[i].flg = FALSE;
	}
	//�����S�̃J�E���g�̏�����
	for (int i = 0; i < 4; i++) {
		g_AppleCount[i] = 0;
	}

	hen.g_Time = 1800;
	nextTime = hen.g_Time - GetRand(MAX_INTERVAL);

	//�Q�[�����C��������
	hen.g_GameState = 5;
}

//�Q�[�������L���O�`��\��
void DrawRanking(void) {
	//�X�y�[�X�L�[�Ń��j���[�ɖ߂�
	if (hen.g_KeyFlg & PAD_INPUT_M)  hen.g_GameState = 0;
	//�����L���O�摜�\��
	DrawGraph(0, 0, hen.g_RankingImage, FALSE);
	//�����L���O�ꗗ��\��
	SetFontSize(18);
	for (int i = 0; i < RANKING_DATA; i++) {
		DrawFormatString(50, 170 + i * 25, 0xffffff, "%2d %10s %10d", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
	}
	DrawString(100, 450, "---- �X�y�[�X�L�[�������ă^�C�g���֖߂� ----", 0xffffff, 0);
}

//�Q�[���w���v�`�揈��
void DrawHelp(void) {
	//�X�y�[�X�L�[�Ń��j���[�ɖ߂�
	if (hen.g_KeyFlg & PAD_INPUT_M) hen.g_GameState = 0;

	//�^�C�g���摜�\��
	DrawGraph(0, 0, hen.g_TitleImage, FALSE);
	SetFontSize(16);
	DrawString(20, 120, "�w���v���", 0xffffff, 0);

	DrawString(20, 160, "����͏�Q��������Ȃ���", 0xffffff, 0);
	DrawString(20, 180, "���葱����Q�[���ł�", 0xffffff, 0);
	DrawString(20, 200, "�R�����s���邩��Q����", 0xffffff, 0);
	DrawString(20, 220, "���񓖂���ƃQ�[���I�[�o�[�ł�", 0xffffff, 0);
	DrawString(20, 250, "�A�C�e���ꗗ", 0xffffff, 0);
	DrawGraph(20, 260, hen.g_Item[0], TRUE);
	DrawString(20, 315, "���ƔR�����񕜂����B", 0xffffff, 0);
	DrawGraph(20, 335, hen.g_Item[1], TRUE);
	DrawString(20, 385, "�_���[�W���󂯂Ă��鎞�Ɏ��Ƒϋv��", 0xffffff, 0);
	DrawString(20, 405, "�ϋv�������Ă��Ȃ�������R���������񕜂����B", 0xffffff, 0);
	DrawString(20, 450, "---- �X�y�[�X�L�[�������ă^�C�g���֖߂� ----", 0xffffff, 0);
}

//�Q�[���G���h�`�揈��
void DrawEnd(void) {
	//�G���h�摜�\��
	DrawGraph(0, 0, hen.g_EndImage, FALSE);
	SetFontSize(24);
	DrawString(360, 480 - 24, "Thank you for Playing", 0xffffff, 0);

	//�^�C���̉��Z����&�I��
	if (++hen.g_WaitTime > 180) hen.g_GameState = 99;
}

//�Q�[�����C��
void GameMain(void) {
	DrawGraph(0, 0, hen.Backimg, FALSE);
	PlayerControl();
	for (int i = 0; i < APPLE_MAX; i++) {
		apple[i].AppleControl();
	}
	if (--hen.g_Time < nextTime) {
		for (int i = 0; i < APPLE_MAX; i++) {
			if (apple[i].CreateApple()) {
				nextTime -= GetRand(MAX_INTERVAL);
				break;
			}
		}
	}

	////�X�y�[�X�L�[�Ń��j���[�ɖ߂�
	//if (g_KeyFlg & PAD_INPUT_M) g_GameState = 6;

	//SetFontSize(16);
	//DrawString(20, 20, "�Q�[�����C��", 0xffffff, 0);
	//DrawString(150, 450, "---- �X�y�[�X�L�[�������ăQ�[���I�[�o�[�� ----", 0xffffff, 0);
}

void EnemyControl() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].flg == TRUE) {
			//�G�̕\��
			DrawRotaGraph(g_enemy[i].x, g_enemy[i].y, 1.0f, 0, g_enemy[i].img, TRUE, FALSE);

			if (g_player.flg == FALSE) continue;

			//�܂��������Ɉړ�
			g_enemy[i].y += g_enemy[i].speed + g_player.speed - PLAYER_SPEED + 1;

			//��ʂ��͂ݏo���������
			if (g_enemy[i].y > SCREEN_HEIGHT + g_enemy[i].h) g_enemy[i].flg = FALSE;

			//�G�@��ǂ��z������J�E���g
			if (g_enemy[i].y > g_player.y && g_enemy[i].point == 1) {
				g_enemy[i].point = 0;
				if (g_enemy[i].type == 0)hen.g_EnemyCount1++;
				if (g_enemy[i].type == 1)hen.g_EnemyCount2++;
				if (g_enemy[i].type == 2)hen.g_EnemyCount3++;
				if (g_enemy[i].type == 3)hen.g_EnemyCount4++;
			}

			if (++hen.g_Time < 120) {
				if (g_enemy[i].type == 3)g_enemy[i].x += hen.v[g_enemy[i].cnt] + g_enemy[i].speed - PLAYER_SPEED + 3;
			}
			else if (++hen.g_Time < 240) {
				if (g_enemy[i].type == 3)g_enemy[i].x -= hen.v[g_enemy[i].cnt] + g_enemy[i].speed - PLAYER_SPEED + 3;
			}
			else if (hen.g_Time > 300) {
				hen.g_Time = 0;
			}

			//�����蔻��
			if (HitBoxPlayer(&g_player, &g_enemy[i]) == TRUE && g_player.baricnt <= 0) {
				g_player.flg = FALSE;
				g_player.speed = PLAYER_SPEED;
				g_player.count = 0;
				g_player.hp -= 100;
				g_enemy[i].flg = FALSE;
				if (g_player.hp <= 0)  hen.g_GameState = 6;
			}
		}
	}

	//���s�������ƂɓG�o���p�^�[���𐧌䂷��
	if (hen.g_Mileage / 10 % 50 == 0) {
		//apple.CreateApple();
	}
}

int CreateEnemy() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].flg == FALSE) {
			g_enemy[i].cnt = 0;
			g_enemy[i] = g_enemy00;
			g_enemy[i].type = GetRand(3);
			g_enemy[i].img = hen.g_Teki[g_enemy[i].type];
			g_enemy[i].x = GetRand(4) * 105 + 40;
			g_enemy[i].speed = g_enemy[i].type * 2;
			//����
			return TRUE;
		}
	}
	return FALSE;
}

int HitBoxPlayer(PLAYER* p, ENEMY* e) {
	//x,y�͒��S���W�Ƃ���
	int sx1 = p->x - (p->w / 2);
	int sy1 = p->y - (p->h / 2);
	int sx2 = sx1 + p->w;
	int sy2 = sy1 + e->h;

	int dx1 = e->x - (e->w / 2);
	int dy1 = e->y - (e->h / 2);
	int dx2 = dx1 + e->w;
	int dy2 = dy1 + e->h;

	//�Z�`���d�Ȃ��Ă���Γ�����
	if (sx1 < dx2 - 5 && dx1 < sx2 - 5 && sy1 < dy2 - 5 && dy1 < sy2 - 5) {
		return TRUE;
	}
	if (hen.g_EnemyCount4) {
		if (sx1 < dx2 - 150 && dx1 < sx2 - 150 && sy1 < dy2 - 150 && dy1 < sy2 - 150) {
			return TRUE;
		}
	}
	return FALSE;
}

void PlayerControl() {
	//�R���̏���
	//g_player.fuel -= g_player.speed;
	//�Q�[���I�[�o�[������
	if (hen.g_Time <= 0)  hen.g_GameState = 6;

	//Z�L�[�ŉ���
	//if (hen.g_KeyFlg & PAD_INPUT_A && g_player.speed < 10) g_player.speed += 1;
	//X�L�[�Ō���
	//if (hen.g_KeyFlg & PAD_INPUT_B && g_player.speed > 1) g_player.speed -= 1;

	//�㉺���E�ړ�
	if (g_player.flg == TRUE) {
		if (hen.g_NowKey & PAD_INPUT_LEFT) g_player.x -= g_player.speed;
		if (hen.g_NowKey & PAD_INPUT_RIGHT) g_player.x += g_player.speed;
	}

	//��ʂ��͂ݏo���Ȃ��悤�ɂ���
	if (g_player.x < 32)  g_player.x = 32;
	if (g_player.x > SCREEN_WIDTH - 180)  g_player.x = SCREEN_WIDTH - 180;
	if (g_player.y < 60)  g_player.y = 60;
	if (g_player.y > SCREEN_HEIGHT - 60)  g_player.y = SCREEN_HEIGHT - 60;

	//�v���C���[�̕\��
	if (g_player.flg == TRUE) {
		if (hen.g_NowKey & PAD_INPUT_LEFT) {
			DrawRotaGraph(g_player.x, g_player.y, 1.0f, -M_PI / 18, hen.g_Car, TRUE, FALSE);
		}
		else if (hen.g_NowKey & PAD_INPUT_RIGHT) {
			DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / 18, hen.g_Car, TRUE, FALSE);
		}
		else {
			DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, hen.g_Car, TRUE, FALSE);
		}

		//if (hen.g_KeyFlg & PAD_INPUT_C && g_player.bari > 0 && g_player.baricnt <= 0) {
		//	g_player.bari--;
		//	g_player.baricnt = 1000;
		//}
		//if (g_player.baricnt > 0) {
		//	g_player.baricnt -= g_player.speed;
		//	DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, hen.g_Barrier, TRUE, FALSE);
		//}
		//else {
		//	g_player.baricnt = 0;
		//}
	}
	else {
		DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / 8 * (++g_player.count / 5), hen.g_Car, TRUE, FALSE);
		if (g_player.count >= 80)  g_player.flg = TRUE;
	}

	//�G�����������\��
	SetFontSize(25);
	DrawFormatString(520, 20, 0x000000, "��������");
	DrawFormatString(560, 60, 0xffffff, "%d", hen.g_Time / 60);
	DrawRotaGraph(528, 120, 0.5f, 0, hen.AppleImages[0], TRUE, FALSE);
	DrawRotaGraph(558, 120, 0.5f, 0, hen.AppleImages[1], TRUE, FALSE);
	DrawRotaGraph(588, 120, 0.5f, 0, hen.AppleImages[2], TRUE, FALSE);
	DrawRotaGraph(618, 120, 0.5f, 0, hen.AppleImages[3], TRUE, FALSE);

	SetFontSize(16);
	DrawFormatString(520, 140, 0xFFFFFF, "%02d", g_AppleCount[0]);
	DrawFormatString(550, 140, 0xFFFFFF, "%02d", g_AppleCount[1]);
	DrawFormatString(580, 140, 0xFFFFFF, "%02d", g_AppleCount[2]);
	DrawFormatString(610, 140, 0xFFFFFF, "%02d", g_AppleCount[3]);

	/*DrawFormatString(510, 20, 0x000000, "�n�C�X�R�A");
	DrawFormatString(560, 40, 0xFFFFFF, "%08d", g_Ranking[0].score);
	DrawFormatString(510, 80, 0x000000, "��������");
	DrawRotaGraph(523, 120, 0.3f, 0, hen.g_Teki[0], TRUE, FALSE);
	DrawRotaGraph(553, 120, 0.3f, 0, hen.g_Teki[1], TRUE, FALSE);
	DrawRotaGraph(583, 120, 0.3f, 0, hen.g_Teki[2], TRUE, FALSE);
	DrawRotaGraph(613, 120, 0.3f, 0, hen.g_Teki[3], TRUE, FALSE);

	DrawFormatString(515, 140, 0xFFFFFF, "%02d", hen.g_EnemyCount1);
	DrawFormatString(545, 140, 0xFFFFFF, "%02d", hen.g_EnemyCount2);
	DrawFormatString(575, 140, 0xFFFFFF, "%02d", hen.g_EnemyCount3);
	DrawFormatString(605, 140, 0xFFFFFF, "%02d", hen.g_EnemyCount4);
	DrawFormatString(510, 200, 0x000000, "���s����");
	DrawFormatString(555, 220, 0xFFFFFF, "%08d", hen.g_Mileage / 10);
	DrawFormatString(510, 240, 0x000000, "�X�s�[�h");
	DrawFormatString(555, 260, 0xFFFFFF, "%08d", g_player.speed);*/

	//�o���A�̕\��
	//for (int i = 0; i < g_player.bari; i++) {
	//	DrawRotaGraph(520 + i * 25, 340, 0.2f, 0, hen.g_Barrier, TRUE, FALSE);
	//}

	//�R���Q�[�W�̕\��
	//int F_X = 510; int F_Y = 390; int F_W = 100; int F_H = 20;
	//DrawString(F_X, F_Y, "FUEL METER", 0x000000, 0);
	////�����Q�[�W
	//DrawBox(F_X, F_Y + 20, F_X + (int)(g_player.fuel * F_W / PLAYER_FUEL), F_Y + 20 + F_H, 0x0066cc, TRUE);
	////�O���Q�[�W�g
	//DrawBox(F_X, F_Y + 20, F_X + F_W, F_Y + 20 + F_H, 0x0066cc, FALSE);

	////�̗̓Q�[�W�̕\��
	//int X = 510; int Y = 430; int W = 100; int H = 20;
	//DrawString(X, Y, "PLAYER HP", 0x000000, 0);
	////�����̃Q�[�W
	//DrawBox(X, Y + 20, X + (int)(g_player.hp * W / PLAYER_HP), Y + 20 + H, 0xff0000, TRUE);
	////�O���̃Q�[�W�g
	//DrawBox(X, Y + 20, X + W, Y + 20 + H, 0x000000, FALSE);
}

//�Q�[���I�[�o�[�摜�`�揈��
void DrawGameOver(void) {
	hen.Score = (hen.g_Mileage / 10 * 10) + hen.g_EnemyCount3 * 50 + hen.g_EnemyCount2 * 100 + hen.g_EnemyCount1 * 200;

	//�X�y�[�X�L�[�Ń��j���[�ɖ߂�
	if (hen.g_KeyFlg & PAD_INPUT_M) {
		if (g_Ranking[RANKING_DATA - 1].score >= hen.Score) {
			hen.g_GameState = 0;
		}
		else {
			hen.g_GameState = 7;
		}
	}

	//BackScrool();


	DrawBox(150, 150, 490, 330, 0x009900, TRUE);
	DrawBox(150, 150, 490, 330, 0x000000, FALSE);

	SetFontSize(20);
	DrawString(220, 170, "�Q�[���I�[�o�[", 0xcc0000);
	SetFontSize(16);
	DrawString(180, 200, "���s�����@�@�@", 0x000000);

	DrawRotaGraph(230, 230, 0.3f, M_PI / 2, hen.g_Teki[2], TRUE, FALSE);
	DrawRotaGraph(230, 250, 0.3f, M_PI / 2, hen.g_Teki[1], TRUE, FALSE);
	DrawRotaGraph(230, 270, 0.3f, M_PI / 2, hen.g_Teki[0], TRUE, FALSE);
	DrawRotaGraph(230, 290, 0.3f, M_PI / 2, hen.g_Teki[3], TRUE, FALSE);

	DrawFormatString(260, 200, 0xFFFFFF, "%6d x  10 = %6d", hen.g_Mileage / 10, hen.g_Mileage / 10 * 10);
	DrawFormatString(260, 222, 0xFFFFFF, "%6d x  50 = %6d", hen.g_EnemyCount3, hen.g_EnemyCount3 * 50);
	DrawFormatString(260, 243, 0xFFFFFF, "%6d x 100 = %6d", hen.g_EnemyCount2, hen.g_EnemyCount2 * 100);
	DrawFormatString(260, 264, 0xFFFFFF, "%6d x 200 = %6d", hen.g_EnemyCount1, hen.g_EnemyCount1 * 200);
	DrawFormatString(260, 285, 0xFFFFFF, "%6d x 300 = %6d", hen.g_EnemyCount4, hen.g_EnemyCount4 * 300);

	DrawString(310, 310, "�X�R�A", 0x000000);
	DrawFormatString(260, 310, 0xFFFFFF, "             = %6d", hen.Score);
	DrawString(150, 450, "---- �X�y�[�X�L�[�������ă^�C�g���֖߂� ----", 0xffffff, 0);
}

//�����L���O���͏���
void InputRanking(void) {
	//�����L���O�摜�\��
	DrawGraph(0, 0, hen.g_RankingImage, FALSE);
	SetFontSize(20);

	//���O���͎w��������̕`��
	DrawString(150, 240, "�����L���O�ɓo�^���܂�", 0xffffff);
	DrawString(150, 270, "���O���p���œ��͂��Ă�������", 0xffffff);

	//���O�̓���
	DrawString(150, 310, ">", 0xffffff);
	DrawBox(160, 305, 300, 335, 0x000055, TRUE);

	if (KeyInputSingleCharString(170, 310, 10, g_Ranking[4].name, FALSE) == 1) {
		g_Ranking[4].score = hen.Score;
		SortRanking();
		SaveRanking();
		hen.g_GameState = 2;
	}
}

//�����L���O���ёւ�
void SortRanking(void) {
	int i, j;
	RankingData work;

	//�I���\�[�g
	for (i = 0; i < 4; i++) {
		for (j = i + 1; j < 5; j++) {
			if (g_Ranking[i].score <= g_Ranking[j].score) {
				work = g_Ranking[i];
				g_Ranking[i] = g_Ranking[j];
				g_Ranking[j] = work;
			}
		}
	}

	//���ʕt��
	for (i = 0; i < 5; i++) {
		g_Ranking[i].no = i + 1;
	}
	//���_�������������ꍇ�́A�������ʂƂ���
	//�����ʂ��������ꍇ�̎��̏��ʂ̓f�[�^�������Z���ꂽ���ʂƂ���
	for (i = 0; i < 4; i++) {
		for (j = i + 1; j < 5; j++) {
			if (g_Ranking[i].score > g_Ranking[j].score) {
				g_Ranking[j].no++;
			}
		}
	}
}

//�����L���O�f�[�^�̕ۑ�
int SaveRanking(void) {
	FILE* fp;
#pragma warning(disable:4996)

	//�t�@�C���I�[�v��
	if ((fp = fopen("rankingdata.txt", "w")) == NULL) {
		//�G���[����
		printf("Ranking Data Error\n");
		return-1;
	}

	//�����L���O�f�[�^���z��f�[�^����������
	for (int i = 0; i < 5; i++) {
		fprintf(fp, "%2d %10s %10d\n", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
	}

	//�t�@�C���N���[�Y
	fclose(fp);

	return 0;
}

//�����L���O�f�[�^�ǂݍ���
int ReadRanking(void) {
	FILE* fp;
#pragma warning(disable:4996)
	if ((fp = fopen("rankingdata.txt", "r")) == NULL) {
		printf("Ranking Data Error\n");
		return-1;
	}

	fclose(fp);

	
	return 0;
}



