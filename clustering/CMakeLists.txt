#COMMON
project(clustering)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
set(SRC_LIST_WITHOUT_MAIN ${SRC_LIST})
list(REMOVE_ITEM SRC_LIST_WITHOUT_MAIN ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#OpenCV
find_package( OpenCV REQUIRED )
#ENDCOMMON


# Add FindTBB directory to CMake's module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}")
# Execute the FindTBB macro
find_package(TBB)
# If you want FindTBB to fail if TBB is not found, use this form:
# find_package(TBB REQUIRED)
# Here goes the actual project
include_directories(${TBB_INCLUDE_DIRS})
link_directories(${TBB_LIBRARY_DIRS})
## Add  search path to get annotation handler
set(LABEL_DIR_INCLUDE /home/prassanna/Development/workspace/frameworkV3/Labels /home/prassanna/Development/workspace/frameworkV3/features2D)
set(LABEL_DIR_LINK /home/prassanna/Development/workspace/frameworkV3/builds/Labels /home/prassanna/Development/workspace/frameworkV3/builds/features2d)
include_directories(${LABEL_DIR_INCLUDE})
link_directories(${LABEL_DIR_LINK})


#CREATING the Library
set(LIBRARY_NAME clustering_superpixels)

#COMMON
add_library(
    ${LIBRARY_NAME}
    SHARED
    ${SRC_LIST_WITHOUT_MAIN}
    ${INCLUDE_FILES}
)
add_executable(${PROJECT_NAME} ${SRC_LIST})
#ENDCOMMON

target_link_libraries(
    ${LIBRARY_NAME}
    ${OpenCV_LIBS}
    labelManager
    featureManager
)

#COMMON
target_link_libraries( ${PROJECT_NAME} ${LIBRARY_NAME})
#EndCOMMON




