#pragma once

#define  RANKING_DATA  5

class RANKING {
public:
	//�����L���O�f�[�^�i�\���́j
	struct RankingData {
		int no;
		char name[11];
		long score;
	};

	int g_RankingImage;

	//�����L���O�f�[�^�ϐ��錾
	struct RankingData  g_Ranking[RANKING_DATA];

	int ReadRanking(void);
	void DrawRanking(void);
	void InputRanking(void);

private:
	void SortRanking(void);
	int SaveRanking(void);
};

extern RANKING ranking;