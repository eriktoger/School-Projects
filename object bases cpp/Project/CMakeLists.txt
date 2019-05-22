# Project name
project(Project)

# Minimum required cmake version
cmake_minimum_required(VERSION 3.2)

# Compile with c++ 11 support
set(CMAKE_CXX_STANDARD 11)

# Static inclusion of dependencies required for the executable to be independent
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static  -Wall -Wextra -Wshadow -pedantic")

# Save name of directories in variables for reuse
set(PROJECT "Project")

# Add source directories for the project
aux_source_directory(src SRC)

add_executable(${PROJECT_NAME}_${PROJECT} ${SRC})

#adding the include to my main
target_include_directories(${PROJECT_NAME}_${PROJECT} PRIVATE "include")