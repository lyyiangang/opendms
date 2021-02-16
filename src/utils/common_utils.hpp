#ifndef common_utils_hpp
#define common_utils_hpp
#include "spdlog/spdlog.h"
#include <opencv2/core.hpp>
#include <vector>

namespace opendms
{
    struct DetBox {
        cv::Rect2f rect;
        float score = 0.0;
    };
    using Landmark68 = cv::Point2f[68];
    using Landmark68_3d = cv::Point3f[68];
    struct FaceData{
        bool found_face = false;
        DetBox face_bbox;
        Landmark68 landmark;
        Landmark68_3d landmark_3d;
        cv::Vec3f pose_pyr = {0, 0, 0};
    };

    std::shared_ptr<spdlog::logger> RegistLogger();
    //the number of faces appear could be greater than 1, just select the one close to image center
    DetBox SelectBestFace(const std::vector<DetBox>& boxes);
    bool FileExists(const std::string& filename);
} // namespace opendms

#endif 