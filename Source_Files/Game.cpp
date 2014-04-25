/*
* Game.cpp
*
*  Created on: Apr 13, 2014
*      Author: Brian
*/

#include<string>
#include<iostream>
#include<iomanip>
#include<fstream>
#include"Army.h"
#include"Unit.h"
#include"Model.h"
#include"Game.h"
#include"File.h"
using namespace std;

//constructor for beginning a game
Game::Game(Army* newArmy1, Army* newArmy2) : FirstArmy(*newArmy1), SecondArmy(*newArmy2), turnNum(1)
{
	//selector to decide which army goes first
	int goesFirst;
	cout << "Who goes first?\n\n1. " << FirstArmy.armyName << "\n2. " << SecondArmy.armyName << endl;
	cin >> goesFirst;
	bool flag = true;
	if (!cin.fail() && (goesFirst == 2 || goesFirst == 1))
		flag = false;
	else while (flag) //checks to make sure that the point value entered can be converted to int type
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nThe menu selection must be 1 or a 2, please try again: ";
		cin >> goesFirst;
		if (!cin.fail() && (goesFirst == 2 || goesFirst == 1))
		{
			flag = false;
			cin.clear();
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	//switches the order of the two armies if army2 is selected to go first
	if (goesFirst == 2)
	{
		Army TempArmy = FirstArmy;
		FirstArmy = SecondArmy;
		SecondArmy = TempArmy;
	}
}

Game::~Game()
{
	//blank
}


//checks to see if the unit has taken more casualties than it contains models
bool Game::unitDead(int count)
{
	if (count <= 0)
		return true;
	else return false;
}


//function which returns a turn's casualty results
string Game::unitCasualties(Army* inflictingArmy, Army* army)
{
	int idSelect, casNum;
	army->displayArmy(); //displays army so user can select
	cout << "\n\nEnter Unit ID of Unit Taking Casualties: ";
	cin >> idSelect;
	//checks for valid unit ID
	{
		bool flag = true;
		if (!cin.fail())
			flag = false;
		else while (flag) //checks to make sure that the point value entered can be converted to int type
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nThe unit ID must be an integer, please try again: ";
			cin >> idSelect;
			if (!cin.fail())
			{
				flag = false;
				cin.clear();
			}
		}
	}
	{
		//iterates through a loop in order to select the appropriate unit based on unit ID
		Unit* pTemp = army->pUFirst;
		while (pTemp->pUNext != nullptr) //loop to select appropriate unit
		{
			if (pTemp->unitID == idSelect)
			{
				break;
			}
			else
			{
				pTemp = pTemp->pUNext;
			}
		}
		if (pTemp->unitID != idSelect)
		{
			cout << "Unit ID does not match an existing unit";
		}
		else //repeats the unit selection process
		{
			inflictingArmy->displayArmy();
			cout << "\n\nEnter Unit ID of Unit Inflicting Casualties or a 0 for self inflicted wounds: ";
			cin >> idSelect;
			//checks for valid unit ID
			{
				bool flag = true;
				if (!cin.fail())
					flag = false;
				else while (flag) //checks to make sure that the point value entered can be converted to int type
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\nThe unit ID must be an integer, please try again: ";
					cin >> idSelect;
					if (!cin.fail())
					{
						flag = false;
						cin.clear();
					}
				}
			}
			//section for selecting how to handle a selection of 0, indicating self inflicted casualties
			if (idSelect == 0)
			{
				cout << "Casualty was self inflicted, enter number of casualties: ";
				cin >> casNum;
				//checks for valid unit ID
				bool flag = true;
				if (!cin.fail())
					flag = false;
				else while (flag) //checks to make sure that the point value entered can be converted to int type
				{						
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\nThe unit number of casualties must be an integer, please try again: ";
					cin >> casNum;
					if (!cin.fail())
					{
						flag = false;
						cin.clear();
					}
				}
				pTemp->unitSize = pTemp->unitSize - casNum;
				pTemp->casSustained = pTemp->casSustained + casNum;
				if (unitDead(pTemp->unitSize))
					return pTemp->uName + " wiped out itself out!\n";
				else return pTemp->uName + " inflicted " + to_string(casNum) + " casualties on itself!\n";
			}
		else
			{
				Unit* pITemp = inflictingArmy->pUFirst;
				while (pITemp->pUNext != nullptr) //loop to select appropriate unit
				{
					if (pITemp->unitID == idSelect)
					{
						break;
					}
					else
					{
						pITemp = pITemp->pUNext;
					}
				}
				if (pITemp->unitID != idSelect)
				{
					cout << "Unit ID does not match an existing unit\n";
				}
				else
				{
					cout << "Enter number of casualties inflicted: ";
					cin >> casNum;
					bool flag = true;
					if (!cin.fail())
						flag = false;
					else while (flag) //checks to make sure that the point value entered can be converted to int type
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "\nThe unit number of casualties must be an integer, please try again: ";
						cin >> casNum;
						if (!cin.fail())
						{
							flag = false;
							cin.clear();
						}
					}
					//adds the casualty number to the appropriate member variables of unit
					pTemp->unitSize = pTemp->unitSize - casNum;
					pTemp->casSustained = pTemp->casSustained + casNum;
					pITemp->casInflicted = pITemp->casInflicted + casNum;
					if (unitDead(pTemp->unitSize))
						return pITemp->uName + " wiped out " + pTemp->uName + "!\n";
					else return pITemp->uName + " inflicted " + to_string(casNum) + " casualties on " + pTemp->uName + "\n";
				}
			}
		}
	}
	return "";//return to catch unhandled selections
}


