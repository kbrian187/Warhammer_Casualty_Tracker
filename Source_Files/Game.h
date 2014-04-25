/*
* Game.h
*
*  Created on: Apr 13, 2014
*      Author: Brian
*/

#include<string>
#include<iostream>
#include"Unit.h"
#include"Army.h"
#include"Model.h"
using namespace std;
#ifndef GAME_H_
#define GAME_H_

class Game
{
public:
	Game(Army*, Army*);
	~Game();
	string unitCasualties(Army*, Army*);
	bool unitDead(int);
	string turn(int);
	string displayGameResult();
	string unitReport(Army*, Army*);


	//variables
	Army FirstArmy;
	Army SecondArmy;
	int turnNum;
	string gameResult;
};
#endif