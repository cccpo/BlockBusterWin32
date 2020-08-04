#include <iostream>


#include "DrawEngine.h"




using std::cout;
using std::endl;

//ゲームボード外枠の描画
void DrawEngine::DefaultDrawBoard(const GameBoard& ioGameBoard) {
	//色設定
	SetColor((int)Color::Gray, (int)Color::Gray);

	SetCursorPos(ioGameBoard.mGameBoardPosX, ioGameBoard.mGameBoardPosY);
	for (int x = 0; x < GameBoard::mGbWidth + 2; ++x) {
		cout << "  ";
	}

	SetCursorPos(ioGameBoard.mGameBoardPosX, ioGameBoard.mGameBoardPosY + GameBoard::mGbHeight + 1);
	for (int x = 0; x < GameBoard::mGbWidth + 2; ++x) {
		cout << "  ";
	}
	for (int y = ioGameBoard.mGameBoardPosY + 1; y < ioGameBoard.mGameBoardPosY + GameBoard::mGbHeight + 1; ++y) {
		SetCursorPos(ioGameBoard.mGameBoardPosX, y);
		cout << "  ";
		SetCursorPos(ioGameBoard.mGameBoardPosX + (GameBoard::mGbWidth + 1) * 2, y);
		cout << "  ";
	}
}

//ゲームボード外枠の描画(外枠色指定)
void DrawEngine::DrawBoard(const GameBoard& ioGameBoard, const Color& cl) 
{
	//色設定
	SetColor((int)cl, (int)cl);

	SetCursorPos(ioGameBoard.mGameBoardPosX, ioGameBoard.mGameBoardPosY);
	for (int x = 0; x < GameBoard::mGbWidth + 2; ++x) {
		cout << "  ";
	}

	SetCursorPos(ioGameBoard.mGameBoardPosX, ioGameBoard.mGameBoardPosY + GameBoard::mGbHeight + 1);
	for (int x = 0; x < GameBoard::mGbWidth + 2; ++x) {
		cout << "  ";
	}
	for (int y = ioGameBoard.mGameBoardPosY + 1; y < gbpy + GameBoard::mGbHeight + 1; ++y) {
		SetCursorPos(ioGameBoard.mGameBoardPosX, y);
		cout << "  ";
		SetCursorPos(ioGameBoard.mGameBoardPosX + (GameBoard::mGbWidth + 1) * 2, y);
		cout << "  ";
	}
}

//ゲームボード内部の描画
void DrawEngine::DrawStage(GameBoard inGameBoard) {
	for (int y = 1; y <= GameBoard::mGbHeight; ++y) {
		SetCursorPos(inGameBoard.GetGameBoardPosX() + 2, y + inGameBoard.GetGameBoardPosY());
		for (int x = 1; x <= GameBoard::mGbWidth; ++x) {
			int Value = inGameBoard.GetGameBoardValue(x, y);
			//空ではないブロックは固定化→
			if(Value !=GameBoard::Value::empty){
				int Color = TetriminoTypeToColor(Value);

				//テトリミノの色を設定
				SetColor(Color, Color);
			}
			else
				SetColor((int)Color::Gray, (int)Color::Black);
			cout << "  ";
		}
	}
}

//テトリミノの描画
void DrawEngine::DrawTetrimino(GameBoard ioGameBoard, const BlockPiece& ioBlockPiece)
{
	//GUIアプリとして移植する際にテトリミノを形状と色を持った構造体として定義することで描画を行う関数側から指定する必要をなくす
	int tetrimino_color = TetriminoTypeToColor(ioBlockPiece.mTetriminoType + 1);//Typeの範囲を0~6ではなく、1~7に、

	//テトリミノの色を設定
	SetColor(static_cast<int>(tetrimino_color), static_cast<int>(tetrimino_color));


	for (int i = 0; i < gTetriminoWidth; ++i) {
		int blockpiece_posy = ioBlockPiece.mTetriminoPosY + i;
		
		if (blockpiece_posy < 0 || blockpiece_posy >= GameBoard::mGbHeight) continue;
			for (int k = 0; k < gTetriminoWidth; ++k) {
				int blockpiece_posx = ioBlockPiece.mTetriminoPosX + k;

				if (blockpiece_posx < 0 || blockpiece_posx >= GameBoard::mGbWidth) continue;
					
				if (ioBlockPiece.mTetrimino[k][i]) {
					SetCursorPos(ioGameBoard.GetGameBoardPosX() + (blockpiece_posx + 1) * 2, 
								ioGameBoard.GetGameBoardPosY() + blockpiece_posy + 1);
					cout << "  ";
			}
		}
	}
}

