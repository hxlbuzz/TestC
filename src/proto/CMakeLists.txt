#用直接链接静态库的方法
#include_directories("/usr/local/include/google/protobuf/descrptor.h")

AUX_SOURCE_DIRECTORY(. DIR_PROTO_SRCS)

ADD_LIBRARY(Proto ${DIR_PROTO_SRCS})

#target_link_libraries(Proto ${PROTOBUF_LIBRARY})
#target_link_libraries(Proto /usr/local/lib/libprotoc.a)
