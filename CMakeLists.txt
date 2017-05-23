cmake_minimum_required(VERSION 3.6)
project(UtilityCode)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES AStar.cpp AStar.h Heuristics.h Heuristics.cpp Coordinates.h LinkedList.h)
add_library(UtilityCode SHARED ${SOURCE_FILES})