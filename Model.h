/*
 * Model.h
 *
 *  Created on: Apr 13, 2014
 *      Author: Brian
 */

using namespace std;
#ifndef MODEL_H_
#define MODEL_H_

#include<string>
#include<iostream>
#include<memory>

class Model
{
public:
	Model(string,string);
	Model();
	~Model();

	string getName();
	void setName(string);
	Model* pMNext;
	string name;
	string description;

};



#endif /* MODEL_H_ */
