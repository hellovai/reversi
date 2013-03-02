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
	//starting positions for 1 and 2
	board[boardsize/2 - 1][boardsize/2] = 1;
	board[boardsize/2][boardsize/2 - 1] = 1;
	board[boardsize/2 - 1][boardsize/2 - 1] = 2;
	board[boardsize/2][boardsize/2] = 2;

	moves = 0;
	my_status = false;
	current_player = 1;
	
	perimeter.clear();
	Move temp;
	//row 1
	temp.y = boardsize/2 - 2;
	temp.x = boardsize/2 - 2;
	perimeter.push_back(temp);
	temp.x = boardsize/2 - 1;
	perimeter.push_back(temp);
	temp.x = boardsize/2 ;
	perimeter.push_back(temp);
	temp.x = boardsize/2 + 1;
	perimeter.push_back(temp);
	//row 2
	temp.y = boardsize/2 - 1;
	temp.x = boardsize/2 - 2;
	perimeter.push_back(temp);
	temp.x = boardsize/2 + 1;
	perimeter.push_back(temp);
	//row 3
	temp.y = boardsize/2;
	temp.x = boardsize/2 - 2;
	perimeter.push_back(temp);
	temp.x = boardsize/2 + 1;
	perimeter.push_back(temp);
	//row 4
	temp.y = boardsize/2 + 1;
	temp.x = boardsize/2 - 2;
	perimeter.push_back(temp);
	temp.x = boardsize/2 - 1;
	perimeter.push_back(temp);
	temp.x = boardsize/2 ;
	perimeter.push_back(temp);
	temp.x = boardsize/2 + 1;
	perimeter.push_back(temp);
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
	if(hint)
		ValidMove(true);
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
	vector<Move> moveList;
	for(int i=0; i<(int)perimeter.size(); i++) {
		bool val = false;
		int j = 0;
		while(j < 10 ) {
			val = Recurse(perimeter[i], j, false);
			if(val)
				break;
			// cout<<"This move "<<perimeter [i].x<<", "<<perimeter[i].y<<" is "<<(val ? "true" : "false")<<" for "<<j<<endl;
			j++;
			if(j == 4) j++;
		}
		// cout<<"This move "<<perimeter [i].x<<", "<<perimeter[i].y<<" was for: "<<j<<endl;
		if(val)
			moveList.push_back(perimeter[i]);
		board[perimeter[i].x][perimeter[i].y] = 0;
	}
	return moveList;
}

vector<Move> Game::ValidMove(bool show){
	vector<Move> moveList;
	for(int i=0; i<(int)perimeter.size(); i++) {
		bool val = false;
		int j = 0;
		while(j < 10 ) {
			val = Recurse(perimeter[i], j, false);
			if(val)
				break;
			// cout<<"This move "<<perimeter [i].x<<", "<<perimeter[i].y<<" is "<<(val ? "true" : "false")<<" for "<<j<<endl;
			j++;
			if(j == 4) j++;
		}
		// cout<<"This move "<<perimeter [i].x<<", "<<perimeter[i].y<<" was for: "<<j<<endl;
		if(val) {
			board[perimeter[i].x][perimeter[i].y] = -1;
			moveList.push_back(perimeter[i]);
		} else {
			board[perimeter[i].x][perimeter[i].y] = 0;
		}
	}
	return moveList;
}

void Game::MakeMove(Move move){

}

int Game::WhoWon(){
	
}

bool Game::isValid(Move check) {
	vector<Move> valid = ValidMove();
	for(int i=0; i<(int)valid.size(); i++)
		if(valid[i].x == check.x && valid[i].y == check.y)
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
			return "\u2736";
		case -2:
			return "-";
		default: return " ";
	}
}

bool Game::Recurse(Move move, int dir, bool found) {
	switch(dir) {
		case 0:
			move.x-=1;
			move.y-=1;
			break;
		case 1:
			move.y-=1;
			break;
		case 2:
			move.x+=1;
			move.y-=1;
			break;
		case 3:
			move.x-=1;
			break;
		case 5:
			move.x+=1;
			break;
		case 6:
			move.x-=1;
			move.y+=1;
			break;
		case 7:
			move.y+=1;
			break;
		case 8:
			move.x+=1;
			move.y+=1;
			break;
	}
	if(move.x < 0 || move.x >= boardsize || move.y < 0 || move.y >= boardsize) {
		cout<<"overextended..."<<endl;
		return false;
	} else if(board[move.x][move.y] == current_player)
		return found;
	else if(board[move.x][move.y] == (current_player == 1 ? 2 : 1) )
		return Recurse(move, dir, true);
	else
		return false;
}