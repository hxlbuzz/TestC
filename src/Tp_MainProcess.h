/*
 * MainProcess.h
 *
 *  Created on: 2013-1-6
 *      Author: sakishum1118
 */

#ifndef MAINPROCESS_H_
#define MAINPROCESS_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "common/Tp_typedef.h"
#include "Tp_CRobotMaker.h"
#include "Tp_CPlayerInfo.h"
#include "Tp_CStandardIO.h"
//protobuff 相关的头文件
#include "proto/Tp_ProtobufInclude.h"
//#include "proto/lm.helloworld.pb.h"
//#include "proto/ProtoTest1.pb.h"

using namespace std;


#define G_MAX_ERVERY_SEC_MSG_LENGTH  2048  //周期定时消息数据最大长度
#define G_MAX_MSG_BUFF_LENGTH        2048  //接收消息buff最大长度
//#define DEBUG_MODE

#define swap16(x) ((x & 0xff00 ) >> 8 | (x & 0x00ff) << 8)

#ifdef DEBUG_MODE
#define  LOG_MODE
#endif
//从erlang传过来的消息类型

/// 与前台对应
const string plugin_head = "Plug_in_msg";

typedef queue<string> MsgQueue_t;

typedef vector<char>  Message_vct;//保存接收到或者需要处理的信息

/// 主逻辑进程
class TpMainProcess {
private:
	typedef vector<string> stringArray;
	typedef vector<Message_vct> msg_parts;
	typedef map<int, Message_vct> msg_pairs;
	typedef
	enum{
		E_MSG_TYPE_NOME,
		E_MSG_TYPE_GETUSRLIST,
		E_MSG_TYPE_MSG,
		E_MSG_TYPE_LOGOUT,
	}E_ERLANG_MSG_TYPE;

	string strEverySecMsg;//
	string strPingMsg;
	CPlayerInfo* m_pPlayerInfo;//by now  It's containing positiong msg // 2013.1.21
	TpCRobotMaker* m_pRobotMaker;
	MsgQueue_t msgQueue;
	Message_vct  m_inMsg;
public:
	TpMainProcess();
	virtual ~TpMainProcess();
private:
	string format_back_msg (string Command, string Value);// 组串返回
	bool format_back_msg (string Command, char* Value, unsigned short val_len);// 组串返回
	string format_back_msg_to_socket(string Command, string Value, string Socket);// 向某个socket发送信息
	int splitInString(string& _in, string seg, vector<string>& Array);
	int getMsgParts(Message_vct& _inMsg, msg_parts&_outParts);
public:
	/*
	 *@data: a completed msg(without head) for erlang, it could contain 0
	 *@len : length of the @data
	 */
	char* process_msg_in(char*data, unsigned short len);
	bool processPbMessage(Message* pbMsg, TP_E_PROTOBUF_GLOBAL_MSG_TYPE type);
};

// 返回定义
// 多个信息用|//|隔开 例如 RAM|//|done|/|Value|//|done|/|Value|//|done|/|Value
// RAM|//|done|/|Value 这个Value值会被忽略
// RAM|//|Msg|/|Value
// RAM|//|SendBack|/|Value 回调自身，会自动加上Msg前缀 也就是发出的信息自动加为 Msg|*|SocketString|*|Value
// RAM|//|Leave|/|SocketString 强制退出Socket客户端
// RAM|//|MsgToSingleSocket|/|Value|/|SocketString 发给单一用户

#endif /* MAINPROCESS_H_ */
