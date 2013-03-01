//
//  CPlayerInfo.cpp
//  ErlangPlugin
//
//  Created by shum saki on 13-1-11.
//  Copyright (c) 2013年 shum saki. All rights reserved.
//

#include "Tp_CPlayerInfo.h"

bool CPlayerInfo::isEmpty()
{
    // 判断 map 是否为空
    if(this->m_recordList.empty()){
        return true;
    }
    
    return false;
}

bool CPlayerInfo::addNewRecord(int id, string data)//const USER_INFO& data)
{
	int size = this->m_recordList.size();
	if (getListLen() == 0)
	{
		mAllRecordLen = 0;
	}

	if (size > 0)
	{
			map_RecordList::iterator l_it;
			int detaLen = 0;
			l_it = this->m_recordList.find(id);

			if (l_it == this->m_recordList.end()){
				this->m_recordList.insert(make_pair(id, data));
				mAllRecordLen = data.size();
			}else{
				//m_recordList.erase(it);
				detaLen = data.size() -  ((string)l_it->second).size();
				((string)l_it->second).clear();
				(string)l_it->second = data;
				mAllRecordLen += detaLen;
			}
	}
	else
	{
		this->m_recordList.insert(make_pair(id, data));
		mAllRecordLen = data.size();
	}

    return false;
}

string CPlayerInfo::findListID(int id)
{
    
    
    /// find the date which id equal "id"
    map_RecordList::iterator tempIt = this->m_recordList.find(id);
    /// find the data
    if ( tempIt != this->m_recordList.end() ) {
        string data = tempIt->second;
        return data;    //data.m_Pos;
    }
    return "empty";
}

bool CPlayerInfo::deleteAllRecord()
{
    this->m_recordList.clear();
    /// 判断是否清除成功
    if(isEmpty()){
        return true;
    }
    return false;
}

bool CPlayerInfo::deleteARecord(int id)
{
    // 判断 map 是否为空
    if(isEmpty()){
        return false;
    }
    
    // 通过迭代器删除
    map_RecordList::iterator tempIt = this->m_recordList.find(id);
    this->m_recordList.erase(tempIt);
    return false;
}

string CPlayerInfo::getAllRecord()
{
    string result = "";
    // 判断 map 是否为空
    if(isEmpty()){
        return result;
    }
    int len = m_recordList.size();
	int count = 0;
    for(map_RecordList::iterator tempIt = this->m_recordList.begin(); tempIt != this->m_recordList.end(); ++tempIt)
    {
		count ++;
        result += tempIt->second;

		if ( count < len)
		{
			result += "|";
		}
    }
    
    return result;
}

int CPlayerInfo::getListLen()
{
    /// return map's len
    return  static_cast<int>(this->m_recordList.size());
}

int CPlayerInfo::getAllRecordLen()
{
	return mAllRecordLen;
}
