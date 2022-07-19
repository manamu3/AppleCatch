#include"DxLib.h"
#include"variable.h"
#include"UI.h"
#include <math.h>

void UI::DrawUI() {
	//UI�̘g�\��
	DrawBox(SCREEN_WIDTH - 130, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x00ffff, TRUE);

	//�������Ԃ̕\��
	SetFontSize(25);
	DrawFormatString(520, 20, 0x000000, "��������");
	DrawFormatString(560, 60, 0x000000, "%d", (int)ceil((double)var.g_Time / 60.0));

	//��񂲂����������\��
	SetFontSize(16);
	for (int i = 0; i < 4; i++) {
		DrawRotaGraph(528 + i * 30, 120, 0.5f, 0, var.AppleImages[i], TRUE, FALSE);
		DrawFormatString(520 + i * 30, 140, 0x000000, "%02d", g_AppleCount[i]);
	}

	SetFontSize(30);
	DrawFormatString(530, 180, 0x000000, "�X�R�A");
	SetFontSize(32);
	DrawFormatString(522, 220, 0x000000, "%06d", var.Score);
}