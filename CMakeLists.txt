cmake_minimum_required(VERSION 3.16)
project(projekt_studia LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(projekt_studia src/main.cpp
        src/Date.cpp
        src/CalendarRenderer.cpp
)
target_include_directories(projekt_studia PRIVATE include)