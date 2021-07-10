IF(BUILD_TEST)
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../)
    MESSAGE("build tests---.")

    add_executable(test_func test.cpp test_utils.cpp)
    target_link_libraries(test_func PRIVATE spdlog::spdlog ${OpenCV_LIBS}   MNN dms)

    add_executable(face_detector_test test_face_detector.cpp test_utils.cpp )
    target_link_libraries(face_detector_test PRIVATE spdlog::spdlog ${OpenCV_LIBS}   MNN dms)

    add_executable(face_landmark_test test_faceLandmarkDetector.cpp test_utils.cpp )
    target_link_libraries(face_landmark_test PRIVATE spdlog::spdlog ${OpenCV_LIBS}   MNN dms)

    add_executable(eye_landmark_test test_EyeLandmarkDetector.cpp test_utils.cpp )
    target_link_libraries(eye_landmark_test PRIVATE spdlog::spdlog ${OpenCV_LIBS}   MNN dms)

ENDIF()