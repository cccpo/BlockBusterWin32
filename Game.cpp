#include <iostream>
#include <Windows.h>
#include <thread>
#include <chrono>
#include <memory>
#include <conio.h>
#include <chrono>

#include "Game.h"

#include "board/ScoreManager.h"
#include "board/GameBoard.h"
#include "board/DrawEngine.h"
#include "board/BlockPiece.h"
#include "Data/Data.h"
#include "Input/KeyInput.h"

using std::cout;
using std::endl;


//game
void gPlayGame(DrawEngine& ioDrawEngine) {
	
	GameBoard game_board(1,2);

	BlockPiece block_piece;
	KeyInput key_input;
	ScoreManager score;
	Data data;

	int hi_score = data.HiScoreLoad();//ハイスコアを取得
	score.SetHighScore(hi_score);//ハイスコアをセットする

	game_board.InitGameBoard();//ゲームボード初期化

	score.SetScore(0);//スコアの初期化

	block_piece.AddTertimino(game_board);//テトリミノの追加

	int block_piece_posx = block_piece.GetTetriminoPosX(game_board);//テトリミノx座標設定
	int block_piece_posy = block_piece.GetTetriminoPosY(game_board);//テトリミノy座標設定

	ioDrawEngine.DefaultDrawBoard(game_board);//ゲームボード外枠の描画
	ioDrawEngine.DrawStage(game_board);//ゲームボード内部の描画

	ioDrawEngine.DrawScore(score);//スコア表示
	ioDrawEngine.DrawHiScore();//ハイスコア表示

	ioDrawEngine.DrawTetrimino(game_board,block_piece);//テトリミノの描画

	// Todo fix
	int mCurrentTime = 1;
	int ts = 0;

	int key = 0;
	int keyDown = 0;
	
	
	//テトリミノ生成時点で固定ブロックと接触するとループを抜ける
	 while (!block_piece.IsOverLaped(game_board)) {
	//for(int cnt =1;;++cnt){
			bool update = false;

			if (mCurrentTime % FallInterval == 0 || key == VK_DOWN){
				//テトリミノが落下完了した場合に以下の処理
				if (!block_piece.IsMoveDown(game_board)) {
					key = 0;
					int final_posx = block_piece.GetTetriminoPosX(game_board);
					int final_posy = block_piece.GetTetriminoPosY(game_board);
					block_piece.ChangeBlock(game_board);//ブロックの固定化
					block_piece.DeleteLine(game_board);//揃ったlineの消去
					ioDrawEngine.DrawScore(score);
					
					block_piece.AddTertimino(game_board);
					ioDrawEngine.DrawStage(game_board);//ゲームボード内部の描画(ToDo)
					ioDrawEngine.DrawTetrimino(game_board,block_piece);//テトリミノの描画
					block_piece_posx = block_piece.GetTetriminoPosX(game_board);//テトリミノx座標設定
					block_piece_posy = block_piece.GetTetriminoPosY(game_board);//テトリミノy座標設定
					
					//枠外に出てしまった場合終了
					if (block_piece.IsOverLaped(game_board))
						return;
					
					continue;
				}
				++block_piece_posy;     // 落下中テトリスをひとつ下に移動
				block_piece.SetTeriminoPosY(block_piece_posy);
				update = true;
			}

			if (mCurrentTime % MoveInterval == 0) {   
				//Move Left
				if (key == VK_LEFT) {
					if (block_piece.IsMoveLeft(game_board)) {
						--block_piece_posx;  
						block_piece.SetTeriminoPosX(block_piece_posx);
						update = true;
					}
					key = 0;
				}
				//Move Right
				else if (key == VK_RIGHT) {
					if (block_piece.IsMoveRight(game_board)) {
						++block_piece_posx;  
						block_piece.SetTeriminoPosX(block_piece_posx);
						update = true;
					}
					key = 0;
				}
			}

			//Rotate
			if (mCurrentTime % RotateInterval == 0) {       
				if (key == VK_UP) {
					int tx = block_piece.GetRot(game_board);

					if (++tx >= 4) {
						block_piece.SetRot(0);
						tx = 0;
					}
					block_piece.SetTertimino(game_board,block_piece.mTetriminoType, tx);
					if (block_piece.IsOverLaped(game_board)) {    
						block_piece.SetTertimino(game_board,block_piece.mTetriminoType, block_piece.GetRot(game_board));
					}
					else {
						block_piece.SetRot(tx);
						update = true;
					}
					key = 0;
				}
			}
			if (update) {
				ioDrawEngine.DrawStage(game_board);//ゲームボード内部の描画(ToDo)
				ioDrawEngine.DrawTetrimino(game_board,block_piece);
				
			}
			if (!keyDown) {     // キー押下を受け付けていない場合
				if (key_input.IsKeyPressed(VK_LEFT)) {
					key = keyDown = VK_LEFT;
				}
				else if (key_input.IsKeyPressed(VK_RIGHT)) {
					key = keyDown = VK_RIGHT;
				}
				else if (key_input.IsKeyPressed(VK_UP)) {
					key = keyDown = VK_UP;
				}
				else if (key_input.IsKeyPressed(VK_DOWN)) {
					key = keyDown = VK_DOWN;
				}
			}
			else {
				if (!key_input.IsKeyPressed(keyDown))// 押されたキーが離された
					keyDown = 0;
			}


			Sleep(10);
			//std::this_thread::sleep_for(std::chrono::seconds(1));
			++mCurrentTime;
		}


}

void draw_engine_win32(DrawEngine& de) {

}

//main
//int main() {
//	using namespace std;
//	chrono::system_clock::time_point start, end;
//
//	//ゲーム開始
//	DrawEngine de;
//	KeyInput ki;
//	ScoreManager sc;
//	Data d;
//
//	for (;;) {
//		start = chrono::system_clock::now();
//		
//		gPlayGame(de);
//
//
//		end = chrono::system_clock::now();
//
//		double time = static_cast<double>(chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0);
//		
//		//処理を変更する必要がある。
//		de.SetCursorPos(0, GameBoard::mGbHeight+5);
//		de.SetColor((int)DrawEngine::Color::Gray, (int)DrawEngine::Color::Black);
//		
//		//ハイスコア更新時の処理
//		if (sc.GetScore()>sc.GetHighScore()) {
//			std::cout << "HiScore!!" << sc.GetScore() <<endl;
//			d.HiScoreSave(sc.GetScore());
//		}
//		
//		std::cout << "GAME OVER. Replay? [Y/N] "<< endl;
//		
//		for (;;) {
//			if (ki.IsKeyPressed('N'))
//				return 0;
//			if (ki.IsKeyPressed('Y'))
//				break;
//			Sleep(LoopInterval);     // 10ミリ秒ウェイト
//		}
//
//		
//		de.SetCursorPos(0, GameBoard::mGbHeight + 5);//リプレイ時にゲームボードの位置を初期化
//		
//		for (int i = 0; i < 79; ++i) {
//			std::cout << ' ';
//		}
//
//	}
//}


// Key入力管理クラス
bool Game::KeyPress(int input_key) {
	if (input_key != VK_PAUSE)
	
		return false;

	switch (input_key)
	{
	case VK_UP:
		
		break;
	case VK_DOWN:
		
		break;
	case VK_LEFT:
		
		break;
	case VK_RIGHT:
		
		break;
	case VK_SPACE:
	
		break;
	case VK_PAUSE:
	
		break;
	case VK_RETURN:
		//restart();
	default:
		return false;
	}
	return true;
}
