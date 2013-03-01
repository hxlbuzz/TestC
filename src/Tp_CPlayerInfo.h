//
//  CPlayerInfo.h
//  ErlangPlugin
//
//  Created by shum saki on 13-1-11.
//  Copyright (c) 2013年 shum saki. All rights reserved.
//

#ifndef __ErlangPlugin__CPlayerInfo__
#define __ErlangPlugin__CPlayerInfo__

#include <iostream>
#include <string> 
#include <map>

using namespace std;

//typedef struct USER_INFO
//{
//    string m_Pos;
//    string m_Socket;
//}USER_INFO;

class CPlayerInfo {
private:
    typedef map<int, string> map_RecordList;   /// Record player's all status
    map_RecordList m_recordList;
    bool m_isListReaded;
    int  mAllRecordLen;
public:
    bool isEmpty();
    bool addNewRecord(int, string);
    
    bool deleteAllRecord();
    bool deleteARecord(int);
    
    string findListID(int);
    string getAllRecord();
    int getListLen();
    int getAllRecordLen();
};  /// CPlayerInfo

#endif /* defined(__ErlangPlugin__CPlayerInfo__) */
