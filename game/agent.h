//=================================
// include guard
#ifndef __AGENT_H_INCLUDED__
#define __AGENT_H_INCLUDED__
//=================================

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Agent {
	Game* game;
	bool debug;
	vector<Move> moveList;

	//type of agent
	int type;
	
	//types of moves
	Move Random();
	void UpdateMoveList(); 

	public:
		Agent( Game* );
		void Change_game ( Game* curr_game ) { game = curr_game; };
		void setDebug( bool debg ) { debug = debg; };
		void setType( int ty ) { type = ty; };
		
		Move MakeMove( );
};

//=================================
// end guard
#endif
//=================================