/*
 * Tp_ProtobufInclude.cpp
 *
 *  Created on: 26 Feb, 2013
 *      Author: nick
 */
#include "Tp_ProtobufInclude.h"

const string gPbMessageArray[E_PROTO_MSG_TYPE_MAX] = {
		"",
		TestRequest::descriptor()->full_name(),
		lm::helloworld::descriptor()->full_name()
};

/**
22  * @Synopsis  createMessage
23  *  根据Message Type的名字获取到对应的Message* 指针.
24  *
25  * @Param type_name Message Type的名字
26  *
27  * @Returns   Message 指针
28  */

Message *TpCreatePbMessageByName(const string &type_name) {
    Message *message = NULL;
        /// 找到一个 DescriptorPool 对象，它包含了程序编译时所链接的全部
        /// protobuf Message types; 根据 type name 查找 Descriptor .
    const Descriptor *descriptor
                = DescriptorPool::generated_pool()->FindMessageTypeByName(type_name);

    if(descriptor) {
                /// 找到 MessageFactory 对象，它能创建程序编译时所链接的全部
                /// protobuf Message types; 找到具体 Message Type 的 default instance
        const Message *prototype
                        = MessageFactory::generated_factory()->GetPrototype(descriptor);
        if(prototype) {
                        /// 创建对象
            message = prototype->New();
        }
    }
    return message;
}
