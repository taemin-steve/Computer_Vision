cmake_minimum_required(VERSION 3.0.0)
project(Top)

# OpenCV 4.7.0
set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/third_party/opencv/build)
set(OpenCV_STATIC_LIB  ${OpenCV_DIR}/x64/vc16/lib/opencv_world470.lib)
set(OpenCV_DYNAMIC_LIB ${OpenCV_DIR}/x64/vc16/bin/opencv_world470.dll)
include_directories(${OpenCV_DIR}/include)

# Data
set(DATA_DIR ${CMAKE_SOURCE_DIR}/data)

# Projects
add_subdirectory("${CMAKE_SOURCE_DIR}/project/01_hello_opencv")
add_subdirectory("${CMAKE_SOURCE_DIR}/project/02_images")
add_subdirectory("${CMAKE_SOURCE_DIR}/project/03_videos_and_cameras")