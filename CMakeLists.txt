cmake_minimum_required(VERSION 3.0.0)
# project info
set(projectName udpsocksDemo)
set(_version_ 0.0.2)

project(${projectName} VERSION ${_version_})

find_package(OpenCV REQUIRED)

include(cmake/utils.cmake)

if(WIN32)
set(CMAKE_CXX_FLAGS "/utf-8 /EHsc /std:c++latest")
else()
set(CMAKE_CXX_FLAGS "-std=c++17 -pthread")
endif(WIN32)

# 生成对应项目名字的in文件
configure_file(${CMAKE_SOURCE_DIR}/cmake/config.hpp.in 
                    ${CMAKE_SOURCE_DIR}/cmake/buildConfig.hpp.in)
configure_file(${CMAKE_SOURCE_DIR}/cmake/buildConfig.hpp.in 
                    ${CMAKE_SOURCE_DIR}/include/config.hpp @ONLY)

#include
include_directories(include
                    ${OpenCV_INCLUDE_DIRS})
# include cpp
file(GLOB includeSources "./include/*.cpp")
#cpp file
add_executable(server ./src/Server.cpp  ${includeSources})
add_executable(client ./src/Client.cpp  ${includeSources})
target_link_libraries(server ${OpenCV_LIBS})
target_link_libraries(client ${OpenCV_LIBS})

# 如果是win系统则复制dll到项目下
if(WIN32)
string(REPLACE lib "bin" OpenCV_DLL ${OpenCV_LIB_PATH})
copyFiles(server "${OpenCV_DLL}/*.dll")
copyFiles(client "${OpenCV_DLL}/*.dll")
endif(WIN32)