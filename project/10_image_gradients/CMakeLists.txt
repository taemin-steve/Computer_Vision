cmake_minimum_required(VERSION 3.0.0)

# Sub-Projects
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/10_01_prewitt_filter")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/10_02_sobel_filter")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/10_03_sobel_filter_dtype")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/10_04_prewitt_sobel_scharr_filters")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/10_05_laplace_filter")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/10_06_canny_edge_detection_video")