#include "Fatigue.hpp"
#include <iostream>
namespace opendms
{
    Fatigue::Fatigue():yawn(false)
    {
        eye_openness = {1, 1};
    }

    Fatigue::~Fatigue()
    {
    }

    bool Fatigue::Process(const Frame& frame, const FaceData& face_data){
        yawn = false;
        eye_openness = {1, 1};
        cv::Mat landmarks = face_data.landmark;
        if(face_data.found_face)
        {
            //yawn?     
            float width = cv::norm(landmarks.row(48) - landmarks.row(54));
            float height = cv::norm(landmarks.row(66) - landmarks.row(62));
            if(height / width > 0.4){
                yawn = true;
            }
            // close eye? 
            for(int ii = 0; ii <2; ++ii )
            {
                cv::Vec2i corner_idx={36, 39};
                cv::Vec2i up_idx = {37, 38};
                cv::Vec2i down_idx = {41, 40};
                if(ii == 1){
                    corner_idx = {42, 45};
                    up_idx = {43, 44};
                    down_idx = {47, 46};
                }
                width = cv::norm(landmarks.row(corner_idx[0]) - landmarks.row(corner_idx[1]));
                height = cv::norm((landmarks.row(up_idx[0]) + landmarks.row(up_idx[1])) / 2 , \
                    (landmarks.row(down_idx[0]) + landmarks.row(down_idx[1])) / 2);
                lg->debug("left eye height:{}", height);
                if(width > 1e-3)
                    eye_openness[ii] = height / width;
            }
        }
        return true;
    }
} 
