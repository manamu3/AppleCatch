#include "Ranking.h"
#include "hensuu.h"
#include "font.h"
#include "pad.h"
#include "DxLib.h"

//ゲームランキング描画表示
void RANKING::DrawRanking(void) {
	//スペースキーでメニューに戻る
	if (hen.g_KeyFlg & PAD_INPUT_2) {
		hen.g_GameState = 0;
		PlaySoundMem(hen.CancelSE, DX_PLAYTYPE_BACK);
	}
	//ランキング画像表示
	DrawGraph(0, 0, hen.g_RankingImage, FALSE);
	//ランキング一覧を表示
	//SetFontSize(18);
	for (int i = 0; i < RANKING_DATA; i++) {
		DrawFormatStringToHandle(90, 170 + i * 35, 0xffffff, font.fontking, "%2d %+10s %10d", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
	}
	SetFontSize(25);
	DrawString(150, 430, "---- Bボタンで戻る ----", 0xffffff, 0);
}

void RANKING::InputRanking(void) {
	//ランキング画像表示
	DrawGraph(0, 0, hen.g_RankingImage, FALSE);
	SetFontSize(20);

	//名前入力指示文字列の描画
	DrawStringToHandle(110, 120, "ランキングに登録します", 0xffffff, font.fontrans);
	DrawStringToHandle(110, 150, "名前を英字で入力してください", 0xffffff, font.fontrans);

	//名前の入力
	DrawString(110, 210, ">", 0xffffff);
	DrawBox(120, 200, 317, 240, 0x000055, TRUE);

	pad.DrawInput();
	//try {
	if (hen.g_KeyFlg & PAD_INPUT_8 && pad.inputnum > 0) {
		//g_Ranking[4].name = pad.inputchar;
		PlaySoundMem(hen.ClickSE, DX_PLAYTYPE_BACK);
		strcpy_s(g_Ranking[4].name, 11, pad.inputchar);
		g_Ranking[4].score = hen.Score;
		SortRanking();
		SaveRanking();
		hen.g_GameState = 2;
	}
	//}
	//catch (int& err) {
	//	printf("エラーコード%d\n", err);
	//}

	//if (KeyInputSingleCharString(130, 210, 10, g_Ranking[4].name, FALSE) == 1) {
	//	g_Ranking[4].score = hen.Score;
	//	SortRanking();
	//	SaveRanking();
	//	hen.g_GameState = 2;
	//}
}

//ランキング並び替え
void RANKING::SortRanking(void) {
	int i, j;
	RankingData work;

	//選択ソート
	for (i = 0; i < 4; i++) {
		for (j = i + 1; j < 5; j++) {
			if (g_Ranking[i].score <= g_Ranking[j].score) {
				work = g_Ranking[i];
				g_Ranking[i] = g_Ranking[j];
				g_Ranking[j] = work;
			}
		}
	}

	//順位付け
	for (i = 0; i < 5; i++) {
		g_Ranking[i].no = 1;
	}
	//得点が同じだった場合は、同じ順位とする
	//同順位があった場合の次の順位はデータ個数が加算された順位とする
	for (i = 0; i < 4; i++) {
		for (j = i + 1; j < 5; j++) {
			if (g_Ranking[i].score > g_Ranking[j].score) {
				g_Ranking[j].no++;
			}
		}
	}
}

//ランキングデータの保存
int RANKING::SaveRanking(void) {
	FILE* fp;
#pragma warning(disable:4996)

	//ファイルオープン
	if ((fp = fopen("rankingdata.txt", "w")) == NULL) {
		//エラー処理
		printf("Ranking Data Error\n");
		return-1;
	}

	//ランキングデータ分配列データを書き込む
	for (int i = 0; i < 5; i++) {
		fprintf(fp, "%2d %10s %10d\n", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
	}

	//ファイルクローズ
	fclose(fp);

	return 0;
}

//ランキングデータ読み込み
int RANKING::ReadRanking(void) {
	FILE* fp;
#pragma warning(disable:4996)
	if ((fp = fopen("rankingdata.txt", "r")) == NULL) {
		printf("Ranking Data Error\n");
		return-1;
	}

	for (int i = 0; i < 5; i++) {
		fscanf(fp, "%2d %10s %10d\n", &g_Ranking[i].no, g_Ranking[i].name, &g_Ranking[i].score);
	}

	fclose(fp);


	return 0;
}