//function for handling an individual game turn
string Game::turn(int turnNum)
{
	int response;
	string turnResults = FirstArmy.armyName + "      Turn " + to_string(turnNum) + "\n\nMOVE PHASE\n"; //string of the turn results to be returned, will be consistenty added to
	cout << "\n\nMOVE PHASE\nAny casualties during the move phase? (1 for yes 2 for no)\n";
	cin >> response;
	bool flag = true;
	if (!cin.fail() && (response == 1 || response == 2))
		flag = false;
	else while (flag) //checks to make sure that the point value entered can be converted to int type
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nThe response must be an integer, please try again: ";
		cin >> response;
		if (!cin.fail() && (response == 1 || response == 2))
		{
			flag = false;
			cin.clear();
		}
	}
	if (response == 1)//what happeens if casualties are reported
	{
		bool exit = true;
		turnResults = turnResults + unitCasualties(&SecondArmy, &FirstArmy);
		while (exit)
		{
			cout << "\n\nMOVE PHASE\nFurther casualties? (1 for yes 2 for no)\n";
			cin >> response;
			bool flag = true;
			if (!cin.fail() && (response == 1 || response == 2))
				flag = false;
			else while (flag) //checks to make sure that the point value entered can be converted to int type
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\nThe response must be an integer, please try again: ";
				cin >> response;
				if (!cin.fail() && (response == 1 || response == 2))
				{
					flag = false;
					cin.clear();
				}
			}
			if (response == 1)
			turnResults = turnResults + unitCasualties(&SecondArmy, &FirstArmy);
			else exit = false;
		}
	}
	else turnResults = turnResults + "No casualties reported";

	turnResults = turnResults + "\n\nSHOOTING PHASE\n";
	cout << "\n\nSHOOTING PHASE\nAny casualties during the shooting phase? (1 for yes 2 for no)\n";
	cin >> response;
	flag = true;
	if (!cin.fail() && (response == 1 || response == 2))
		flag = false;
	else while (flag) //checks to make sure that the point value entered can be converted to int type
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nThe response must be an integer, please try again: ";
		cin >> response;
		if (!cin.fail() && (response == 1 || response == 2))
		{
			flag = false;
			cin.clear();
		}
	}
	if (response == 1)//what happens if casualties are reported
	{
		bool exit = true;
		turnResults = turnResults + unitCasualties(&FirstArmy, &SecondArmy);
		while (exit)
		{
			cout << "\n\nSHOOTING PHASE\nFurther casualties? (1 for yes 2 for no)\n";
			cin >> response;
			bool flag = true;
			if (!cin.fail() && (response == 1 || response == 2))
				flag = false;
			else while (flag) //checks to make sure that the point value entered can be converted to int type
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\nThe response must be an integer, please try again: ";
				cin >> response;
				if (!cin.fail() && (response == 1 || response == 2))
				{
					flag = false;
					cin.clear();
				}
			}
			if (response == 1)
				turnResults = turnResults + unitCasualties(&FirstArmy, &SecondArmy);
			else exit = false;
		}
	}
	else turnResults = turnResults + "No casualties reported";

	turnResults = turnResults + "\n\nASSAULT PHASE\n";
	cout << "\n\nASSAULT PHASE\nAny casualties during the assault phase by the army who's turn it currently is? (1 for yes 2 for no)\n";
	cin >> response;
	flag = true;
	if (!cin.fail() && (response == 1 || response == 2))
		flag = false;
	else while (flag) //checks to make sure that the point value entered can be converted to int type
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nThe response must be an integer, please try again: ";
		cin >> response;
		if (!cin.fail() && (response == 1 || response == 2))
		{
			flag = false;
			cin.clear();
		}
	}
	if (response == 1)//what happens if casualties are reported
	{
		bool exit = true;
		turnResults = turnResults + unitCasualties(&FirstArmy, &SecondArmy);
		while (exit)
		{
			cout << "\n\nASSAULT PHASE\nFurther casualties? (1 for yes 2 for no)\n";
			cin >> response;
			bool flag = true;
			if (!cin.fail() && (response == 1 || response == 2))
				flag = false;
			else while (flag) //checks to make sure that the point value entered can be converted to int type
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\nThe response must be an integer, please try again: ";
				cin >> response;
				if (!cin.fail() && (response == 1 || response == 2))
				{
					flag = false;
					cin.clear();
				}
			}
			if (response == 1)
				turnResults = turnResults + unitCasualties(&FirstArmy, &SecondArmy);
			else exit = false;
		}
	}
	cout << "\n\nASSAULT PHASE\nAny casualties during the assault phase by the opposing player? (1 for yes 2 for no)\n";
	cin >> response;
	flag = true;
	if (!cin.fail() && (response == 1 || response == 2))
		flag = false;
	else while (flag) //checks to make sure that the point value entered can be converted to int type
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nThe response must be an integer, please try again: ";
		cin >> response;
		if (!cin.fail() && (response == 1 || response == 2))
		{
			flag = false;
			cin.clear();
		}
	}
	if (response == 1)//what happens if casualties are reported
	{
		bool exit = true;
		turnResults = turnResults + unitCasualties(&SecondArmy, &FirstArmy);
		while (exit)
		{
			cout << "\n\nASSAULT PHASE\nFurther casualties? (1 for yes 2 for no)\n";
			cin >> response;
			bool flag = true;
			if (!cin.fail() && (response == 1 || response == 2))
				flag = false;
			else while (flag) //checks to make sure that the point value entered can be converted to int type
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\nThe response must be an integer, please try again: ";
				cin >> response;
				if (!cin.fail() && (response == 1 || response == 2))
				{
					flag = false;
					cin.clear();
				}
			}
			if (response == 1)
				turnResults = turnResults + unitCasualties(&SecondArmy, &FirstArmy);
			else exit = false;
		}
	}
	else turnResults = turnResults + "No casualties reported";

	//begins second armies turn
