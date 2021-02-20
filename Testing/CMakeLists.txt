cmake_minimum_required(VERSION 3.6)

project(Testing CXX)

add_executable(AllTests AllTests.cpp)
target_include_directories(AllTests PUBLIC
        ${CMAKE_SOURCE_DIR}/DataStructures
        ${CMAKE_SOURCE_DIR}/DataTypes
        ${CMAKE_SOURCE_DIR}/SortingAlgorithms
        ${CMAKE_SOURCE_DIR}/TestDrivers
)
target_link_libraries(AllTests PUBLIC TestDrivers)
set_target_properties(AllTests PROPERTIES LINKER_LANGUAGE CXX)

add_executable(BinaryTreeTests BinaryTreeTests.cpp)
target_link_libraries(BinaryTreeTests PUBLIC BinaryTreeTestDriver)
target_include_directories(BinaryTreeTests PUBLIC .)
set_target_properties(BinaryTreeTests PROPERTIES LINKER_LANGUAGE CXX)

add_executable(DictionaryTests DictionaryTests.cpp)
target_link_libraries(DictionaryTests PUBLIC DictionaryTestDriver)
target_include_directories(DictionaryTests PUBLIC .)
set_target_properties(DictionaryTests PROPERTIES LINKER_LANGUAGE CXX)

add_executable(GraphTests GraphTests.cpp)
target_link_libraries(GraphTests PUBLIC GraphTestDriver)
target_include_directories(GraphTests PUBLIC .)
set_target_properties(GraphTests PROPERTIES LINKER_LANGUAGE CXX)

add_executable(LinkedListTests LinkedListTests.cpp)
target_link_libraries(LinkedListTests PUBLIC LinkedListTestDriver)
target_include_directories(LinkedListTests PUBLIC .)
set_target_properties(LinkedListTests PROPERTIES LINKER_LANGUAGE CXX)

add_executable(SetTests SetTests.cpp)
target_link_libraries(SetTests PUBLIC SetTestDriver)
target_include_directories(SetTests PUBLIC .)
set_target_properties(SetTests PROPERTIES LINKER_LANGUAGE CXX)

add_executable(SmartPointerTests SmartPointerTests.cpp)
target_link_libraries(SmartPointerTests PUBLIC SmartPointerTestDriver)
target_include_directories(SmartPointerTests PUBLIC .)
set_target_properties(SmartPointerTests PROPERTIES LINKER_LANGUAGE CXX)

add_executable(SmartStringTests SmartStringTests.cpp)
target_link_libraries(SmartStringTests PUBLIC SmartStringTestDriver)
target_include_directories(SmartStringTests PUBLIC .)
set_target_properties(SmartStringTests PROPERTIES LINKER_LANGUAGE CXX)

add_executable(SortingTests SortingTests.cpp)
target_link_libraries(SortingTests PUBLIC SortingTestDriver)
target_include_directories(SortingTests PUBLIC .)
set_target_properties(SortingTests PROPERTIES LINKER_LANGUAGE CXX)

add_executable(StackTests StackTests.cpp)
target_link_libraries(StackTests PUBLIC StackTestDriver)
target_include_directories(StackTests PUBLIC .)
set_target_properties(StackTests PROPERTIES LINKER_LANGUAGE CXX)