cmake_minimum_required(VERSION 3.10.2)
project(opendms)
option(BUILD_EXAMPLE "Build example or not" ON)
option(BUILD_TEST "build tests or not" ON)
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
add_definitions(-fPIC)
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
MESSAGE("lib dir:" ${LIB_DIR})
MESSAGE("INC_DIR:" ${INC_DIR})


FILE(GLOB DMS_baisc_src src/basic/*)
FILE(GLOB DMS_utils_src src/utils/*)
set(DMS_LIB_SRC src/api.cpp ${DMS_baisc_src} ${DMS_utils_src})

include_directories(
    include/
    src/
    3rdparty/nlohmann
    3rdparty/
    ${OpenCV_INCLUDE_DIRS}
    ${INC_DIR}
)

LINK_DIRECTORIES(
    ${LIB_DIR}
)

add_library(dms SHARED ${DMS_LIB_SRC})
target_link_libraries(dms PRIVATE spdlog::spdlog ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT}  MNN)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/examples/cpp_example)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/test/)