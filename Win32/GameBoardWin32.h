#pragma once

#include <Windows.h>

#include "../Data/Data.h"
#include "../board/ScoreManager.h"

#include "DrawEngineWin32.h"
#include "TetriminoSet.h"


class GameBoardWin32
{

public:
	GameBoardWin32(DrawEngineWin32& draw_engine_win32,
				   int game_board_width = 10, int game_board_height = 20);
	~GameBoardWin32();

	inline int GetScore() const{ return mScore;};
	inline int GetHiScore() const { return HiScore; };

	bool IsHiScore();

	/*void CheckHiScore();*/
	const void DrawGameBoard();//GameBoardの描画を描画エンジンに行わせる

	bool Rotate();//回転

	bool Move(int move_to_x, int move_to_y);// テトリミノを移動

	void UpdateTime();

	bool IsGameOver();//ゲームオーバーであるかを確認する
	const void DrawScore();//スコアを描画
	const void DrawHiScore();//ハイスコアを描画
	const void DrawSpeed();//落下速度レベルを描画
	const void DrawLines();//消したラインの数を表示
	const void DrawNextTetrimino();//次のテトリミノを描画

protected:
		bool Place(int inPosX, int inPosY, const TetriminoWin32& ioTetrimino);

		
		void ClearTetrimino(const TetriminoWin32& piece);

		
		void MakeRandomPiece();

		const bool IsHitBottom();
		const bool IsHitLeft();
		const bool IsHitRight();

		const bool IsCovered(const TetriminoWin32& piece, int inPosX, int inPosY);

		// 揃った行を削除する
		int ClearRows();


		COLORREF** game_board_win32;
		DrawEngineWin32& draw_engine_win32;

		TetriminoSet tetrimino_set; 
		TetriminoWin32* current_tetrimino;    
		TetriminoWin32* next_tetrimino;

		ScoreManager score_manager;
		Data data;


		int game_board_width;
		int game_board_height;

		int mPosX;
		int mPosY; 
		int mSpeed; 
		double mLastTime;   
		double mCurrentTime;  
		int mScore;
		int mHiScore;
		int mLines;
};

