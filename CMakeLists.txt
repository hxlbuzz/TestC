PROJECT(cPlusPlugin)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
ADD_SUBDIRECTORY(src)
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
ADD_EXECUTABLE(cPlusPlugin ${DIR_SRCS})
TARGET_LINK_LIBRARIES(cPlusPlugin MainProcess)
##add from github
#change again
#once again
##test 
