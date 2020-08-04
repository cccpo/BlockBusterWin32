#pragma once
#include <random>

#include "TetriminoWin32.h"


class TetriminoSet
{

public:
	enum {
		Rotate_Pattern = 4, Num_Tetriminos = 7
	};

	TetriminoSet();
	~TetriminoSet();

	TetriminoWin32* GetTetrimino(int id, int rotation = 0);

	inline TetriminoWin32* GetRandomTetrimino() {return GetTetrimino(rand() % Num_Tetriminos, rand() % Rotate_Pattern);
	};


protected:

	TetriminoWin32* tetriminos[Num_Tetriminos][Rotate_Pattern];

	void MakeTetriminoRotateAllPattern();
	void RotateTetrimino(POINT* apt, int inNumPoints = 4);//ƒeƒgƒŠƒ~ƒm‚ð‰ñ“]‚³‚¹‚é
};