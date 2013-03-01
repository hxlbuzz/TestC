/*
 * CRobotMaker.cpp
 *
 *  Created on: 2013-1-22
 *      Author: nick
 */
#include <cstdlib>
#include "Tp_CRobotMaker.h"



int TpCRobotMaker::makeRobot(int num, int x, int y)
{
	int ret = 0;
	posX = x;
	posY = y;
	if (num > 0)
	{
		int robotTotalNum = robotIdVec.size();

		for (int i = 0; i < num; i++)
		{
			char uId[16] = {0};
			sprintf(uId, "Robot%d", robotTotalNum + i);
			string uIdStr = string(uId);
			robotIdVec.push_back(uIdStr);
		}
		ret = 1;
	}
	return ret;
}

int TpCRobotMaker::clearRobot(int num)
{
	int ret = 0;

	if(num > 0)
	{
		for (int i = 0; i < num; i ++)
		{
			if(!robotIdVec.empty())
			{
				robotIdVec.pop_back();
			}
		}
		ret = 1;
	}
	return ret;
}

string TpCRobotMaker::makePosStr()
{
	string ret = "";
	static int count = 0;
	if (count > 0)
	{
		count --;	
		return ret;
	}
	else
	{
		count = 4;	
	}

	int i = 0;
	ret.clear();
	vector<string>::iterator it;
	for (it = robotIdVec.begin(); it != robotIdVec.end(); it ++)
	{
		int x, y;
		char xc[8] = {0};
		char yc[8] = {0};

		i ++;
		srand(time(0) + i);
		x = rand()%10 + posX;
		y = rand()%10 + posY;
		sprintf(xc, "%d", x);
		sprintf(yc, "%d", y);
		ret.append("|");
		ret.append(it->c_str());
		ret.append("|");
		ret += string(xc);
		//ret.append(x);
		ret.append("|");
		ret += string(yc);
		ret.append("|");
		ret += string("0");
	}
	return ret;

}


