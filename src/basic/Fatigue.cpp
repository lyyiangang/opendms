#include "Fatigue.hpp"
#include <iostream>
namespace opendms
{
    Fatigue::Fatigue():close_eye(false),
        yawn(false)
    {
    }

    Fatigue::~Fatigue()
    {
    }

    bool Fatigue::Process(const Frame& frame, const FaceData& face_data){
        close_eye = false;
        yawn = false;
        if(face_data.found_face)
        {
            float width = cv::norm(face_data.landmark.row(48) - face_data.landmark.row(54));
            float height = cv::norm(face_data.landmark.row(66) - face_data.landmark.row(62));
            float openness = height / width;
            // lg->debug("openness:{}", openness);
            if(openness > 0.4){
                yawn = true;
            }
        }
        return true;
    }
} 
