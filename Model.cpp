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

Model::Model(string newName, string desc) : pMNext(nullptr), name(newName), description(desc)
	{

	}

Model::Model() : pMNext(nullptr)
{

}

	Model::~Model()
	{
		//intentionally blank
	}

	string Model::getName()
	{
		return name;
	}

	void Model::setName(string input)
	{
		cout << "Enter model name and/or description: ";
		cin >> name;
	}
