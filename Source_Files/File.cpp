/*
* File.cpp
*
*  Created on: Apr 13, 2014
*      Author: Brian
*/



#include<string>
#include<fstream>
#include<iostream>
#include<memory>
#include<iomanip>
#include"Army.h"
#include"Model.h"
#include"File.h"
#include"Unit.h"

//constructor for File object
File::File() : path("C:\\Users\\Brian\\Documents\\Visual Studio 2013\\Projects\\Warhammer Casualty Tracker\\Warhammer Casualty Tracker\\")
{
	//blank
}

File::~File()
{
	//blank
}

//saves the game result in a single string written to a .txt file
void File::saveGame(string result, string armyName1, string  armyName2)
{
	fstream saveFile(path + armyName1 + "_vs_" + armyName2 + ".txt", ios::out);
	if (!saveFile)
	{
		cerr << "File could not be opened" << endl;
		exit(1);
	}
	else
	{
		saveFile << result;
	}
	saveFile.close();
}




void File::saveArmy(Army* army)
{
	fstream saveFile(path + army->armyName + ".txt", ios::out);
	int nullNum = 0;
	if (!saveFile)
	{
		cerr << "File could not be opened" << endl;
		exit(1);
	}
	else
	{
		saveFile << army->armyName << ' ' << army->pointTotal << endl;//outputs army info at the top of the file

		if (army->pUFirst != nullptr)
		{
			Unit* pIterator = army->pUFirst;
			while (pIterator->pUNext != nullptr)//this loops through the units and saves them all line by line
			{
				saveFile << pIterator->unitID << ' ' << pIterator->pointValue << ' ' << pIterator->uName << ' ' << pIterator->type << endl;
				if (pIterator->pMFirst != nullptr)
				{
					Model* pMIterator = pIterator->pMFirst;
					for (int ii = 0; ii < pIterator->unitSize; ii++)//this loop goes through all of the models in a unit, saving them with 0s at the beginning for easy loading later. Prints all models before moving on to the next unit
					{
						saveFile << nullNum << ' ' << nullNum << ' ' << pMIterator->name << ' ' << pMIterator->description << endl;
						pMIterator = pMIterator->pMNext;
					}
				}
				pIterator = pIterator->pUNext;
			}
			
			saveFile << pIterator->unitID << ' ' << pIterator->pointValue << ' ' << pIterator->uName << ' ' << pIterator->type << endl;
			if (pIterator->pMFirst != nullptr)
			{
				Model* pMIterator = pIterator->pMFirst;
				for (int ii = 0; ii < pIterator->unitSize; ii++)
				{
					saveFile << nullNum << ' ' << nullNum << ' ' << pMIterator->name << ' ' << pMIterator->description << endl;
					pMIterator = pMIterator->pMNext;
				}
			}
		}
	}
	saveFile.close();
}

//function to check the formatting ofa  line to determine whether or not its a model
bool File::isModel(int id)
{
	if (id == 0)
		return true;
	else return false;
}


Army* File::loadArmy(string fileName)
{
	fstream loadFile(path + fileName, ios::in);
	if (!loadFile)
	{
		cerr << "File could not be opened";
		exit(1);
	}
	else
	{
		string tempArmyName;
		string tempName;
		string tempDesc;
		int tempUnitValue;
		int tempUnitID;

		loadFile >> tempArmyName >> tempUnitValue;//loads the army info header at the top of the file

		Army* newArmy = new Army(tempArmyName);//creates an army based on the above info
		while (!loadFile.eof())//loop to read the file line by line, then create either a unit or a model based on the results of the isModel() check
		{
			loadFile >> tempUnitID >> tempUnitValue >> tempName >> tempDesc;
			if (!isModel(tempUnitID))
			{
				newArmy->addUnit(tempName, tempDesc, tempUnitValue, tempUnitID);
			}
			else
			{
				Unit* pIterator = newArmy->pUFirst;
				while (pIterator->pUNext != nullptr)
				{
					pIterator = pIterator->pUNext;
				}
				pIterator->addUnique(tempName, tempDesc);
			}
		}
		loadFile.close();
		return newArmy;
	}
}