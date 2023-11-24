cmake_minimum_required(VERSION 3.10)
project(Gaussian_Blur_CPP)

set(CMAKE_CXX_STANDARD 17)

include_directories(includes)
include_directories(third-party/libpng)

file(GLOB SOURCES "src/*.cpp")

add_executable(Gaussian_Blur_CPP ${SOURCES})

find_package(ZLIB REQUIRED)

include_directories(${ZLIB_INCLUDE_DIRS})
target_link_libraries(Gaussian_Blur_CPP ${CMAKE_SOURCE_DIR}/third-party/libpng/build/libpng.a ${ZLIB_LIBRARIES})