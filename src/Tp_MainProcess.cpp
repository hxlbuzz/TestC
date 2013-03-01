/*
 * MainProcess.cpp
 *
 *  Created on: 2013-1-6
 *      Author: sakishum1118
 */
#include <cstring>
#include "Tp_MainProcess.h"
TpMainProcess::TpMainProcess() {
	// TODO Auto-generated constructor stub
	m_pPlayerInfo = new CPlayerInfo();
	m_pRobotMaker = new TpCRobotMaker();
	strPingMsg = string("");
}

TpMainProcess::~TpMainProcess() {
	// TODO Auto-generated destructor stub
	delete(m_pPlayerInfo);
	delete(m_pRobotMaker);
	m_pPlayerInfo = 0;
}

string TpMainProcess::format_back_msg(string Command, string Value)
{
	stringArray str_array_f;
	stringArray str_array;

	Message_vct back_msg;

	return "";
}

bool TpMainProcess::format_back_msg(string Command, char* Value, unsigned short val_len)// 组串返回
{
	Message_vct back_msg;
	unsigned short total_len = 0;
	unsigned short ntotal_len = 0;
	byte cmd_len = (byte)Command.size();

	if (val_len < 0)
	{
		TP_LOG("farmat_back_msg error");
		return false;
	}

	total_len = cmd_len + val_len + sizeof(byte); //cmd len 需要占一个字节  //+ sizeof(unsigned short)

	//todo 检查长度是否在正确的范围内

	back_msg.reserve(total_len);
//	ntotal_len = swap16(total_len);

//	memset(back_msg.data(), 0, total_len);

//	memcpy(back_msg.data(), &ntotal_len, sizeof(unsigned short));
	memcpy(back_msg.data(), &cmd_len, sizeof(byte));
	memcpy(back_msg.data() + sizeof(byte), Command.c_str(), Command.size());
	memcpy(back_msg.data() + sizeof(byte) + Command.size(), Value, val_len);

	TP_LOG("to write cmd:");
	TP_LOG(Value);
	write_cmd((byte*)back_msg.data(), (int)total_len);

	back_msg.clear();
	return true;
}

string TpMainProcess::format_back_msg_to_socket(string Command, string Value, string Socket)
{
	stringArray str_array_f;
	stringArray str_array;

	str_array.push_back(Command);
	str_array.push_back(plugin_head + "|" + Value);
	str_array.push_back(Socket);

	str_array_f.push_back("RAM");

	return "";
}

int TpMainProcess::splitInString(string& _in, string seg, stringArray&strArrayOut){
	//string temp = string("");
	int ret = 0;
	int currPos = 0;
	for (int i = 0; i < (int)_in.size(); i ++){
		int pos = -1;
		pos = _in.find(seg, i);

		if (pos < ((int)_in.size()) && pos >= 0){
			int size = 0;

			if (pos > i){
				string s = _in.substr(i, pos - i);

				size = s.size();
				//string::iterator new_end = remove_if(s.begin(), s.end(), bind2nd(equal_to <char>(), ' '));

				//s.erase(new_end, s.end());
				if (size > 0){
					strArrayOut.push_back(s);
				}
			}

			i = pos + seg.size() - 1;
			currPos = i;
			ret ++;
		}
		else{
			if (currPos > 0){
				int size = (int)_in.size();

				if (currPos + 1 <= size - 1){
					string s = _in.substr(currPos + 1, size - 1 - currPos);
					strArrayOut.push_back(s);
				}
			}
			break;
		}
	}
	return ret;
}


int TpMainProcess::getMsgParts(Message_vct& _inMsg, msg_parts& _outParts){

	return 0;
}

