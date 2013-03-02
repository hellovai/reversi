#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

#include "main.h"
#include "game.h"

using namespace std;

//public functions
//1 is white, 2 is black
Game::Game(int size){
	boardsize = size;
	board = new int *[boardsize];
	for(int i=0;i<boardsize;i++)
		board[i] = new int[boardsize];
	Reset();
}

void Game::Reset(){
	for(int i=0;i<boardsize;i++)
		for(int j=0;j<boardsize;j++)
			board[i][j] = 0;
	board[boardsize/2 - 1][boardsize/2 - 1] = 1;
	board[boardsize/2][boardsize/2] = 1;
	board[boardsize/2 - 1][boardsize/2] = 2;
	board[boardsize/2][boardsize/2 - 1] = 2;
	moves = 0;
	my_status = false;
	current_player = 1;
}

void Game::Print(){
	for(int i=0;i<boardsize;i++)
	{
		for(int j=0;j<boardsize;j++)
			wcout << '|' << GetChar(board[i][j]);	
		cout << '|' << endl;
		for(int j=0;j<boardsize;j++)
			cout << " -";	
		cout<<endl;
	}
}

vector<Move> Game::ValidMove(){

}

void Game::MakeMove(){

}

int Game::WhoWon(){
	
}

//private functions
char Game::GetChar(int num){
	switch(num)
	{
		case 1: return '□';
		case 2: return '■';
		default: return ' ';
	}
}