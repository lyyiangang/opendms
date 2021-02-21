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
    struct FaceData{
        bool found_face = false;
        DetBox face_bbox;
        cv::Mat landmark;
        cv::Mat landmark_3d;
        cv::Vec3f pose_pyr = {0, 0, 0};
    };

    std::shared_ptr<spdlog::logger> RegistLogger();
    
    //the number of faces appear could be greater than 1, just select the one close to image center
    DetBox SelectBestFace(const std::vector<DetBox>& boxes);

    bool FileExists(const std::string& filename);

    cv::Mat Crop(const cv::Mat& img, const cv::Rect& rect);

    cv::Rect2f Square(const cv::Rect2f& rect);

    static inline cv::Point2f operator +(const cv::Point2f pt, float val){
        cv::Point2f new_pt = pt;
        new_pt.x += val;
        new_pt.y += val;
        return new_pt; 
    }

    static inline cv::Point2f operator -(const cv::Point2f& pt, float val){
        cv::Point2f new_pt = pt;
        new_pt.x -= val;
        new_pt.y -= val;
        return new_pt; 
    }

} // namespace opendms

#endif 