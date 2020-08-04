#pragma once


//スコア管理クラス
class ScoreManager
{
private:
	


 public:
	
	const int GetScore();////スコアを取得
	void SetScore(int inScore);//スコアをセット

	void AddScore(int inAddScore);//消去パターンに応じてスコアを加算
	int AddScoreWin32(int inDeletePattern);


	const int GetHighScore();//　ハイスコアをゲット
	void SetHighScore(int inHiScore);// ハイスコアをセット


	//Score() {};
	//~Score() {};
};

