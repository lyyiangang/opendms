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
        cv::Vec6d head_rt; // head rotation vector and translation vector
        cv::Vec3d pyr_to_cam; // head pose in radius. pitch, yaw, roll order
    };

    std::shared_ptr<spdlog::logger> RegistLogger();
    
    //the number of faces appear could be greater than 1, just select the one close to image center
    DetBox SelectBestFace(const std::vector<DetBox>& boxes);

    bool FileExists(const std::string& filename);

    cv::Mat Crop(const cv::Mat& img, const cv::Rect& rect);

    cv::Rect2f Square(const cv::Rect2f& rect);

    cv::Mat NormFaceLandmark68();

    cv::Mat DefaultIntrinsicMat(const cv::Size& frame_size);

    cv::Mat Estimate3dLandmark(const cv::Mat& lnd_2d, const cv::Mat& template_face_mat, cv::Vec6d* landmark_3d,
        const cv::Mat& intrinsic = cv::Mat(), const cv::Mat& dist_coefs = cv::Mat());

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