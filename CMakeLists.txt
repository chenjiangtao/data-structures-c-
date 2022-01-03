cmake_minimum_required(VERSION 3.17)
project(data_structures_cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(21)
include_directories(22)
include_directories(23)
include_directories(2list)
include_directories(3stack-queue)
include_directories(4string)
include_directories(6tree)
include_directories(7graph)
include_directories(8search)
include_directories(9sort)

add_executable(data_structures_cpp
        21/linkedlist.h
        21/main.cpp
        22/binarytree.h
        22/bst.h
        22/main.cpp
        23/main.cpp
        23/template_seqqueue.h
        2list/circlelist.h
        2list/linkedlist.h
        2list/main.cpp
        2list/polyn.h
        2list/seqlist.h
        3stack-queue/linkedstack.h
        3stack-queue/main.cpp
        3stack-queue/priority_queue.h
        3stack-queue/seqqueue.h
        3stack-queue/seqstack.h
        3stack-queue/template_seqqueue.h
        4string/hstring.h
        4string/main.cpp
        4string/sstring.h
        6tree/binarytree.h
        6tree/bst.h
        6tree/heap.h
        6tree/huffmantree.h
        6tree/main.cpp
        7graph/graph.h
        7graph/main.cpp
        8search/AVLTree.cpp
        8search/AVLTree.h
        8search/bst.h
        8search/main.cpp
        8search/seqlist.h
        9sort/main.cpp
        9sort/recordlist.h
        main.cpp)
