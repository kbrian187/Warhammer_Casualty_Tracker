/*
* File.h
*
*  Created on: Apr 13, 2014
*      Author: Brian
*/


#ifndef FILE_H_
#define FILE_H_
#include<string>
#include<fstream>
#include<iostream>
#include<iomanip>
#include"Army.h"
#include"Model.h"
#include"Unit.h"

class File
{
public:
	File();
	~File();
	void saveGame(string, string, string);
	void saveArmy(Army*);
	Army* loadArmy(string);
	bool isModel(int);
	string path;
};

#endif /* FILE_H_ */
