cmake_minimum_required(VERSION 3.10.2)

project(opendms)

SET(CMAKE_CXX_FLAGS "-std=c++14 -Wall -O3 -fPIC")
find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED)
find_package(spdlog REQUIRED)
MESSAGE( " *** OpenCV_INCLUDE_DIRS : " ${OpenCV_INCLUDE_DIRS} )
MESSAGE( " *** OpenCV_LIB_DIRS : " ${OpenCV_LIB_DIRS} )
MESSAGE( " *** OpenCV_LIBS : " ${OpenCV_LIBS} )
SET(SOURCES
#   ${CMAKE_CURRENT_SOURCE_DIR}/test/test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/test_spdlog.cpp
)

LINK_DIRECTORIES(
  ${OpenCV_LIB_DIR}
)

add_executable(demo ${SOURCES})
target_include_directories(demo PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(demo PRIVATE  ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT} spdlog::spdlog)
