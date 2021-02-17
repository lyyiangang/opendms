#include "Pipeline.hpp"

namespace opendms
{
    Pipeline::Pipeline(const json& js){
        _face_tracker.reset(new FaceTracker(js["face_tracker"]));

    }

    Pipeline::~Pipeline(){

    }

    const FaceData& Pipeline::GetFaceData() const{
        return _face_data;
    }

    bool Pipeline::ProcessFrame(const Frame& frame){
        _face_tracker->ExtractFaceData(frame);
        _face_data = _face_tracker->GetFaceData();
        return true;
    }
} // namespace opendms