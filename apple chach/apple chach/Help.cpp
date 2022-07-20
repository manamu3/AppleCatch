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
	DrawRotaGraph(480, 250, 0.7f, 0, GamepadImage, TRUE);

	DrawBox(10, 130, 310, 355, 0xffffff, 1);
    DrawStringToHandle(20, 140, "���E�ɓ����ė����Ă���\n�l�X�ȃ����S���E���Q�[���ł��B", 0x000000, font.fontHelp);
	DrawStringToHandle(20, 180, "���㉺�ړ��͂ł��܂���", 0x000000, font.fontHelp);
	DrawStringToHandle(20, 200, "�������Ԃ�30�b�ł��B", 0x000000, font.fontHelp);
	DrawStringToHandle(20, 220, "���X�e�B�b�N�F�ړ�", 0xff00ff, font.fontHelp);
	DrawStringToHandle(20, 240, "A�{�^���F����  B�{�^���F�߂�", 0xff00ff, font.fontHelp);
	DrawStringToHandle(20, 260, "�v���C����START�{�^����������\n�|�[�Y�Ɉڍs���܂��B", 0xff00ff, font.fontHelp);
	DrawStringToHandle(20, 300, "(������x������\n�v���C��ʂɖ߂�܂�)", 0xff00ff, font.fontHelp);

	SetFontSize(20);
	DrawBox(10, 355, 310, 475, 0xffffff, 1);
	DrawStringToHandle(20, 360, "�����S�ꗗ", 0x000000, font.fontHelp);
	DrawGraph(20, 380, var.AppleImages[0], TRUE);
	DrawString(62, 395, "+150P", 0x000000, 0);
	DrawGraph(120, 380, var.AppleImages[1], TRUE);
	DrawString(162, 395, "+300P", 0x000000, 0);
	DrawGraph(20, 430, var.AppleImages[2], TRUE);
	DrawString(62, 445, "+500P", 0x000000, 0);
	DrawGraph(120, 430, var.AppleImages[3], TRUE);
	DrawString(160, 445, "-1000P", 0xff0000, 0);

	SetFontSize(23);
	DrawString(470, 420, "�߂�[B�{�^��]", 0xff0000,1);
	DrawString(420, 450, "�Q�[����[A�{�^��]", 0x0000ff,1);

	//DrawStringToHandle(20, 120, "�w���v���", 0xffffff, font.fontHelp);
}