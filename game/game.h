//=================================
// include guard
#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__
//=================================

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Game{

	int boardsize;
	int ** board;
	int current_player;
	int moves;
	bool my_status;

	vector<Move> perimeter;

	string GetChar(int);
	bool Recurse(Move, int, bool);

public:
	Game(int);
	void Print();
	void Print(bool);
	void Reset();
	vector<Move> ValidMove();
	vector<Move> ValidMove(bool show);
	bool isValid(Move);
	void MakeMove(Move);
	int WhoWon();
	bool IsFinished(){return my_status;};

};

//=================================
// end guard
#endif
//=================================