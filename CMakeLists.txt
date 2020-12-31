cmake_minimum_required(VERSION 3.10)
project(DirectGrav VERSION 0.1 LANGUAGES C)

include_directories(include)

set(SOURCES "src/main.c")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O3 -Wall -Werror")

add_executable(directgrav ${SOURCES})
target_link_libraries(directgrav PUBLIC m)

