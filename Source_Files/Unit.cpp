/*
 * Unit.cpp
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

Unit::Unit(string newName, string newType, int pv, int id) : pMFirst(nullptr), unitSize(0), pUNext(nullptr), uName(newName), type(newType), pointValue(pv), unitID(id), casInflicted(0), casSustained(0)
	{
		//blank
	}

	
	//constructor requiring user input. Intended for use w/ a menu system
Unit::Unit() : pMFirst(nullptr), unitSize(0), pUNext(nullptr), casInflicted(0), casSustained(0)
	{
		selectType();
		cout << "\nEnter point value: \n";
		cin >> pointValue;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		bool flag = true;
		if ( ! cin.fail())
			flag = false;
		else while(flag) //checks to make sure that the point value entered can be converted to int type
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nThe point value must be an integer, please try again: ";
			cin >> pointValue;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if ( ! cin.fail())
			flag = false;
		}
		cout << "Enter the unit name: ";
		cin >> uName;
	}


	Unit::~Unit()
	{
		//intentionally blank
	}

	
	//function to add models to a unit. Prompt for model name string handled in advance of calling this function by the caller
	void Unit::addModel(string paramName, string paramDesc)
	{
		int typeSelector = 0;
		enum typeSelector {UNIQUE = 1, STANDARD};
		cout << "\nSelect model type to add:\n1. Unique Model\n2. Standard Model\n";
		cin >> typeSelector;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch(typeSelector)
		{
		case UNIQUE:
			addUnique(paramName, paramDesc);
			break;
		case STANDARD:
			int totalNumber;
			cout << "\nHow many of this model?\n";
			cin >> totalNumber;
			addStandard(paramName, paramDesc, totalNumber);
			break;
		default:
			cout << "\nInvalid Selection\n";
			break;
		}
	}

	//function for adding a single model to the end  of the linked list
	void Unit::addUnique(string paramName, string desc)
	{

		Model* pNewModel = new Model(paramName, desc);
		if(pMFirst == nullptr) //
		{
			pMFirst = pNewModel;
		}
		else
		{
			Model* pIterator = pMFirst;
			while(pIterator->pMNext != nullptr)
			{
				pIterator = pIterator->pMNext;
			}
			pIterator->pMNext = pNewModel;
		}
		unitSize++;
	}

	//function for adding multiple models to the end of a unit's linked list. Simply calls addUnique multiple times
	void Unit::addStandard(string paramName, string paramDesc, int number)
	{
		int totalNumber = number;
		for(int i = 0; i < totalNumber; i++)
		{
			addUnique(paramName, paramDesc);
		}

	}

	//function that assigns a type to a unit
	void Unit::selectType()
	{
		enum typeSelector{HQ = 1, ELITES, TROOPS, FAST_ATTACK, HEAVY};
		int typeSelector = 0;
		cout << "\nSelect Unit Type:\n1. HQ\n2. Elites\n3. Troops\n4. Fast Attack\n5. Heavy\n";
		while(typeSelector != 1 && typeSelector != 2 && typeSelector != 3 && typeSelector != 4 && typeSelector != 5)
		{
			cin >> typeSelector;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			switch(typeSelector)
			{
			case HQ:
				type = "HQ";
				break;
			case ELITES:
				type = "Elites";
				break;
			case TROOPS:
				type = "Troops";
				break;
			case FAST_ATTACK:
				type = "Fast Attack";
				break;
			case HEAVY:
				type = "Heavy";
				break;
			}
		}

		
	//unit size getter function
	int Unit::getUnitSize()
	{
		return unitSize;
	}

	//standard getter function
	string Unit::getType()
	{
		return type;
	}
	//standard getter function
	string Unit::getName()
	{
		return uName;
	}
	//standard getter function
	int Unit::getPointValue()
	{
		return pointValue;
	}

	
	//function to print the models contained with a unit, if they exist
	void Unit::printUnit()
	{
		if(unitSize > 0)
		{
			Model* pIterator = pMFirst;
			while(pIterator!= nullptr)
			{
				cout << pIterator->name << endl;
				pIterator = pIterator->pMNext;
			}
		}
		else
		{
			cout << "\nUnit is empty\n";
		}
	}

	
	//standard set function
	void Unit::setName()
	{
		cout << "Enter Unit Name: ";
		cin >> uName;
	}

	
	//function used for changing an already set point value
	void Unit::setPointValue()
	{
		cout << "Enter Point Value: ";
		int tempPV;
		cin >> tempPV;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		bool flag = true;
		if ( ! cin.fail())
			flag = false;
		else while (flag) //checks to make sure that the point value entered can be converted to int type
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nThe point value be an integer, please try again: ";
			cin >> tempPV;
			if ( ! cin.fail())
			{
				flag = false;
				cin.clear();
			}
		}
		pointValue = tempPV;
	}

	void Unit::displayUnit()
	
	//if the unit contains models, this prints them out to the screen
	{
		if (pMFirst == nullptr)
		{
			cout << "Unit is empty" << endl;
		}
		else
		{
			Model* pTemp = pMFirst;
			cout << endl << left << uName << endl;
			cout << setw(25) << left << "Model Name" << endl;
			while (pTemp->pMNext != nullptr)
			{
				cout << setw(25) << left << pTemp->name << endl;
				pTemp = pTemp->pMNext;
			}
			cout << setw(25) << left << pTemp->name << endl << endl;
		}
	}