#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

#include "main.h"
#include "game.h"
#include "agent.h"

using namespace std;


int main(int argc, char **argv ) {
	int boardsize = 8;
	bool c1 = false;
	bool c2 = false;
	bool dolog = false;

	//read arguments and define variable based on them
	for(int i=1; i<argc; i++) {
		string temp = argv[i];
		if(temp.compare("-b") == 0) {
			boardsize = atoi(argv[++i]);
		} else if (temp.compare("-c1") == 0) {
			c1 = true;
		} else if (temp.compare("-c2") == 0) {
			c2 = true;
		} else if (temp.compare("-log") == 0) {
			dolog = true;
		} else
			usage_err(temp);
	}

	//create game
	while(!game->finish()) {
		//play game
		Move move;
		
		//alternate moves
		if(game->turn() == 1)
			if(c1) move = agent1->move();
			else move = getHuman();
		else
			if(c2) move = agent2->move();
			else move = getHuman();

	}

	//display result
	return 0;
}

void usage_err(string var) {
	cout<<"Usage: ./reversi "<<endl;
	exit(0);
}