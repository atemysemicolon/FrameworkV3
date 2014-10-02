# Add FindTBB directory to CMake's module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}")

# Execute the FindTBB macro
find_package(TBB)
# If you want FindTBB to fail if TBB is not found, use this form:
# find_package(TBB REQUIRED)


# Here goes the actual project
include_directories(${TBB_INCLUDE_DIRS})
link_directories(${TBB_LIBRARY_DIRS})



