cmake_minimum_required(VERSION 3.27)
project(SA)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        src/main.cpp
        include/TSP.cpp
        include/DataIO.cpp
)

add_executable(SA ${SOURCES})

target_include_directories(SA
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)


