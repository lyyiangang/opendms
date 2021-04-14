IF(BUILD_TEST)
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../)
    MESSAGE("build tests---.")
    add_executable(face_landmark_test test_faceLandmarkDetector.cpp test_utils.cpp )
    target_link_libraries(face_landmark_test PRIVATE spdlog::spdlog ${OpenCV_LIBS}   MNN dms)

ENDIF()