turnResults = turnResults + "\n\n\n\n";
turnResults = turnResults + SecondArmy.armyName + "      Turn " + to_string(turnNum) + "\n\nMOVE PHASE\n";
cout << "\n\nMOVE PHASE\nAny casualties during the move phase? (1 for yes 2 for no)\n";
cin >> response;
flag = true;
if (!cin.fail() && (response == 1 || response == 2))
flag = false;
else while (flag) //checks to make sure that the point value entered can be converted to int type
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "\nThe response must be an integer, please try again: ";
	cin >> response;
	if (!cin.fail() && (response == 1 || response == 2))
	{
		flag = false;
		cin.clear();
	}
}
if (response == 1)//what happens if casualties are reported
{
	bool exit = true;
	turnResults = turnResults + unitCasualties(&FirstArmy, &SecondArmy);
	while (exit)
	{
		cout << "\n\nMOVE PHASE\nFurther casualties? (1 for yes 2 for no)\n";
		cin >> response;
		bool flag = true;
		if (!cin.fail() && (response == 1 || response == 2))
			flag = false;
		else while (flag) //checks to make sure that the point value entered can be converted to int type
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nThe response must be an integer, please try again: ";
			cin >> response;
			if (!cin.fail() && (response == 1 || response == 2))
			{
				flag = false;
				cin.clear();
			}
		}
		if (response == 1)
			turnResults = turnResults + unitCasualties(&FirstArmy, &SecondArmy);
		else exit = false;
	}
}
else turnResults = turnResults + "No casualties reported";

turnResults = turnResults + "\n\nSHOOTING PHASE\n";
cout << "\n\nSHOOTING PHASE\nAny casualties during the shooting phase? (1 for yes 2 for no)\n";
cin >> response;
flag = true;
if (!cin.fail() && (response == 1 || response == 2))
flag = false;
else while (flag) //checks to make sure that the point value entered can be converted to int type
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "\nThe response must be an integer, please try again: ";
	cin >> response;
	if (!cin.fail() && (response == 1 || response == 2))
	{
		flag = false;
		cin.clear();
	}
}
if (response == 1)//what happens if casualties are reported
{
	bool exit = true;
	turnResults = turnResults + unitCasualties(&SecondArmy, &FirstArmy);
	while (exit)
	{
		cout << "\n\nSHOOTING PHASE\nFurther casualties? (1 for yes 2 for no)\n";
		cin >> response;
		bool flag = true;
		if (!cin.fail() && (response == 1 || response == 2))
			flag = false;
		else while (flag) //checks to make sure that the point value entered can be converted to int type
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nThe response must be an integer, please try again: ";
			cin >> response;
			if (!cin.fail() && (response == 1 || response == 2))
			{
				flag = false;
				cin.clear();
			}
		}
		if (response == 1)
			turnResults = turnResults + unitCasualties(&SecondArmy, &FirstArmy);
		else exit = false;
	}
}
else turnResults = turnResults + "No casualties reported";

