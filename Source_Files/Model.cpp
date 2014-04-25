/*
 * Model.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: Brian
 */

#include<string>
#include<iostream>
#include"Model.h"
using namespace std;

//simple constructor
Model::Model(string newName, string desc) : pMNext(nullptr), name(newName), description(desc)
	{

	}

	//simple constructor
Model::Model() : pMNext(nullptr)
{
	//intentionally blank
}

	Model::~Model()
	{
		//intentionally blank
	}

	
	//standard getter function
	string Model::getName()
	{
		return name;
	}

	//standard setter function
	void Model::setName(string input)
	{
		cout << "Enter model name and/or description: ";
		cin >> name;
	}
