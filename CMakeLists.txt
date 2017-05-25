cmake_minimum_required(VERSION 3.6)
project(UtilityCode)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES SearchAlgorithms/AStar.cpp SearchAlgorithms/AStar.h SearchAlgorithms/Heuristics.h SearchAlgorithms/Heuristics.cpp SearchAlgorithms/Coordinates.h DataStructures/LinkedList.h main.cpp Testing/TestDriver.h Testing/LinkedListTestDriver.h)
add_executable(UtilityCode ${SOURCE_FILES})