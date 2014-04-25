/*
 * Main.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: Brian
 */

#include<iostream>
#include<string>
#include<fstream>
#include"File.h"
#include"Army.h"
#include"Unit.h"
#include"Model.h"
#include"Game.h"
using namespace std;



int main()
{
	cout << "*****PLEASE NOTE THAT SPACES IN STRINGS ARE NOT ALLOWED! WILL CAUSE ERRORS*****\n\n";
	File File1;
	Army Army1;
	int option;
	cout << "Load an existing army or create a new one?\n\n1. Load\n2. Create new\n\n";
	cin >> option;
	bool flag = true;
	if (!cin.fail() && (option == 2 || option == 1))
		flag = false;
	else while (flag) //checks to make sure that the point value entered can be converted to int type
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nThe menu selection must be 1 or a 2, please try again: ";
		cin >> option;
		if (!cin.fail() &&( option == 2 || option == 1))
		{
			flag = false;
			cin.clear();
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	string army1;
	if (option == 1)
	{
		cout << "Enter the name of the file to load: ";
		cin >> army1;
		Army* TempArmy = File1.loadArmy(army1); 
		Army1 = *TempArmy;
	}
	else
	{
		cout << "Enter First Army Name: ";
		cin >> army1;
		Army* TempArmy = new Army(army1);
		Army1 = *TempArmy;
	}

	bool exit = false;
	while (exit != true) //menu loop
	{
		string uName;
		string uDesc;

		int selection = 0;
		cout << "\n1. Create New Unit\n2. Edit a Unit\n3. View Unit List\n4. Next Army\nEnter Selection: ";
		cin >> selection;
			bool flag = true;
			if (!cin.fail())
				flag = false;
			else while (flag) //checks to make sure that the point value entered can be converted to int type
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\nThe menu selection must be an integer, please try again: ";
				cin >> selection;
				if (!cin.fail())
				{
					flag = false;
					cin.clear();
				}
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		switch (selection)
		{
		case 1:
			Army1.addUnit();
			break;
		case 2: //allows user to select which unit to select, then provides assorted editing options
			Army1.displayArmy();
			cout << "Enter Unit ID of Unit to Edit: ";
			int idSelect;
			cin >> idSelect;
			//checks for valid unit ID
			{
				bool flag = true;
				if ( ! cin.fail())
					flag = false;
				else while (flag) //checks to make sure that the point value entered can be converted to int type
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\nThe unit ID must be an integer, please try again: ";
					cin >> idSelect;
					if ( ! cin.fail())
					{
						flag = false;
						cin.clear();
					}
				}
			}
			{
				Unit* pTemp = Army1.pUFirst;
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
				else
				{
					cout << "Select Action to Perform\n1. Change Unit Name\n2. Change Point Value\n3. Add Model\n4. Display Unit\n";
					int select;
					cin >> select;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					switch (select)
					{
					case 1:
						pTemp->setName();
						break;
					case 2:
						Army1.pointTotal = Army1.pointTotal - pTemp->pointValue;
						pTemp->setPointValue();
						Army1.pointTotal = Army1.pointTotal + pTemp->pointValue;
						break;
					case 3:
						cout << "Enter Model Name: ";
						cin >> uName;
						cout << "Enter optional description: ";
						cin >> uDesc;
						pTemp->addModel(uName, uDesc);
						break;
					case 4:
						pTemp->displayUnit();
						break;
					default:
						cout << "Invalid Selection";
						break;
					}
				}
			}
			break;
		case 3:
			Army1.displayArmy();
			break;
		case 4:
			File1.saveArmy(&Army1);
			exit = true;
			break;
		default:
			cout << "Invalid selection. Try again.";
			break;
		}
	}

		//begins second army creation
		File File2;
		string army2;
		Army Army2;
		cout << "Load an existing army or create a new one?\n\n1. Load\n2. Create new\n\n";
		cin >> option;
		flag = true;
		if (!cin.fail() && (option == 2 || option == 1))
			flag = false;
		else while (flag) //checks to make sure that the point value entered can be converted to int type
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nThe menu selection must be 1 or a 2, please try again: ";
			cin >> option;
			if (!cin.fail() && (option == 2 || option == 1))
			{
				flag = false;
				cin.clear();
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if (option == 1)
		{
			cout << "Enter the name of the file to load: ";
			cin >> army2;
			Army* TempArmy2 = File2.loadArmy(army2);
			Army2= *TempArmy2;
		}
		else
		{
			cout << "Enter Second Army Name: ";
			cin >> army2;
			Army* TempArmy2 = new Army(army2);
			Army2 = *TempArmy2;
		}
		exit = false;
		while (exit != true) //menu loop
		{
			string uName;
			string uDesc;
			int selection = 0;
			cout << "\n1. Create New Unit\n2. Edit a Unit\n3. View Unit List\n4. Begin Game\nEnter Selection: ";
			cin >> selection;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			switch (selection)
			{
			case 1:
				Army2.addUnit();
				break;
			case 2:
				Army2.displayArmy();
				cout << "Enter Unit ID of Unit to Edit: ";
				int idSelect;
				cin >> idSelect;
				//checks for valid unit ID
				{
					bool flag = true;
					if ( ! cin.fail())
						flag = false;
					else while (flag) //checks to make sure that the point value entered can be converted to int type
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "\nThe unit ID must be an integer, please try again: ";
						cin >> idSelect;
						if ( ! cin.fail())
						{
							flag = false;
							cin.clear();
						}
					}
				}
				{
					Unit* pTemp = Army2.pUFirst;
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
					else
					{
						cout << "Select Action to Perform\n1. Change Unit Name\n2. Change Point Value\n3. Add Model\n4. Display Unit\n";
						int select;
						cin >> select; 
						bool flag = true;
						if ( ! cin.fail())
							flag = false;
						else while (flag) //checks to make sure that the point value entered can be converted to int type
						{
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							cout << "\nThe unit ID must be an integer, please try again: ";
							cin >> select;
							if ( ! cin.fail())
							{
								flag = false;
								cin.clear();
							}
						}
						switch (select)
						{
						case 1:
							pTemp->setName();
							break;
						case 2:
							Army2.pointTotal = Army2.pointTotal - pTemp->pointValue;
							pTemp->setPointValue();
							Army2.pointTotal = Army2.pointTotal + pTemp->pointValue;
							break;
						case 3:
							cout << "Enter Model Name: ";
							cin >> uName;
							cout << "Enter optional description: ";
							cin >> uDesc;
							pTemp->addModel(uName, uDesc);
							break;
						case 4:
							pTemp->displayUnit();
							break;
						default:
							cout << "Invalid Selection";
							break;
						}
					}
				}
				break;
			case 3:
				Army2.displayArmy();
				break;
			case 4:
				File2.saveArmy(&Army2);
				exit = true;
				break;
			default:
				cout << "Invalid selection. Try again.";
				break;
			}
		}
		
		Game Game(&Army1, &Army2);
		Game.gameResult = Game.turn(1);
		cout << Game.gameResult;
		Game.gameResult = Game.gameResult + Game.turn(2);
		cout << Game.gameResult;
		Game.gameResult = Game.gameResult + Game.turn(3);
		cout << Game.gameResult;
		Game.gameResult = Game.gameResult + Game.turn(4);
		cout << Game.gameResult;
		Game.gameResult = Game.gameResult + Game.turn(5);
		cout << Game.gameResult;
		cout << "Does the game continue? (1 for yes, 2 for no)\n";
		cin >> option;
		flag = true;
		if (!cin.fail() && (option == 2 || option == 1))
			flag = false;
		else while (flag) //checks to make sure that the point value entered can be converted to int type
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nThe menu selection must be 1 or a 2, please try again: ";
			cin >> option;
			if (!cin.fail() && (option == 2 || option == 1))
			{
				flag = false;
				cin.clear();
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if (option == 1)
		{
			Game.gameResult = Game.gameResult + Game.turn(6);
			cout << Game.gameResult;
			cout << "Does the game continue? (1 for yes, 2 for no)\n";
			cin >> option;
			flag = true;
			if (!cin.fail() && (option == 2 || option == 1))
				flag = false;
			else while (flag) //checks to make sure that the point value entered can be converted to int type
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\nThe menu selection must be 1 or a 2, please try again: ";
				cin >> option;
				if (!cin.fail() && (option == 2 || option == 1))
				{
					flag = false;
					cin.clear();
				}
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			if (option == 1)
			{
				Game.gameResult = Game.gameResult + Game.turn(7);
			}
		}
		Game.gameResult = Game.gameResult + Game.unitReport(&Game.FirstArmy, &Game.SecondArmy);
		cout << Game.gameResult;
		File1.saveGame(Game.gameResult, Army1.armyName, Army2.armyName);
		return 0;
}