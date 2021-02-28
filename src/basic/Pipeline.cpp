#include "Pipeline.hpp"

namespace opendms
{
    Pipeline::Pipeline(const json& js){
        _face_tracker = std::make_unique<FaceTracker>(js["face_tracker"]);
        _distract = std::make_unique<Distraction>(M_PI / 6);
    }

    Pipeline::~Pipeline(){

    }

    const FaceData& Pipeline::GetFaceData() const{
        return _face_data;
    }

    bool Pipeline::ProcessFrame(const Frame& frame){
        _face_tracker->ExtractFaceData(frame);
        _face_data = _face_tracker->GetFaceData();
        if(!_face_data.found_face)
            return false;
        _distract->Process(frame, _face_data);
        // std::cout<<"pip "<<_face_data.head_rt;
        return true;
    }
} // namespace opendms