/*
 * Army.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: Brian
 */

#include<string>
#include<iostream>
#include<iomanip>
#include"Army.h"
#include"Unit.h"
#include"Model.h"
using namespace std;

Army::Army(string inputName) : pULast(nullptr)
	{
		pUFirst = nullptr;
		armyName = inputName;
		armySize = 0;
	}

Army::Army() : pULast(nullptr)
{
	pUFirst = nullptr;
	armySize = 0;
}

	Army::~Army()
	{
		//intentionally blank
	}
	void Army::addUnit()
	{
		Unit* pNewUnit = new Unit();
		if (pUFirst == nullptr)
		{
			pUFirst = pNewUnit;
			pNewUnit->unitID = armySize + 1;
		}
		else
		{
			Unit* pIterator = pUFirst;
			while (pIterator->pUNext != nullptr)
			{
				pIterator = pIterator->pUNext;
			}
			pIterator->pUNext = pNewUnit;
			pNewUnit->unitID = armySize + 1;
			pULast = pNewUnit;
		}
		armySize++;
		pointTotal = pNewUnit->pointValue + pointTotal;
	}

	void Army::addUnit(string newName, string newType, int pv, int id)
	{
		Unit* pNewUnit = new Unit(newName, newType, pv, id);
		if (pUFirst == nullptr)
		{
			pUFirst = pNewUnit;
		}
		else
		{
			Unit* pIterator = pUFirst;
			while (pIterator->pUNext != nullptr)
			{
				pIterator = pIterator->pUNext;
			}
			pIterator->pUNext = pNewUnit;
			pULast = pNewUnit;
		}
		pointTotal = pNewUnit->pointValue + pointTotal;
		armySize = armySize++;
	}
	
	string Army::getArmyName()
	{
		return armyName;
	}

	int Army::getArmySize()
	{
		return armySize;
	}

	Unit* Army::getLast()
	{
		return pULast;
	}

	void Army::displayArmy()
	{
		if (pUFirst == nullptr)
		{
			cout << "Army list is empty" << endl;
		}
		else
		{
			Unit* pTemp = pUFirst;
			cout << endl << setw(50) << left << armyName << setw(8) << right << pointTotal << setw(4) << right << " pts" << endl;
			cout << setw(25) << left << "Unit Name" << setw(15) << left << "Unit Type" << setw(8) << right << "Unit ID" << setw(14) << right << "Point Value" << endl;
			while (pTemp->pUNext != nullptr)
			{
				cout << setw(25) << left << pTemp->uName << setw(15) << left << pTemp->type << setw(8) << right << pTemp->unitID << setw(14) << right << pTemp->pointValue << endl;
				pTemp = pTemp->pUNext;
			}
			cout << setw(25) << left << pTemp->uName << setw(15) << left << pTemp->type << setw(8) << right << pTemp->unitID << setw(14) << right << pTemp->pointValue << endl << endl;
		}
	}