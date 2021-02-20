cmake_minimum_required(VERSION 3.6)

project(TestDrivers)

add_library(TestDriver TestDriver.cpp)
target_include_directories(TestDriver PUBLIC .)

add_library(BinaryTreeTestDriver BinaryTreeTestDriver.cpp)
target_link_libraries(BinaryTreeTestDriver PUBLIC TestDriver)
target_include_directories(BinaryTreeTestDriver PUBLIC . ..)

add_library(DictionaryTestDriver DictionaryTestDriver.cpp)
target_link_libraries(DictionaryTestDriver PUBLIC TestDriver)
target_include_directories(DictionaryTestDriver PUBLIC . ..)

add_library(GraphTestDriver GraphTestDriver.cpp)
target_link_libraries(GraphTestDriver PUBLIC TestDriver)
target_include_directories(GraphTestDriver PUBLIC . ..)

add_library(LinkedListTestDriver LinkedListTestDriver.cpp)
target_link_libraries(LinkedListTestDriver PUBLIC TestDriver)
target_include_directories(LinkedListTestDriver PUBLIC . ..)

add_library(SetTestDriver SetTestDriver.cpp)
target_link_libraries(SetTestDriver PUBLIC TestDriver)
target_include_directories(SetTestDriver PUBLIC . ..)

add_library(SmartPointerTestDriver SmartPointerTestDriver.cpp)
target_link_libraries(SmartPointerTestDriver PUBLIC TestDriver)
target_include_directories(SmartPointerTestDriver PUBLIC . ..)

add_library(SmartStringTestDriver SmartStringTestDriver.cpp)
target_link_libraries(SmartStringTestDriver PUBLIC TestDriver)
target_include_directories(SmartStringTestDriver PUBLIC . ..)

add_library(SortingTestDriver SortingTestDriver.cpp)
target_link_libraries(SortingTestDriver PUBLIC TestDriver)
target_include_directories(SortingTestDriver PUBLIC . ..)

add_library(StackTestDriver StackTestDriver.cpp)
target_link_libraries(StackTestDriver PUBLIC TestDriver)
target_include_directories(StackTestDriver PUBLIC . ..)

add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(${PROJECT_NAME} INTERFACE
    BinaryTreeTestDriver
    DictionaryTestDriver
    GraphTestDriver
    LinkedListTestDriver
    SetTestDriver
    SmartPointerTestDriver
    SmartStringTestDriver
    SortingTestDriver
    StackTestDriver
)
