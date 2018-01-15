cmake_minimum_required(VERSION 3.6)
project(UtilityCode)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp DataStructures/LinkedList.h Testing/TestDriver.h Testing/LinkedListTestDriver.h SortingAlgorithms/Sort.h Testing/SortingTestDriver.h DataStructures/Graph.h Testing/GraphTestDriver.h DataStructures/Stack.h Testing/StackTestDriver.h DataStructures/BinaryTree.h Testing/BinaryTreeTestDriver.h DataTypes/SmartPointer.h Testing/SmartPointerTestDriver.h DataStructures/Set.h DataTypes/SmartString.h Testing/SmartStringTestDriver.h DataTypes/Regex.h DataTypes/ArgEnsure.h DataStructures/Dictionary.h Testing/DictionaryTestDriver.h Testing/SetTestDriver.h)
add_executable(UtilityCode ${SOURCE_FILES})