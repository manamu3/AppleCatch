#include"DxLib.h"
#include"hensuu.h"
#include"Font.h"
#include"End.h"

void END::DrawEnd() {
	//�G���h�摜�\��
	//DrawGraph(0, 0, hen.EndImg, FALSE);

	DrawStringToHandle(65, 30, "Thank you for Playing !!", 0xffff00, font.fonten);

	if (++hen.g_WaitTime < 90)hen.PosY = 90 - hen.g_WaitTime / 2;
	DrawStringToHandle(80, 70 + hen.PosY, "�^�C�g���@�@AppleChach", 0xffffff, font.fontensc);
	DrawStringToHandle(80, 110 + hen.PosY, "����ҁ@���ۓd�q�r�W�l�X���w�Z", 0xffffff, font.fontensc);
	DrawStringToHandle(80, 150 + hen.PosY, "�@�@�@�@�@����@��m", 0xffffff, font.fontensc);
	DrawStringToHandle(80, 190 + hen.PosY, "�@�@�@�@�@�u�o���@���l", 0xffffff, font.fontensc);
	DrawStringToHandle(80, 230 + hen.PosY, "�@�@�@�@�@��ԁ@����", 0xffffff, font.fontensc);
	DrawStringToHandle(80, 270 + hen.PosY, "�@�@�@�@�@�V���@�A�l", 0xffffff, font.fontensc);
	DrawStringToHandle(80, 310 + hen.PosY, "�f�ޗ��p", 0xffffff, font.fontensc);
	DrawStringToHandle(80, 350 + hen.PosY, "BGM�@�@�@�@������", 0xffffff, font.fontensc);
	DrawStringToHandle(80, 390 + hen.PosY, "SE�@�@�@�@   ������", 0xffffff, font.fontensc);

	//�^�C���̉��Z����&�I��
	if (++hen.g_WaitTime > 160) hen.g_GameState = 99;
}
