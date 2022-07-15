#include "DxLib.h"
#include "variable.h"
#include "Title.h"
#include"pad.h"
#include "Load.h"

//�Q�[���^�C�g���\��
void TITLE::DrawGameTitle(void) {
	static int MenuNo = 0;
	if (CheckSoundMem(TitleBGM) == 0)
	PlaySoundMem(TitleBGM, DX_PLAYTYPE_BACK);
	//���j���[�J�[�\���ړ�����
	if (pad.g_KeyFlg & PAD_INPUT_DOWN) {
		if (++MenuNo > 3)MenuNo = 0;
		PlaySoundMem(load.MoveSE, DX_PLAYTYPE_BACK);
	}
	if (pad.g_KeyFlg & PAD_INPUT_UP) {
		if (--MenuNo < 0)MenuNo = 3;
		PlaySoundMem(load.MoveSE, DX_PLAYTYPE_BACK);
	}

	//Z�L�[�Ń��j���[�I��
	if (pad.g_KeyFlg & PAD_INPUT_A) {
		var.g_GameState = MenuNo + 1;
		PlaySoundMem(load.ClickSE, DX_PLAYTYPE_BACK);
	}

	//�^�C�g���摜�\��
	DrawGraph(0, 0, g_TitleImage, FALSE);

	//���j���[�J�[�\��
	DrawRotaGraph(430, 300 + MenuNo * 42, 0.7f, 0, applecursor, TRUE);
}
