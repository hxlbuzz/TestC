//============================================================================
// Name        : PortInErlang.cpp
// Author      : sakishum
// Version     :
// Copyright   : Your copyright notice
// Description : C++, Ansi-style
//============================================================================
#include <istream>
#include <iostream>

#include <ctime>
#include <vector>

#include <cstring>
//for linux system
//

#include "src/Tp_MainProcess.h"


using namespace std;


int main(int argc, char* argv[]) {
	TpMainProcess* _mainProcess = new TpMainProcess();
	byte answer[4] = {'n','e','x','t'};//请求下一条指令
	byte data[G_MAX_MSG_BUFF_LENGTH] = {0};
	int  read_len = 0;

    TP_LOG("It works!!");
	while(read_cmd(data, &read_len) > 0){

		do{
//			char data[1024] = {0};
			char* pOut = NULL;
			static int counter = 100;
			unsigned short len = 0;

			TP_LOG("read len = %d", read_len);

			len = (data[0] << 8) | data[1];
			if (len <= 2){// todo min len
				//
				TP_LOG("error total msg len = %d", len);
				break;
			}
			//获取到了头部,后继续获取消息

			TP_LOG("len = %d ,data: %x, %x, %x, %x, %x, %x, %x, %x, %x", len, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8]);

			if ((len < G_MAX_MSG_BUFF_LENGTH - 2) && len > 0)
				pOut = _mainProcess->process_msg_in((char *)(data + 2), len);

			memset(data, 0, G_MAX_MSG_BUFF_LENGTH);
			write_cmd(answer, 4);

		}while(0);
	}

	TP_LOG("I'm not supposed to be here, you gonna find out why!!");

	return 0;
//	string command;
//	while ( cin >> command&& command != "d0.com.cn:exit:!!")
//	{
//		cout<< _mainProcess->msg_in(command) <<endl;
//	}
//	return 0;
}
