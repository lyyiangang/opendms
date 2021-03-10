#include "Pipeline.hpp"
#include <error_code.hpp>
namespace opendms
{
    Pipeline::Pipeline(const json& js){
        _face_tracker = std::make_unique<FaceTracker>(js["face_tracker"]);
        _distract = std::make_unique<Distraction>(M_PI / 6);
        _fatigue = std::make_unique<Fatigue>();
    }

    Pipeline::~Pipeline(){

    }

    const FaceData& Pipeline::GetFaceData() const{
        return _face_data;
    }

    int Pipeline::ProcessFrame(const Frame& frame){
        _face_tracker->ExtractFaceData(frame);
        _face_data = _face_tracker->GetFaceData();
        _distract->Process(frame, _face_data);
        _fatigue->Process(frame, _face_data);
        return ERROR_SUCCESS;
    }
} // namespace opendms