char* TpMainProcess::process_msg_in(char* data, unsigned short len){
	unsigned short parsed_len = 0;// length of parsed data
	char* pOut = NULL;//pointer of out data
	msg_parts msgParts;
	Message_vct msgFlag;// msg type flag
	Message_vct msgSoc; // msg socket string
	Message_vct msgProtoData; // msg Protocol buffer data
	E_ERLANG_MSG_TYPE msg_type = E_MSG_TYPE_NOME;
	int partLen = 0;
	bool is_continue = true;

	//parsing data and get messages
	do{
		partLen = static_cast<int> (data[parsed_len]);

		if (partLen <= 0 ){ // todo max size to be set
			is_continue = false;
			break;
		}else{
			parsed_len += 1;
			msgFlag.reserve(partLen + 1);
			memcpy(msgFlag.data(), data + parsed_len, sizeof(char) * partLen);
			msgFlag.data()[partLen] = 0;
			TP_LOG(msgFlag.data());
			//消息标识分类
			if (0 == string(msgFlag.data()).compare("Msg")){
				msg_type = E_MSG_TYPE_MSG;
				TP_LOG("got Msg type");
			}else if(0 == string(msgFlag.data()).compare("Logout")){
				TP_LOG("got Logout type");
				msg_type = E_MSG_TYPE_LOGOUT;

			}else if(0 == string(msgFlag.data()).compare("GetUserList")){
				TP_LOG("got GetUserList type");
				msg_type = E_MSG_TYPE_GETUSRLIST;
			}else{
				msg_type = E_MSG_TYPE_NOME;
			}

			parsed_len += partLen;

		}

		if (parsed_len >= len){
			is_continue = false;
			break;
		}

		partLen = 0;
		partLen = static_cast<int> (data[parsed_len]);
		if (partLen <= 0 || (partLen + parsed_len > len)){ // todo max size to be set
			is_continue = false;
			break;
		}else{
			//第一部分是消息标识，第二部分是固定的socketstr,这里获得socketstr
			char testlog[128] = {0};
			parsed_len += 1;
			msgSoc.reserve(partLen + 1);

			//socket str
			memcpy(msgSoc.data(), data + parsed_len, sizeof(char) * partLen);

			msgSoc.data()[partLen] = 0;
			sprintf(testlog, "socket str len = %d , len = %d parsed_len = %d", partLen, len, parsed_len);
			TP_LOG(testlog);

			//todo save socket str and id
			parsed_len += partLen;
			TP_LOG("got soc str");
			TP_LOG(msgSoc.data());
		}

		partLen = 0;
		switch (msg_type) {
			case E_MSG_TYPE_MSG:
				{//msg类型的 在尾部会接上客户端自定义消息内容，而其他类型则应该已经解析完毕
#if 1
					unsigned short protoId = 0;

					Message_vct msgProtoODataVct;
					string msgProtoOData;

					Message* pbMsgData = NULL;

					static int counter = 0; // for test
					char testlog[512] = {0};
					int body_len = len - parsed_len;
					if (parsed_len >= len){

						TP_LOG("no protocol buffer");
						break;
					}




					TP_LOG("got proto data");

					protoId = (data[parsed_len] | data[parsed_len + 1] << 8);
					// for test
					sprintf(testlog, "body len = %d protoId = %d", body_len, protoId);
					TP_LOG(testlog);
					msgProtoData.reserve(body_len - sizeof(unsigned short) + 1);
					memcpy(msgProtoData.data(), data + parsed_len + sizeof(unsigned short), sizeof(char) * (body_len - sizeof(unsigned short)));
					msgProtoData.data()[body_len] = 0;

					if ((TP_E_PROTOBUF_GLOBAL_MSG_TYPE)protoId <= E_PROTO_MSG_TYPE_MIN || (TP_E_PROTOBUF_GLOBAL_MSG_TYPE)protoId >= E_PROTO_MSG_TYPE_MAX ){
						TP_LOG("error: wrong proto buff type");
						break;
					}

					pbMsgData = TpCreatePbMessageByName(gPbMessageArray[(TP_E_PROTOBUF_GLOBAL_MSG_TYPE)protoId]);
					TP_LOG("proto buf type name : [%s]",gPbMessageArray[(TP_E_PROTOBUF_GLOBAL_MSG_TYPE)protoId].c_str());

					if (pbMsgData){
						if (!pbMsgData->ParseFromArray((const void*)msgProtoData.data(), body_len-2)){
								TP_LOG("error when parsing proto in msg");
								break;
						}

						// todo
						processPbMessage(pbMsgData, (TP_E_PROTOBUF_GLOBAL_MSG_TYPE)protoId);
					}


#else
				string test = "hey";

				format_back_msg("Msg", (char*)test.c_str(), test.size());

#endif
				}

				break;
			default:


				break;
		}
	}while(0);

	return NULL;
}

