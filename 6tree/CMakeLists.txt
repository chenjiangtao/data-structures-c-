cmake_minimum_required(VERSION 3.17)
project(C__)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(C__
        binarytree.h
        bst.h
        heap.h
        huffmantree.h
        main.cpp)
