cmake_minimum_required(VERSION 3.8)
project(src)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES
        include/Key.h
        include/ParameterK.h
        include/Value.h
        main.cpp
        include/BalancedTreeK.h BalancedTreeK.cpp include/Node.h include/Leaf.h include/InternalNode.h)

include_directories(include)

add_executable(src ${SOURCE_FILES})