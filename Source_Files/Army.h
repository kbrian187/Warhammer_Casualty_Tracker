/*
 * Army.h
 *
 *  Created on: Apr 13, 2014
 *      Author: Brian
 */


#ifndef ARMY_H_
#define ARMY_H_
#include<string>
#include"Unit.h"

class Army
{
public:
	 Army(string);
	 Army();
	~Army();
	void addUnit();
	void addUnit(string,string,int,int);
	int getArmySize();
	string getArmyName();
	void displayArmy();
	Unit* getLast();
	Unit* pUFirst;
	string armyName;
	int armySize;
	Unit* pULast;
	int pointTotal;
};

#endif /* ARMY_H_ */
