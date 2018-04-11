# ------------------------------------------------------------
#  libdacs1500
#
#  auotmatically build and install
#  ~/src
# ------------------------------------------------------------


# set include directories
include_directories(${PROJECT_SOURCE_DIR}/include)


# set ALL COMPLE OPTIONS
set(CMAKE_C_FLAGS "-Wall -O3 -Werror -m32")
set(CMAKE_CXX_FLAGS "-Wall -O3 -Werror -m32")


# generate and install libdacs1500 static library
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/src)
add_library(libdacs1500Static STATIC libdacs1500.c)
set_target_properties(libdacs1500Static PROPERTIES OUTPUT_NAME libdacs1500)
install(TARGETS libdacs1500Static DESTINATION lib)


# generate and install libdacs1500 shared library
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/src)
add_library(libdacs1500Shared SHARED libdacs1500.c)
set_target_properties(libdacs1500Shared PROPERTIES OUTPUT_NAME libdacs1500)
install(TARGETS libdacs1500Shared DESTINATION lib)
