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

Agent::Agent(Game* meh) {
	game = meh;
	debug = false;
	type = 0;
}

Move Agent::MakeMove() {
	if(debug) cout<<"Starting Move"<<endl;
	UpdateMoveList();
	switch(type) {
		case 0:
		default:
			return Random();
	}
}

//Private Functions
Move Agent::Random() {
	return moveList[rand() % moveList.size()];
}

void Agent::UpdateMoveList() {
	moveList = game->ValidMove();
}