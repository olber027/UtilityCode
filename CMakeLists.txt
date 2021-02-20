cmake_minimum_required(VERSION 3.6)

project(UtilityCode)
set(CMAKE_CXX_STANDARD 17)

set(DATA_STRUCTURES ${CMAKE_SOURCE_DIR}/DataStructures)
set(DATA_TYPES ${CMAKE_SOURCE_DIR}/DataTypes)
set(SORTING_ALGORITHMS ${CMAKE_SOURCE_DIR}/SortingAlgorithms)
set(TEST_DRIVERS ${CMAKE_SOURCE_DIR}/TestDrivers)

add_subdirectory(DataStructures)
add_subdirectory(DataTypes)
add_subdirectory(SortingAlgorithms)
add_subdirectory(TestDrivers)
add_subdirectory(Testing)