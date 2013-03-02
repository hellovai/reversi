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
	board[boardsize/2 - 1][boardsize/2] = 1;
	board[boardsize/2][boardsize/2 - 1] = 1;
	board[boardsize/2 - 1][boardsize/2 - 1] = 2;
	board[boardsize/2][boardsize/2] = 2;
	moves = 0;
	my_status = false;
	current_player = 1;
}

void Game::Print(){
	cout<<'\t';
	for(int j=0;j<boardsize;j++)
		cout << ' ' << (char) (j+65);
		cout<<endl;
	for(int i=0;i<boardsize;i++)
	{
		cout<<i<<'\t';
		for(int j=0;j<boardsize;j++)
			cout << '|' << GetChar(board[i][j]);	
			cout << '|' << endl;
	}
}

void Game::Print(bool hint) {
	cout<<'\t';
	for(int j=0;j<boardsize;j++)
		cout << ' ' << (char) (j+65);
		cout<<endl;
	for(int i=0;i<boardsize;i++)
	{
		cout<<i<<'\t';
		for(int j=0;j<boardsize;j++) {
			Move temp;
			temp.x = i;
			temp.y = j;
			if(isValid(temp))
				cout << '|' << GetChar(-1);
			else 
				cout << '|' << GetChar(board[i][j]);
		}	
			cout << '|' << endl;
	}
}

vector<Move> Game::ValidMove(){

}

void Game::MakeMove(Move move){

}

int Game::WhoWon(){
	
}

bool Game::isValid(Move check) {
	vector<Move> valid = ValidMove();
	for(int i=0; i<valid.size(); i++)
		if(valid[i] == check)
			return true;
	return false;
}

//private functions
string Game::GetChar(int num){
	switch(num)
	{
		case 1: return "\u25A0";
		case 2: return "\u25A1";
		case -1:
			return "\u2742";
		default: return " ";
	}
}