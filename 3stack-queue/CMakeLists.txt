cmake_minimum_required(VERSION 3.17)
project(C__)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(C__
        linkedstack.h
        main.cpp
        priority_queue.h
        seqqueue.h
        seqstack.h
        template_seqqueue.h)