//テトリミノの形状から色を設定する
int DrawEngine::TetriminoTypeToColor(int inTetriminoType) {
	static int tetrimino_color;


	switch (inTetriminoType)
	{
		case static_cast<int>(BlockPiece::TetrimnoType::TypeA) :
			tetrimino_color = static_cast<int>(Color::Cyan);
			break;
		case static_cast<int>(BlockPiece::TetrimnoType::TypeB) :
			tetrimino_color = static_cast<int>(Color::Yellow);
			break;
		case static_cast<int>(BlockPiece::TetrimnoType::TypeC) :
			tetrimino_color = static_cast<int>(Color::Red);
			break;
		case static_cast<int>(BlockPiece::TetrimnoType::TypeD) :
			tetrimino_color = static_cast<int>(Color::Green);
			break;
		case static_cast<int>(BlockPiece::TetrimnoType::TypeE) :
			tetrimino_color = static_cast<int>(Color::Blue);
			break;
		case static_cast<int>(BlockPiece::TetrimnoType::TypeF) :
			tetrimino_color = static_cast<int>(Color::DarkRed);
			break;
		case static_cast<int>(BlockPiece::TetrimnoType::TypeG) :
			tetrimino_color = static_cast<int>(Color::Violet);
			break;
		default:
			break;
	}

	return tetrimino_color;
}

//コンソール上の描画位置を設定
void DrawEngine::SetCursorPos(int inConsolePosX, int inConsolePosY) {
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = inConsolePosX;
	pos.Y = inConsolePosY;
	SetConsoleCursorPosition(hCons, pos);
}


//スコア表示
void DrawEngine::DrawScore(ScoreManager inScore) {
	//スコア表示位置の設定
	int ScorePosX = (game_board.GetGameBoardPosX() + GameBoard::mGbWidth + 2) * 3 + 4;
	int ScorePosY = game_board.GetGameBoardPosY()+2;
	
	int score = inScore.GetScore();//スコア取得

	SetCursorPos(ScorePosX,ScorePosY);
	//スコアの色を設定
	SetColor(static_cast<int>(Color::Gray), static_cast<int>(Color::Black));
	
	cout << "Score:";
	cout.width(8);     
	cout << score;
}

//ルール表示
void DrawEngine::DrawHiScore() {
	//スコア表示位置の設定
	int RulePosX = (game_board.GetGameBoardPosX() + GameBoard::mGbWidth + 2) * 3 + 4;
	int RulePosY = game_board.GetGameBoardPosY();

	int hiscore = score.GetHighScore();//スコア取得

	SetCursorPos(RulePosX, RulePosY);
	//スコアの色を設定
	SetColor(static_cast<int>(Color::Gray), static_cast<int>(Color::Black));

	cout << "HiScore:";
	cout.width(6);
	cout << hiscore;
}

//デバック用テスト関数
void DrawEngine::DrawRotType() {
	//int RotPosX = (gb.GetmGameBoardPosX() + (GameBoard::mGbWidth + 2) * 3 + 4);
	//int RotePosY = gb.GetmGameBoardPosY() + 2;

	//int RotType = bp.GetRot();
	//SetCursorPos(RotPosX, RotePosY);
	//SetColor(static_cast<int>(Color::Gray), static_cast<int>(Color::Black));
	//cout << "RotType:";
	//cout.width(8);
	//cout << RotType;
}

//前景色と背景色を設定
void DrawEngine::SetColor(int inForeGroundColor, int inBackGroundColor) {
	HANDLE h_cons = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD attr = 0;
	if (inForeGroundColor & static_cast<int>(Mask::Intensity))
		attr |= FOREGROUND_INTENSITY;
	if (inForeGroundColor & static_cast<int>(Mask::RedMask))
		attr |= FOREGROUND_RED;
	if (inForeGroundColor & static_cast<int>(Mask::GreenMask))
		attr |= FOREGROUND_GREEN;
	if (inForeGroundColor & static_cast<int>(Mask::BlueMask))
		attr |= FOREGROUND_BLUE;

	if (inBackGroundColor & static_cast<int>(Mask::Intensity))
		attr |= BACKGROUND_INTENSITY;
	if (inBackGroundColor & static_cast<int>(Mask::RedMask))
		attr |= BACKGROUND_RED;
	if (inBackGroundColor & static_cast<int>(Mask::GreenMask))
		attr |= BACKGROUND_GREEN;
	if (inBackGroundColor & static_cast<int>(Mask::BlueMask))
		attr |= BACKGROUND_BLUE;
	SetConsoleTextAttribute(h_cons, attr);
}