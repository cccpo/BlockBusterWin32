#include <iostream>

#include "GameBoard.h"
#include "ScoreManager.h"

typedef unsigned char byte;

using std::cout;
using std::endl;

static int sBoard[GameBoard::mGbWidth + 2][GameBoard::mGbHeight + 2];

// ゲームボード初期化
void GameBoard::InitGameBoard() {

    //ゲームボード内部の初期化
    for (int x = 1; x < mGbWidth + 1; ++x) {
        for (int y = 1; y < mGbHeight + 1; ++y) {
            sBoard[x][y] = GetmEmpty();    
        }
    }
  
    //ゲームボード外枠の初期化
    for (int x = 0; x <= mGbWidth + 1; ++x) {
        sBoard[x][0] = sBoard[x][mGbHeight + 1] = mOuterFrame;
    }
    for (int y = 0; y <= mGbHeight + 1; ++y) {
        sBoard[0][y] = sBoard[mGbWidth + 1][y] = mOuterFrame;
    }

};

// ゲームボードの値をゲット
int GameBoard::GetGameBoardValue(int inPosX, int inPosY) {
    int s = sBoard[inPosX][inPosY];
    return s;
}

// ゲームボードの値をセット
void GameBoard::SetTerimonoValue(int inPosX,int inPosY,int inValue) {
    sBoard[inPosX][inPosY] = inValue;
}

// 一段落とす(揃ったときに使用)
void GameBoard::Down(int inLinePosY) {

    while (inLinePosY > 1) {
        for (int x = 1; x <= mGbWidth; ++x)
            sBoard[x][inLinePosY] = sBoard[x][inLinePosY - 1];     // １行下に移動
        --inLinePosY;      //  上の行に
    }
    
    for (int x = 1; x <= mGbWidth; ++x)
        sBoard[x][1] = 0;     // 最上行は空に
}

// 初期化関数
const int GameBoard::GetmEmpty(){
    return mEmpty;
}

// ゲームボードのx座標を返す
int GameBoard::GetGameBoardPosX() {
    return mGameBoardPosX;
}

// ゲームボードのy座標を返す
int GameBoard::GetGameBoardPosY(){
    return mGameBoardPosY;
}

GameBoard::GameBoard() :mGameBoardPosX(1),mGameBoardPosY(2){

}

//　ゲームボードを生成する座標及びを与える
GameBoard::GameBoard(int inPosX,int inPosY) :mGameBoardPosX(inPosX),mGameBoardPosY(inPosY){
}




