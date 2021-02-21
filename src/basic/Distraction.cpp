#include "Distraction.hpp"
#include <algorithm>
namespace opendms
{
    Distraction::Distraction(float warn_angle_threshold):
        _threshold(warn_angle_threshold),
        is_distract(false){
    }

    Distraction::~Distraction(){

    }

    bool Distraction::Process(const Frame& frame, const FaceData& face_data){
        cv::Vec3f pyr_deg =face_data.pyr_to_cam * 180 / M_PI;
        is_distract = false;
        if(std::abs(pyr_deg[1]) > _threshold){
            is_distract = true;
        }
        return true;
    }

}