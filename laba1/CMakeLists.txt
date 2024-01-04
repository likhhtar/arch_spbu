cmake_minimum_required(VERSION 3.16)

set(X_PROJECT_NAME lab-1_numbers)
set(COMMON_SOURCES main.cpp functions.cpp functions.h)

project(${X_PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror)

set(MAIN_SOURCES main.cpp ${COMMON_SOURCES})

add_executable(${X_PROJECT_NAME} ${MAIN_SOURCES})
target_include_directories(${X_PROJECT_NAME} PRIVATE include)
