#pragma once

class Load {
public:
	//SE
	int FallSE, PoisonSE, CatchSE; //Apple SE
	int MoveSE, ClickSE, CancelSE; //�{�^��SE

public:
	int LoadImages();
	int LoadSound();
};

extern Load load;