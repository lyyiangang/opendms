#include "FaceTracker.hpp"
#include <memory>

namespace opendms{
    FaceTracker::FaceTracker(const json& j){
        _face_detector = std::make_unique<FaceDetector>(j["face_detector"]["model_path"], \
            320, 240, 4, j["face_detector"]["score_threshold"]);
    } 

    FaceTracker::~FaceTracker(){

    }

    bool FaceTracker::ExtractFaceData(const Frame& frame){
        std::vector<DetBox> face_boxes;
        _face_detector->detect(frame.img, face_boxes);
        if(face_boxes.empty()){
            _face_data.found_face = false;
        }
        else{
            _face_data.found_face = true;
            _face_data.face_bbox = SelectBestFace(face_boxes);
        }
        return true;
    }
    const FaceData& FaceTracker::GetFaceData()const{
        return _face_data;
    }
}