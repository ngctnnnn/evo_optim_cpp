cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(optim-cpp)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS} ${OPENCV_CXX_FLAGS} -DFFMPEG=OFF -DWITH_OPENCL=1 -pthread -Wall -I/Users/ngctnnnn/Documents/Research/optim_cpp/include/optim/header_only_version -I/Users/ngctnnnn/Documents/Research/optim_cpp/include/eigen")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FILE(GLOB_RECURSE sourcefiles "src/main.cpp")
FILE(GLOB_RECURSE headerfiles "src/*.h")

set(CMAKE_CXX_STANDARD 17)

add_executable(main ${sourcefiles} ${headerfiles})

target_link_libraries(main)

set_property(TARGET main PROPERTY CXX_STANDARD 17)