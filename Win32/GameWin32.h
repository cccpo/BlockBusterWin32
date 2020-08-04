#include "DrawEngineWin32.h"
#include "GameBoardWin32.h"
#include "TetriminoSet.h"
#include "TetriminoWin32.h"


class GameWin32
{

public:
	GameWin32(DrawEngineWin32& draw_engine_win32);
	~GameWin32();

	void RestartGame();//ゲームをリスタート
	void UpdateTime();//時間を更新

	const void PriorityDraw();// 描画対象を呼び出す
	
	void Pause(bool inPaused);// 一時停止
	bool IsKeyPress(int inInputKey);// Key入力検出
	
	void DrawHiScore() const;
	void DrawGameOver() const;
	void DrawPause() const;

	bool IsGameOver() const;//ゲームオーバー判定
protected:
	DrawEngineWin32& draw_engine_win32;
	GameBoardWin32* game_board_win32;

	bool mIsPaused;
	bool mIsUpdateHiScore;
};