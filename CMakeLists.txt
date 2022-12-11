cmake_minimum_required(VERSION 3.24)

project(2cpp)
set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp)

#include_directories(/usr/include)
#link_directories(/usr/lib)
#target_link_libraries(untitled sqlite3)

#project (untitled)
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "C:/sqlite")
#add_executable(untitled main.cpp)
#find_package (SQLite3)

#if (SQLITE3_FOUND)
#    include_directories(${SQLITE3_INCLUDE_DIRS})
#    target_link_libraries (tutorial ${SQLITE3_LIBRARIES})
#endif (SQLITE3_FOUND)