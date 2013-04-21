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
			if(board[i][j] != 0)
				cout << '|' << GetCharPlayer(board[i][j]);	
			else
				cout << '|' << GetCharPlayer(board[i][j]);
			cout << '|' << endl;
	}
}

void Game::Print(bool hint) {
	if(hint) {
		vector<Move> moveList = ValidMove();
		for(int i=0; i<(int) moveList.size(); i++)
			board[moveList[i].x][moveList[i].y] = 3*current_player;
	}
	Print();
}

vector<Move> Game::ValidMove(){
	vector<Move> moveList;
	for(int i=0; i<(int)perimeter.size(); i++) {
		bool val = false;
		int j = 0;
		while(j < 9 ) {
			val = Recurse(perimeter[i], j, false);
			if(val)
				break;
			j++;
			if(j == 4) j++;
		}
		if(val)
			moveList.push_back(perimeter[i]);
		board[perimeter[i].x][perimeter[i].y] = 0;
	}
	return moveList;
}

void Game::MakeMove ( Move move ) {
	board[move.x][move.y] = current_player;
	//account for swapping middle pieces
	for(int i=0; i<9; i++)
		if(MoveFlip(move, (i == 4 ? 5 : i), false))
			cout<<"We flipped for direction: "<<i<<endl;
		else
			cout<<"No flip for dirction: "<<i<<endl;
	//fix the perimeter
	vector<Move> possible ( 9, move);
	possible[0].x -=1;
	possible[0].y -=1;
	possible[1].y -=1;
	possible[2].x +=1;
	possible[2].y -=1;

	possible[3].x -=1;
	possible[5].x +=1;

	possible[6].x -=1;
	possible[6].y +=1;
	possible[7].y +=1;
	possible[8].x +=1;
	possible[8].y +=1;

	vector<bool> truth (9, true);
	truth[4] = false;

	//delete current move from perimeter
	for(int i=0; i<(int) perimeter.size(); i++)
		if(perimeter[i].x == possible[4].x && perimeter[i].y == possible[4].y) {
			perimeter.erase(perimeter.begin()+i);
			i--;
		} else
			for(int j=0; j<9; (++j == 4 ? ++j : j) )
				if (perimeter[i].x == possible[j].x && perimeter[i].y == possible[j].y)
					truth[j] = false;
	
	for(int i=0; i<9; i++)
		if(truth[i])
			perimeter.push_back(possible[i]);

	current_player = OtherPlayer();
}

int Game::WhoWon() {
	return 1;
}

bool Game::isValid(Move check) {
	vector<Move> valid = ValidMove();
	for(int i=0; i<(int)valid.size(); i++)
		if(valid[i].x == check.x && valid[i].y == check.y)
			return true;
	return false;
}

//private functions
string Game::GetCharPlayer(int num){
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
	move = updateMove(move, dir);
	if(move.x < 0 || move.x >= boardsize || move.y < 0 || move.y >= boardsize)
		return false;
	else if(board[move.x][move.y] == current_player)
		return found;
	else if(board[move.x][move.y] == OtherPlayer() )
		return Recurse(move, dir, true);
	else
		return false;
}

bool Game::MoveFlip(Move move, int dir, bool found) {
	// cout<<"Flipping: "<<move.x<<", "<<move.y<<"::Dirction: "<<dir<<" With: "<<found<<endl;
	// Print();
	move = updateMove(move, dir);
	bool val;
	if(move.x < 0 || move.x >= boardsize || move.y < 0 || move.y >= boardsize)
		val = false;
	else if(board[move.x][move.y] == current_player)
		return found;
	else if(board[move.x][move.y] == OtherPlayer() )
		val = MoveFlip(move, dir, true);
	else
		val = false;
	if(val) {
		board[move.x][move.y] = current_player;
		// cout<<"\tShould Have changed: "<<move.x<<", "<<move.y<<endl;
	}
	return val;
}

Move Game::updateMove(Move move, int dir) {
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
	return move;
}

int Game::OtherPlayer() {
	return (current_player == 1 ? 2 : 1);
}