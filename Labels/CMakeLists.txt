project(Labels)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#OpenCV
find_package( OpenCV REQUIRED )
aux_source_directory(. SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})


set(LIBRARY_NAME labelManager)
set(SRC_LIST_WITHOUT_MAIN ${SRC_LIST})
list(REMOVE_ITEM SRC_LIST_WITHOUT_MAIN ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
add_library(
    ${LIBRARY_NAME}
    SHARED
    ${SRC_LIST_WITHOUT_MAIN}
    ${INCLUDE_FILES}
)

target_link_libraries(
    ${LIBRARY_NAME}
    ${OpenCV_LIBS}
)

target_link_libraries( ${PROJECT_NAME} ${LIBRARY_NAME})
