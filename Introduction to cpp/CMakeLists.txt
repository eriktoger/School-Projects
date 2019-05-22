# Project name
project(ertg1700_solutions)

# Minimum required cmake version
cmake_minimum_required(VERSION 3.2)

# Compile with c++ 14 support
set(CMAKE_CXX_STANDARD 14)

# Static inclusion of dependencies required for the executable to be independent
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

# Add source directories for the project
aux_source_directory(Project/src PROJECT)
aux_source_directory(Project/include PROJECT)

# Add executable
add_executable(ertg1700_solutions-PROJECT Project/src/main.cpp)
