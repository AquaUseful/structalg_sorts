cmake_minimum_required(VERSION 3.0.0)

project(strutalgs_sorts VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

add_subdirectory(ui)
add_subdirectory(main)
add_subdirectory(sorts)
add_subdirectory(test)
add_subdirectory(timer)
