/*
 * Unit.h
 *
 *  Created on: Apr 13, 2014
 *      Author: Brian
 */

#ifndef UNIT_H_
#define UNIT_H_

#include<string>
#include<iostream>
#include"Model.h"

class Unit
{
public:
	Unit();
	Unit(string, string, int, int);
	~Unit();
	void addModel(string, string);
	void addUnique(string, string);
	void addStandard(string, string, int);
	void deleteModel();
	void selectType();
	void setName();
	void setPointValue();
	void displayUnit();
	int getUnitSize();
	string getType();
	string getName();
	int getPointValue();
	void printUnit();
	Unit* pUNext;

	int pointValue;
	string type, uName;
	Model* pMFirst;
	int unitSize;
	int unitID;
	int casInflicted;
	int casSustained;


};




#endif /* UNIT_H_ */
