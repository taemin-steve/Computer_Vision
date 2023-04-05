cmake_minimum_required(VERSION 3.0.0)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_LIST_DIR} NAME) #이름 긁어와서 프러젝트 명으로 해줘 
string(REPLACE " " "_" PROJECT_NAME ${PROJECT_NAME})
project(${PROJECT_NAME} C CXX)#프로젝트 이름으로 하겠다~~

set (CMAKE_CXX_STANDARD 11)
 
add_executable(${PROJECT_NAME} main.cpp) #exectuable을 만들때 main.cpp를 봐라~ >> 컴파일해~
target_link_libraries(${PROJECT_NAME} ${OpenCV_STATIC_LIB}) #링크를 어디다랑 할 것인가. 

configure_file(${DATA_DIR}/unequalized.jpg ${CMAKE_CURRENT_BINARY_DIR} COPYONLY) #넣을 이미지 바꿔줘야햐~
configure_file(${OpenCV_DYNAMIC_LIB} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

## 이거 어디기억할수 있게 맨 위로 보내는게 좋을거같은데 
