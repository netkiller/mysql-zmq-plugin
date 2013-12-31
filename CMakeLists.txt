cmake_minimum_required(VERSION 2.8)
PROJECT(zeromq)
ADD_LIBRARY(zeromq SHARED zeromq.c)
INCLUDE_DIRECTORIES(/usr/include/mysql)
TARGET_LINK_LIBRARIES(zeromq zmq)
INSTALL(PROGRAMS libzeromq.so DESTINATION /usr/lib/mysql/plugin/)

