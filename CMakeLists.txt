cmake_minimum_required(VERSION 3.0.0) # 버전 쓰세요 
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
add_subdirectory("${CMAKE_SOURCE_DIR}/project/04_drawing")
add_subdirectory("${CMAKE_SOURCE_DIR}/project/05_user_interface")
add_subdirectory("${CMAKE_SOURCE_DIR}/project/06_image_histogram")
add_subdirectory("${CMAKE_SOURCE_DIR}/project/07_image_thresholding")
add_subdirectory("${CMAKE_SOURCE_DIR}/project/08_image_blending")
add_subdirectory("${CMAKE_SOURCE_DIR}/project/09_image_blurring")
add_subdirectory("${CMAKE_SOURCE_DIR}/project/10_image_gradients")
add_subdirectory("${CMAKE_SOURCE_DIR}/project/81_homework_01") 
add_subdirectory("${CMAKE_SOURCE_DIR}/project/정태민_2018204059_HW_02")
