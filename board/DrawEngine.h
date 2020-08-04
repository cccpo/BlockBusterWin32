#pragma once
#include <Windows.h>

#include "GameBoard.h"
#include "BlockPiece.h"
#include "Value.h"
#include "../Data/Data.h"
#include "ScoreManager.h"

//　GameBoardの描画を行うクラス
class DrawEngine
{
private:
	int gbpx, gbpy;

	enum Mask {
		Intensity = 8, RedMask = 4, GreenMask = 2, BlueMask = 1
	};

public:
	enum class Color : int
	{
		Black = 0x00, DarkBlue, DarkGreen, DarkCyan, DarkRed, DarkViolet, DarkYellow, Gray, LightGray, Blue,
		Green, Cyan, Red, Violet, Yellow, White

	};

	void DefaultDrawBoard(const GameBoard& ioGameBoard);//ゲームボード外枠の描画
	void DrawBoard(const GameBoard& ioGameBoard,const Color& cl);//ゲームボード外枠の描画
	void DrawStage(GameBoard inGameBoard);//ゲームボード内部の描画
	
	void DrawTetrimino(GameBoard ioGameBoard, const BlockPiece& ioBlockPiece);

	int TetriminoTypeToColor(int inTetriminoType);//テトリミノの形状から色を設定する

	void DrawScore(ScoreManager inScore);//スコア表示

	void DrawHiScore();

	void DrawRotType();

	void SetColor(int inForeGroundColor, int inBackGroundColor);
	void SetCursorPos(int inConsolePosX, int inConsolePosY);

	//DrawGameBoard(){}
	//~DrawGameBoard(){}

protected:
	GameBoard game_board;
	BlockPiece block_piece;
	ScoreManager score;
	Data data;


};

