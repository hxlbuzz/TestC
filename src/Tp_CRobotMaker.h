/*
 * CRobotMaker.h
 *
 *  Created on: 2013-1-22
 *      Author: nick
 *      简单实现增加能够随机走动的机器人
 */

#ifndef CROBOTMAKER_H_
#define CROBOTMAKER_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <map>
using namespace std;

class Robot{
private:
	int posX;
	int posY;
	string uId;
public:
	Robot(){
		posX = 0;
		posY = 0;
		uId  = string("");
	};
	~Robot();

	void create(int x, int y, string& uIdStr){};
};

class TpCRobotMaker{
private:
	int posX;
	int posY;
	vector<string> robotIdVec;
public:
	TpCRobotMaker(){};
	~TpCRobotMaker(){};

	int makeRobot(int num, int x, int y);
	int clearRobot(int num);
    string makePosStr();
};
#endif /* CROBOTMAKER_H_ */
