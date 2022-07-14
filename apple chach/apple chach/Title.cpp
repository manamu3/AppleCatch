#include "DxLib.h"
#include "hensuu.h"
#include "Title.h"

void TITLE::DrawGameTitle(void) {
	static int MenuNo = 0;
	if (CheckSoundMem(TitleBGM) == 0)
	PlaySoundMem(TitleBGM, DX_PLAYTYPE_BACK);
	//���j���[�J�[�\���ړ�����
	if (hen.g_KeyFlg & PAD_INPUT_DOWN) {
		if (++MenuNo > 3)MenuNo = 0;
		PlaySoundMem(hen.MoveSE, DX_PLAYTYPE_BACK);
	}
	if (hen.g_KeyFlg & PAD_INPUT_UP) {
		if (--MenuNo < 0)MenuNo = 3;
		PlaySoundMem(hen.MoveSE, DX_PLAYTYPE_BACK);
	}

	//Z�L�[�Ń��j���[�I��
	if (hen.g_KeyFlg & PAD_INPUT_A) {
		hen.g_GameState = MenuNo + 1;
		PlaySoundMem(hen.ClickSE, DX_PLAYTYPE_BACK);
	}

	//�^�C�g���摜�\��
	DrawGraph(0, 0, g_TitleImage, FALSE);

	//���j���[�J�[�\��
	DrawRotaGraph(430, 300 + MenuNo * 42, 0.7f, 0, applecursor, TRUE);
}
