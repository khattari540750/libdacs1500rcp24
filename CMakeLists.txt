# ------------------------------------------------------------
#  Root CMake file for libdacs1500rcp24
#
#    From the off-tree build directory, invoke:
#      $ cmake <PATH_TO_SSM_ROOT>
#
# ------------------------------------------------------------


# Project setting
cmake_minimum_required(VERSION 2.4 FATAL_ERROR)
project(dacs1500rcp24)


# Project version number
set(VERSION_NUMBER_MAJOR 0)
set(VERSION_NUMBER_MINOR 0)
set(VERSION_NUMBER_MICRO 0)


# configure a header file to pass some of the CMake settings
# to the source code
#configure_file(
#  "${PROJECT_SOURCE_DIR}/config.h.in"
#  "${PROJECT_SOURCE_DIR}/config.h"
#)


# find packages
#find_package(Threads)


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_BUILD_TYPE Release)


include_directories(/usr/local/include)
link_directories(/usr/local/lib)


add_executable(test src/main.cpp src/Dio.cpp)
target_link_libraries(test ftd2xx)

#add_executable(test src/main.cpp src/dacs1500rcp24.c)
#target_link_libraries(test ftd2xx)
