#include"DxLib.h"
#include"Help.h"
#include"variable.h"
#include"Font.h"
#include"pad.h"
#include"Load.h"

void HELP::DrawHelp() {
	//B�{�^���Ń��j���[�ɖ߂�
	if (pad.g_KeyFlg & PAD_INPUT_2) {
		var.g_GameState = 0;
		PlaySoundMem(load.CancelSE, DX_PLAYTYPE_BACK);
	}
	//�Q�[���J�n
	if (pad.g_KeyFlg & PAD_INPUT_A) {
		var.g_GameState = 1;
		PlaySoundMem(load.ClickSE, DX_PLAYTYPE_BACK);
	}

	//�w���v�摜�\��
	DrawGraph(0, 0, HelpImage, FALSE);
	SetFontSize(16);

	DrawString(20, 160, "����͗����Ă��郊���S���E���Q�[���ł��B", 0x000000, 0);
	DrawString(20, 180, "���E�ɓ����ė����Ă���l�X�ȃ����S���E���܂��B", 0x000000, 0);
	DrawString(20, 200, "���㉺�ړ��͂ł��܂���", 0x000000, 0);
	DrawString(20, 220, "�������Ԃ�30�b�ł��B", 0x000000, 0);
	DrawString(20, 250, "�����S�ꗗ", 0x000000, 0);
	DrawGraph(20, 260, var.AppleImages[0], TRUE);
	DrawString(62, 275, "+150P", 0x0000ff, 0);
	DrawGraph(120, 260, var.AppleImages[1], TRUE);
	DrawString(162, 275, "+300P", 0x0000ff, 0);
	DrawGraph(220, 260, var.AppleImages[2], TRUE);
	DrawString(262, 275, "+500P", 0x0000ff, 0);
	DrawString(20, 315, "�ԁA���A�ΐF�̃����S���Ƃ�ƃX�R�A���������B", 0x000000, 0);
	DrawGraph(20, 335, var.AppleImages[3], TRUE);
	DrawString(60, 350, "-1000P", 0xff0000, 0);
	DrawString(20, 385, "�Ń����S�ɐG���Ƃ������������B", 0x000000, 0);
	DrawString(20, 425, "�v���C����START�{�^���������ƃ|�[�Y�Ɉڍs���܂��B", 0x000000, 0);
	DrawString(20, 445, "(������x�����ƃv���C��ʂɖ߂�܂�)", 0x000000, 0);
	DrawString(490, 450, "�Q�[����[A�{�^��]", 0x000000, 0);
	DrawString(524, 430, "�߂�[B�{�^��]", 0x000000, 0);

	DrawStringToHandle(20, 120, "�w���v���", 0xffffff, font.fontHelp);
}