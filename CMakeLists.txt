cmake_minimum_required(VERSION 3.6)

project(UtilityCode)
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES Testing/AllTests.cpp DataStructures/LinkedList.h TestDrivers/TestDriver.h TestDrivers/LinkedListTestDriver.h SortingAlgorithms/Sort.h TestDrivers/SortingTestDriver.h DataStructures/Graph.h TestDrivers/GraphTestDriver.h DataStructures/Stack.h TestDrivers/StackTestDriver.h DataStructures/BinaryTree.h TestDrivers/BinaryTreeTestDriver.h DataTypes/SmartPointer.h TestDrivers/SmartPointerTestDriver.h DataStructures/Set.h DataTypes/SmartString.h TestDrivers/SmartStringTestDriver.h DataTypes/Regex.h DataTypes/ArgEnsure.h DataStructures/Dictionary.h TestDrivers/DictionaryTestDriver.h TestDrivers/SetTestDriver.h)
add_executable(AllTests ${SOURCE_FILES})

project(BinaryTree)
set(CMAKE_CXX_STANDARD 11)
add_executable(BinaryTree Testing/BinaryTreeTests.cpp DataStructures/BinaryTree.h TestDrivers/TestDriver.h TestDrivers/BinaryTreeTestDriver.h)

project(Dictionary)
set(CMAKE_CXX_STANDARD 11)
add_executable(Dictionary Testing/DictionaryTests.cpp DataStructures/Dictionary.h TestDrivers/TestDriver.h TestDrivers/DictionaryTestDriver.h)

project(Graph)
set(CMAKE_CXX_STANDARD 11)
add_executable(Graph Testing/GraphTests.cpp DataStructures/Graph.h TestDrivers/TestDriver.h TestDrivers/GraphTestDriver.h)

project(LinkedList)
set(CMAKE_CXX_STANDARD 11)
add_executable(LinkedList Testing/LinkedListTests.cpp DataStructures/LinkedList.h TestDrivers/TestDriver.h TestDrivers/LinkedListTestDriver.h)

project(Set)
set(CMAKE_CXX_STANDARD 11)
add_executable(Set Testing/SetTests.cpp DataStructures/Set.h TestDrivers/TestDriver.h TestDrivers/SetTestDriver.h)

project(Stack)
set(CMAKE_CXX_STANDARD 11)
add_executable(Stack Testing/StackTests.cpp DataStructures/Stack.h TestDrivers/TestDriver.h TestDrivers/StackTestDriver.h)

project(Sorting)
set(CMAKE_CXX_STANDARD 11)
add_executable(Sorting Testing/SortingTests.cpp SortingAlgorithms/Sort.h TestDrivers/TestDriver.h TestDrivers/SortingTestDriver.h)

project(SmartPointer)
set(CMAKE_CXX_STANDARD 11)
add_executable(SmartPointer Testing/SmartPointerTests.cpp DataTypes/SmartPointer.h TestDrivers/TestDriver.h TestDrivers/SmartPointerTestDriver.h)

project(SmartString)
set(CMAKE_CXX_STANDARD 11)
add_executable(SmartString Testing/SmartStringTests.cpp DataTypes/SmartString.h TestDrivers/TestDriver.h TestDrivers/SmartStringTestDriver.h)