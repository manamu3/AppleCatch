#pragma once
#include"DxLib.h"
class FONT
{
public:
	int font00 = CreateFontToHandle("Tsunagi Gothic Black", 20, 1, DX_FONTTYPE_NORMAL);
	int fonten = CreateFontToHandle("Tsunagi Gothic Black", 50, 1, DX_FONTTYPE_NORMAL);
	int fontensc = CreateFontToHandle("���S�V�b�N Medium", 20, 3, DX_FONTTYPE_NORMAL);
	int fontran = CreateFontToHandle("Tsunagi Gothic Black", 40, 1, DX_FONTTYPE_NORMAL);
	int fontrans = CreateFontToHandle("Tsunagi Gothic Black", 30, 1, DX_FONTTYPE_NORMAL);
	int fontpose = CreateFontToHandle("wb_font", 50, 5, DX_FONTTYPE_NORMAL);
	int fontking = CreateFontToHandle("MS �S�V�b�N", 30, 5, DX_FONTTYPE_NORMAL);
private:

};

extern FONT font;