cmake_minimum_required(VERSION 3.10.2)
project(opendms)
message(STATUS "\tProcessor: ${PLATFORM}")
IF(PLATFORM MATCHES "^aarch64")
    message("build for aarch64")
    set(CMAKE_C_COMPILER /gcc-linaro-7.5.0-2019.12-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc)
    set(CMAKE_CXX_COMPILER /gcc-linaro-7.5.0-2019.12-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-g++)
ENDIF()

# SET(CMAKE_CXX_FLAGS "-Wall -O3 -fPIC")
SET(CMAKE_CXX_FLAGS "-Wall -O0 -g3 -fPIC")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
find_package(Threads REQUIRED)
IF(PLATFORM MATCHES "^aarch64")
    find_package (spdlog REQUIRED PATHS /install_aarch64/)
    find_package(OpenCV REQUIRED PATHS /install_aarch64/)
    set(LIB_DIR /install_aarch64/lib)
    set(INC_DIR /install_aarch64/include)
ELSE()
    find_package (spdlog REQUIRED PATHS /install_x86/)
    find_package(OpenCV REQUIRED PATHS /install_x86/)
    set(LIB_DIR /install_x86/lib)
    set(INC_DIR /install_x86/include)
ENDIF()

MESSAGE( " *** OpenCV_INCLUDE_DIRS : " ${OpenCV_INCLUDE_DIRS} )
MESSAGE( " *** OpenCV_LIBS : " ${OpenCV_LIBS} )
MESSAGE("lib dir:", ${LIB_DIR})

SET(TEST_SRC 
    src/basic/FaceDetector.cpp
    # test/test_face_detector.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/test/test.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/test/test_logger.cpp

)

FILE(GLOB DMS_baisc_src src/basic/*)
FILE(GLOB DMS_utils_src src/utils/*)
FILE(GLOB DMS_ui_src src/ui/*)
set(DMS_LIB_SRC ${DMS_baisc_src} ${DMS_utils_src})
set(DMS_EXTRA_SRC ${DMS_ui_src})

include_directories(
    src/
    3rdparty/nlohmann
    3rdparty/
    ${OpenCV_INCLUDE_DIRS}
    ${INC_DIR}/MNN
    ${INC_DIR}/spdlog
)

LINK_DIRECTORIES(
    ${LIB_DIR}
)
# MESSAGE("source files:", ${DMS_LIB_SRC}, ${DMS_EXTRA_SRC})
add_executable(demo ${DMS_LIB_SRC} ${DMS_EXTRA_SRC} src/main.cpp)
# target_include_directories(demo PRIVATE )
target_link_libraries(demo PRIVATE  ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT} spdlog::spdlog MNN)
