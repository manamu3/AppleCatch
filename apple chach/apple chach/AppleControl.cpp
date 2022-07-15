#define _USE_MATH_DEFINES
#include "apple.h"
#include "Player.h"
#include "variable.h"
#include "DxLib.h"
#include"Load.h"

void APPLE::AppleControl() {
		if (flg == TRUE) {
			//�G�̕\��
			DrawGraph(x, y, img, TRUE);

			if (player.g_PauseFlg == 0) {
				y += speed;
			}

			//��ʂ��͂ݏo���������
			if (y > SCREEN_HEIGHT + h) flg = FALSE;

			//�����蔻��
			if (HitBoxPlayer(&player) == TRUE) {
				g_AppleCount[type]++;
				var.Score += point;
				flg = FALSE;
				if (type == 3) {
					PlaySoundMem(load.PoisonSE, DX_PLAYTYPE_BACK);
					player.flg = FALSE;
					player.count = 120;
					if (var.Score < 0) {
						var.Score = 0;
					}
				}
				else {
					PlaySoundMem(load.CatchSE, DX_PLAYTYPE_BACK);
				}
			}
		}
}