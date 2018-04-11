# ------------------------------------------------------------
#  libdacs1500 CMake file
#
#    auotmatically build
#  ~/sample
# ------------------------------------------------------------


# set include and link directory
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/src)


# set ALL COMPLE OPTIONS
set(CMAKE_C_FLAGS "-Wall -g -m32")
set(CMAKE_CXX_FLAGS "-Wall -g -m32")


# generated test-ms
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/sample)
add_executable(test test.c)
target_link_libraries (test ${CMAKE_THREAD_LIBS_INIT} libdacs1500)
