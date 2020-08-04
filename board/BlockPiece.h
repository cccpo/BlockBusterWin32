#pragma once
#include <Windows.h>
#include <vector>
#include <random>
#include <stdlib.h>

#include "GameBoard.h"

typedef unsigned char byte;

const int gTetriminoHeight = { 4 };
const int gTetriminoWidth = { 4 };



class BlockPiece
{
private:
	
	

	
public:
	int mTetriminoPosX;//ゲームボード左上からの相対的な位置
	int mTetriminoPosY;
	int mTetriminoType;//テトリミノのタイプ

	//テトリミノのタイプを列挙　#ToDO 名前は仮
	enum class TetrimnoType:int
	{
		TypeA=1,TypeB,TypeC,TypeD,TypeE,TypeF,TypeG
	};
	

	int mTetrimino[gTetriminoWidth][gTetriminoHeight];



	bool IsMoveDown(GameBoard inGameBoard);//接触判定
	bool IsMoveLeft(GameBoard inGaneBoard);//左に移動する
	bool IsMoveRight(GameBoard inGaneBoard);//右に移動する
	bool IsOverLaped(GameBoard inGaneBoard);//枠外にいるかを判定
	
	void ChangeBlock(GameBoard inGaneBoard);//テトリミノを固定化
	
	void DeleteLine(GameBoard inGaneBoard);// 揃ったラインを消去

	int GetRot(const GameBoard& ioGaneBoard);//現在のテトリミノの回転タイプをゲット

	void SetTertimino(const GameBoard& ioGameBoard, int type, int inTetriminoType);//テトリミノをゲームボードに配置
	void AddTertimino(const GameBoard& ioGameBoard); // テトリミノの追加
	
	//inline
	inline int GetTetriminoPosX(const GameBoard& inGameBoard) { return mTetriminoPosX;};
	inline void SetTeriminoPosX(int inTetriminoPosX) {mTetriminoPosX = inTetriminoPosX;};

	inline int GetTetriminoPosY(const GameBoard& inGaneBoard) { return mTetriminoPosY;};
	inline void SetTeriminoPosY(int inTetriminoPosY) { mTetriminoPosY = inTetriminoPosY; };

	inline int GetTeriminoType(const GameBoard& inGaneBoard) { return mTetriminoType; };
	inline void SetTeriminoType(int inTetriminoType) {mTetriminoType = inTetriminoType;};
	

	void SetRot(int r);

	int GetTeriminoValue(int x, int y);
	

	
	BlockPiece();
	//~BlockPiece();

protected:
	GameBoard inGaneBoard;

};

