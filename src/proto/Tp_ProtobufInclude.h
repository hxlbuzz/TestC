/*
 * TpProtobufInclude.h
 *
 *  Created on: 25 Feb, 2013
 *      Author: nick
 */

#ifndef TPPROTOBUFINCLUDE_H_
#define TPPROTOBUFINCLUDE_H_

#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include <string>
#include <stdint.h>

#include "lm.helloworld.pb.h"
#include "ProtoTest1.pb.h"

using namespace std;
using namespace google::protobuf;

typedef enum
{
	E_PROTO_MSG_TYPE_MIN,
	E_PROTO_MSG_TYPE_TESTREQUEST,
	E_PROTO_MSG_TYPE_LM_HELLOWORLD,
	E_PROTO_MSG_TYPE_TEST,

	E_PROTO_MSG_TYPE_MAX
}TP_E_PROTOBUF_GLOBAL_MSG_TYPE;

extern const string gPbMessageArray[];

extern Message *TpCreatePbMessageByName(const string &type_name);



#endif /* TPPROTOBUFINCLUDE_H_ */
