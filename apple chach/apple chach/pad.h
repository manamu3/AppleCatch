#pragma once

class PAD {
private:
	int cursorX = 0;
	int cursorY = 0;
	const int OffSetX = 120;
	const int OffSetY = 250;

public:
	char inputchar[10];
	int inputnum = 0;
	int g_OldKey;    // �O��̓��̓L�[
	int g_NowKey;    // ����̓��̓L�[
	int g_KeyFlg;    // ���̓L�[���

public:
	void DrawInput(void);
};

extern PAD pad;