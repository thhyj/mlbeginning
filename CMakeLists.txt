cmake_minimum_required(VERSION 3.14)
project(mlbeginning)

set(CMAKE_CXX_STANDARD 14)

add_executable(mlbeginning
        main.cpp)
set(OpenCV_DIR D:\\opencv\\mingw-build2\\install)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(mlbeginning ${OpenCV_LIBS})