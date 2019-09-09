# Project name
project(Project)

# Minimum required cmake version
cmake_minimum_required(VERSION 3.2)

# Compile with c++ 11 support
set(CMAKE_CXX_STANDARD 11)

# Static inclusion of dependencies required for the executable to be independent
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static  -Wall -Wextra -Wshadow -pedantic")

# add the newSrc folder
aux_source_directory(src SRC)

add_executable(${PROJECT_NAME} ${SRC} src/main.cpp)

#adding the include to my main
target_include_directories(${PROJECT_NAME} PRIVATE "include")