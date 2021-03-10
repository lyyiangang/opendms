#include "Fatigue.hpp"

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
        return true;
    }
} 
