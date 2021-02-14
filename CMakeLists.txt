cmake_minimum_required(VERSION 3.10.2)
project(opendms)

SET(CMAKE_CXX_FLAGS "-std=c++14 -Wall -O3 -fPIC")
find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED)
find_package(spdlog REQUIRED)
MESSAGE( " *** OpenCV_INCLUDE_DIRS : " ${OpenCV_INCLUDE_DIRS} )
MESSAGE( " *** OpenCV_LIB_DIRS : " ${OpenCV_LIB_DIRS} )
MESSAGE( " *** OpenCV_LIBS : " ${OpenCV_LIBS} )

SET(TEST_SRC 
    src/basic/FaceDetector.cpp
    # test/test_face_detector.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/test/test.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/test/test_logger.cpp

)

FILE(GLOB DMS_baisc_src src/basic/*)
FILE(GLOB DMS_utils_src src/utils/*)
set(DMS_LIB_SRC ${DMS_baisc_src} ${DMS_utils_src})
message("lib src: ", ${DMS_LIB_SRC})

INCLUDE_DIRECTORIES(
    src
    ${OpenCV_INCLUDE_DIRS}
    3rdparty/nlohmann
    3rdparty/mnn/include
)

LINK_DIRECTORIES(
  ${OpenCV_LIB_DIRS}
  3rdparty/mnn/lib
)

add_executable(demo ${DMS_LIB_SRC} src/main.cpp)
target_include_directories(demo PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(demo PRIVATE  ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT} spdlog::spdlog MNN)

# add_executable(test.out ${TEST_SRC})
# target_include_directories(test.out PRIVATE ${OpenCV_INCLUDE_DIRS})
# target_link_libraries(test.out PRIVATE  ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT} spdlog::spdlog MNN)