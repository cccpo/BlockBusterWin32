#pragma once
#include "TetriminoWin32.h"
#include <Windows.h>

class DrawEngineWin32
{
public:
	DrawEngineWin32(HDC mHdc, HWND mHwnd, 
					int mBlockSize = 25, int mWidth = 10, int mHeight = 20);

	~DrawEngineWin32();

	void DrawTetrimino(int pos_x, int pos_y, COLORREF color);//テトリミノ描画
	void DrawNextTetrimino(TetriminoWin32& ioTetrimino, int pos_x, int pos_y);//次のテトリミノを描画

	void DrawUIRightArea();//右UIエリア描画
	void DrawUILeftArea();//左UIエリア描画

	void DrawTextOn(TCHAR *text, int pos_x, int pos_y) const;//テキスト描画
	void DrawTextOnRed(TCHAR* text, int pos_x, int pos_y) const;//赤文字テキスト描画
	
	const void DrawScore(int inScore, int pos_x, int pos_y);//スコア表示
	const void DrawHiScore(int inHiScore, int pos_x, int pos_y);//　ハイスコア表示
	const void DrawLines(int inLines, int pos_x, int pos_y);//削除したライン数を表示

	const void DrawSpeed(int inSpeed, int x, int y) ;


protected:
	HDC mHdc;
	HWND mHwnd;
	RECT mRect;
	int mWidth;
	int mHeight;


};