turnResults = turnResults + "\n\nASSAULT PHASE\n";
cout << "\n\nASSAULT PHASE\nAny casualties during the assault phase by the army who's turn it currently is? (1 for yes 2 for no)\n";
cin >> response;
flag = true;
if (!cin.fail() && (response == 1 || response == 2))
flag = false;
else while (flag) //checks to make sure that the point value entered can be converted to int type
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "\nThe response must be an integer, please try again: ";
	cin >> response;
	if (!cin.fail() && (response == 1 || response == 2))
	{
		flag = false;
		cin.clear();
	}
}
if (response == 1)//what happens if casualties are reported
{
	bool exit = true;
	turnResults = turnResults + unitCasualties(&SecondArmy, &FirstArmy);
	while (exit)
	{
		cout << "\n\nASSAULT PHASE\nFurther casualties? (1 for yes 2 for no)\n";
		cin >> response;
		bool flag = true;
		if (!cin.fail() && (response == 1 || response == 2))
			flag = false;
		else while (flag) //checks to make sure that the point value entered can be converted to int type
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nThe response must be an integer, please try again: ";
			cin >> response;
			if (!cin.fail() && (response == 1 || response == 2))
			{
				flag = false;
				cin.clear();
			}
		}
		if (response == 1)
			turnResults = turnResults + unitCasualties(&SecondArmy, &FirstArmy);
		else exit = false;
	}
}
cout << "\n\nASSAULT PHASE\nAny casualties during the assault phase by the opposing player? (1 for yes 2 for no)\n";
cin >> response;
flag = true;
if (!cin.fail() && (response == 1 || response == 2))
flag = false;
else while (flag) //checks to make sure that the point value entered can be converted to int type
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "\nThe response must be an integer, please try again: ";
	cin >> response;
	if (!cin.fail() && (response == 1 || response == 2))
	{
		flag = false;
		cin.clear();
	}
}
if (response == 1)
{
	bool exit = true;
	turnResults = turnResults + unitCasualties(&FirstArmy, &SecondArmy);
	while (exit)
	{
		cout << "\n\nASSAULT PHASE\nFurther casualties? (1 for yes 2 for no)\n";
		cin >> response;
		bool flag = true;
		if (!cin.fail() && (response == 1 || response == 2))
			flag = false;
		else while (flag) //checks to make sure that the point value entered can be converted to int type
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nThe response must be an integer, please try again: ";
			cin >> response;
			if (!cin.fail() && (response == 1 || response == 2))
			{
				flag = false;
				cin.clear();
			}
		}
		if (response == 1)
			turnResults = turnResults + unitCasualties(&FirstArmy, &SecondArmy);
		else exit = false;
	}
}
else turnResults = turnResults + "No casualties reported\n\n";

turnResults = turnResults + "\n\n\n\n";
return turnResults;
}


//function for getting the game result
string Game::displayGameResult()
{
	return gameResult;
}

//returns a string of each unit and its performance during the game, much like when saving the unit to file, though with casualty stats
string Game::unitReport(Army* army1, Army* army2)
{
	string reportString = army1->armyName + "\n\n\n" + " Unit Name             ID  Point Value  Casualties Inflicted  Casualties Sustained\n\n";
	if (army1->pUFirst != nullptr)
	{
		Unit* pIterator = army1->pUFirst;
		while (pIterator->pUNext != nullptr)
		{
			reportString = reportString + pIterator->uName + to_string(pIterator->unitID) + "    " + to_string(pIterator->pointValue) + "   " + to_string(pIterator->casInflicted) + "      "  + to_string(pIterator->casSustained) + "\n";
			pIterator = pIterator->pUNext;
		}
			reportString = reportString + pIterator->uName + to_string(pIterator->unitID) + "    " + to_string(pIterator->pointValue) + "   " + to_string(pIterator->casInflicted) + "      " + to_string(pIterator->casSustained) + "\n";
	}

	reportString = reportString + "\n\n\n\n" + army2->armyName + "\n\n\n" + " Unit Name||ID||Point Value||Casualties Inflicted||Casualties Sustained\n\n";
	if (army1->pUFirst != nullptr)
	{
		Unit* pIterator = army2->pUFirst;
		while (pIterator->pUNext != nullptr)
		{
			reportString = reportString + pIterator->uName + to_string(pIterator->unitID) + "    " + to_string(pIterator->pointValue) + "   " + to_string(pIterator->casInflicted) + "      " + to_string(pIterator->casSustained) + "\n";
			pIterator = pIterator->pUNext;
		}
		reportString = reportString + pIterator->uName + to_string(pIterator->unitID) + "    " + to_string(pIterator->pointValue) + "   " + to_string(pIterator->casInflicted) + "      " + to_string(pIterator->casSustained) + "\n";
	}
	return reportString;
}