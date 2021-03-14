#ifndef FaceData_hpp
#define FaceData_hpp
#include <opencv2/core.hpp>

namespace opendms{
    struct DetBox {
        cv::Rect2f rect;
        float score = 0.0;
    };
    struct FaceData{
        bool found_face = false;
        DetBox face_bbox;
        cv::Mat landmark;
        cv::Mat landmark_3d;
        cv::Vec6d head_rt; // head rotation vector and translation vector
        cv::Vec3d pyr_to_cam; // head pose in radius. pitch, yaw, roll order

        bool distract = false;
    };
}
#endif 