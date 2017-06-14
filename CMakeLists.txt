cmake_minimum_required(VERSION 3.6)
project(UtilityCode)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_HEADERS SearchAlgorithms/AStar.h SearchAlgorithms/Heuristics.h SearchAlgorithms/Coordinates.h DataStructures/LinkedList.h Testing/TestDriver.h Testing/LinkedListTestDriver.h SortingAlgorithms/Sort.h)
set(SOURCE_FILES main.cpp SearchAlgorithms/AStar.cpp SearchAlgorithms/Heuristics.cpp Testing/SortingTestDriver.h DataStructures/Graph.h DataStructures/VertexType.h Testing/GraphTestDriver.h)
add_executable(UtilityCode ${SOURCE_FILES})