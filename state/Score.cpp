#include "Score.h"

int mScore = 0;
static int mHighScore;

//scoreŽæ“¾
int Score::GetScore() const{
	return mScore;
};


void Score::SetScore(int sc) {
	mScore = sc;
};

void Score::AddScore(int a) {
	
	switch (a) {
	case 1: mScore += 50; break;
	case 2: mScore += 100; break;
	case 3: mScore += 160; break;
	case 4: mScore += 250; break;
	}
	
	SetScore(mScore);
}

int Score::GetHighScore() const {
	return mHighScore;
}

void Score::SetHighScore(int hs) {
	mHighScore = hs;
}