bool TpMainProcess::processPbMessage(Message* pbMsg, TP_E_PROTOBUF_GLOBAL_MSG_TYPE type){
	bool ret = true;
	char testlog[512] = {0};
	switch(type){
		case E_PROTO_MSG_TYPE_TESTREQUEST:
		{
			Message_vct msgProtoODataVct;
			string msgProtoOData;
			unsigned short nProtoId = (unsigned short)type;

			TestRequest	*pbIMsg;
			TestRequest pbOMsg;
			unsigned short outLen = 0;

			pbIMsg = dynamic_cast<TestRequest*>(pbMsg);

			memset(testlog, 0, 512);
			sprintf(testlog, "proto in msg: id = %d, str = %s, opt = %d", pbIMsg->id(), pbIMsg->msg().c_str(), pbIMsg->num());
			TP_LOG(testlog);

			pbOMsg.set_id(88);
			pbOMsg.set_msg("HelloWorld from protobuf  TestRequest");
			pbOMsg.set_num(66);

			if (!pbOMsg.SerializeToString(&msgProtoOData)){
				TP_LOG("error when serializing proto out msg");
				break;
			}
			memset(testlog, 0, 512);

			sprintf(testlog, "out proto msg struct size = %d  str size = %d", sizeof(pbOMsg), msgProtoOData.size());
			TP_LOG(testlog);
			msgProtoODataVct.reserve(sizeof(unsigned short) + msgProtoOData.size());

			memcpy(msgProtoODataVct.data(), &nProtoId, sizeof(unsigned short));
			memcpy(msgProtoODataVct.data() + sizeof(unsigned short), msgProtoOData.c_str(), msgProtoOData.size());
			format_back_msg("Msg", (char*)msgProtoODataVct.data(), sizeof(unsigned short) + msgProtoOData.size());

			memset(msgProtoODataVct.data(), 0, sizeof(unsigned short) + msgProtoOData.size());
			msgProtoODataVct.clear();
			delete(pbMsg);

			break;
		}
		case E_PROTO_MSG_TYPE_LM_HELLOWORLD:
		{
			Message_vct msgProtoODataVct;
			string msgProtoOData;
			unsigned short nProtoId = (unsigned short)type;

			lm::helloworld	*pbIMsg;
			lm::helloworld pbOMsg;
			unsigned short outLen = 0;

			pbIMsg = dynamic_cast<lm::helloworld*>(pbMsg);

			memset(testlog, 0, 512);
			sprintf(testlog, "proto in msg: id = %d, str = %s, opt = %d", pbIMsg->id(), pbIMsg->str().c_str(), pbIMsg->id());
			TP_LOG(testlog);

			pbOMsg.set_id(88);
			pbOMsg.set_str("HelloWorld from protobuf  lm::helloworld");
			pbOMsg.set_opt(66);

			if (!pbOMsg.SerializeToString(&msgProtoOData)){
				TP_LOG("error when serializing proto out msg");
				break;
			}
			memset(testlog, 0, 512);

			sprintf(testlog, "out proto msg struct size = %d  str size = %d", sizeof(pbOMsg), msgProtoOData.size());
			TP_LOG(testlog);
			msgProtoODataVct.reserve(sizeof(unsigned short) + msgProtoOData.size());

			memcpy(msgProtoODataVct.data(), &nProtoId, sizeof(unsigned short));
			memcpy(msgProtoODataVct.data() + sizeof(unsigned short), msgProtoOData.c_str(), msgProtoOData.size());
			format_back_msg("Msg", (char*)msgProtoODataVct.data(), sizeof(unsigned short) + msgProtoOData.size());

			memset(msgProtoODataVct.data(), 0, sizeof(unsigned short) + msgProtoOData.size());

			delete(pbMsg);
		}
			break;
		default:
			TP_LOG("process pb msg type error");
			break;
	}
	return ret;
}
