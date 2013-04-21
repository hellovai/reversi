#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib> 

#include "main.h"
#include "game.h"
#include "agent.h"

using namespace std;

Move getHuman();

int main (int argc, char* argv[]) {
	srand(time(NULL));
	int boardsize = 8;
	bool c1 = false;
	bool c2 = false;
	bool dolog = false;
	bool debug = false;

	//read arguments and define variable based on them
	for(int i=1; i<argc; i++) {
		string temp = argv[i];
		if(temp.compare("-b") == 0) {
			if(++i >= argc) usage_err(temp);
			boardsize = atoi(argv[i]);
		} else if (temp.compare("-c1") == 0) {
			c1 = true;
		} else if (temp.compare("-c2") == 0) {
			c2 = true;
		} else if (temp.compare("-log") == 0) {
			dolog = true;
		} else if (temp.compare("-debug") == 0) {
			debug = true;
		}  else
			usage_err(temp);
	}

	boardsize = max(4, boardsize);
	boardsize = min(boardsize, 26);

	Game* game = new Game(boardsize);
	Agent* agent1 = new Agent(game);
	agent1->setDebug(debug);
	Agent* agent2 = new Agent(game);
	agent2->setDebug(debug);
	game->ValidMove();

	//create game
	while(!game->IsFinished()) {
		game->Print();
		//play game
		Move move;
		
		// alternate moves
		if(game->turn() == 1)
		 	if(c1) move = agent1->MakeMove();
		 	else move = getHuman();
		else
			if(c2) move = agent2->MakeMove();
			else move = getHuman();
		while(!game->isValid(move)) {
			cout<<"Sorry, ("<<move.x<<" , "<<move.y<<") is invalid!\n";
			move = getHuman();
		}
		game->MakeMove(move);
	}

	//display result
	return 0;
}

void usage_err(string var) {
	cout<<"Usage: ./reversi "<<endl;
	exit(0);
}

Move getHuman() {
	Move move;
	cout<<"Enter Move: ";
	int a, b;
	// a = getchar();
	// b = getchar();
	cin>>move.x>>move.y;
	// move.x = (int) a - 65;
	// move.y = (int) b - 30;
	cout<<"Attempting: "<<move.x<<", "<<move.y<<endl;
	return move;
}