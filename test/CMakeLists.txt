cmake_minimum_required(VERSION 2.8)
PROJECT(server)
ADD_EXECUTABLE(server server.c)
INCLUDE_DIRECTORIES(/usr/include)
TARGET_LINK_LIBRARIES(server zmq)
#INSTALL(PROGRAMS  DESTINATION bin)

