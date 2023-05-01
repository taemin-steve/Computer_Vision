cmake_minimum_required(VERSION 3.0.0)

# Sub-Projects
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/11_01_erosion")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/11_02_dilation")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/11_03_structuring_element")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/11_04_structuring_element_erosion")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/11_05_structuring_element_dilation")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/11_06_morphological_transformations")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/11_07_morphological_transformations_color")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/11_08_hit_or_miss")