#用寻找的方法, 这种方法需要在cmake时加上 --help-module FindProtobuf
include(FindProtobuf)
find_package(Protobuf REQUIRED)

#MESSAGE 这个指令用于向终端输出用户定义的信息，包含了三种类型
#   SEND_ERROR，产生错误，生成过程被跳过
#   SATUS, 输出前缀为-的信息
#   FATAL_ERROR,立即终止所有cmake过程

IF(PROTOBUF_FOUND)

    MESSAGE(STATUS, "proto found")
    MESSAGE(STATUS, "proto library ", ${PROTOBUF_LIBRARY})
    MESSAGE(STATUS, "proto dir ", ${PROTOBUF_INCLUDE_DIR})
    include_directories(${PROTOBUF_INCLUDE_DIR})
    include_directories(${CMAKE_CURRENT_BINARY_DIR})

    AUX_SOURCE_DIRECTORY(. DIR_MAINPROCESS_SRCS)
    ADD_SUBDIRECTORY(proto)
    ADD_SUBDIRECTORY(common)
    ADD_LIBRARY(MainProcess ${DIR_MAINPROCESS_SRCS})
    TARGET_LINK_LIBRARIES(MainProcess Proto Common ${PROTOBUF_LIBRARY})

ELSE(PROTOBUF_FOUND)
    MESSAGE(FATAL_ERROR "protobuf not found")
ENDIF(PROTOBUF_FOUND)
