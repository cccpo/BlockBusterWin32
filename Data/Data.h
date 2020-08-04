#pragma once
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

static int HiScore;

class Data

{
private:

public:

	int HiScoreLoad();//"HiScore.txt"よりハイスコアを取得
	void HiScoreSave(int inHiScore);//ハイスコアを"HiScore.txt"に保存する
};

