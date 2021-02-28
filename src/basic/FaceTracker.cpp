#include "FaceTracker.hpp"
#include <memory>

namespace opendms{
    FaceTracker::FaceTracker(const json& j){
        _face_detector = std::make_unique<FaceDetector>(j["face_detector"]["model_path"], \
            320, 240, 4, j["face_detector"]["score_threshold"]);
        _face_lnd_detector = std::make_unique<FaceLandmarkDetector>(j["face_landmark_detector"]["model_path"]);
    } 

    FaceTracker::~FaceTracker(){

    }

    bool FaceTracker::ExtractFaceData(const Frame& frame){
        std::vector<DetBox> face_boxes;
        _face_detector->detect(frame.img, face_boxes);
        if(face_boxes.empty()){
            _face_data.found_face = false;
            return false;
        }
        _face_data.found_face = true;
        _face_data.face_bbox = SelectBestFace(face_boxes);
        _face_lnd_detector->Process(frame, _face_data.face_bbox.rect);
        _face_data.landmark = _face_lnd_detector->landmark68;
        _face_data.landmark_3d = _face_lnd_detector->landmark68_3d;
        _face_data.head_rt = _face_lnd_detector->head_rt;
        _face_data.pyr_to_cam = _face_lnd_detector->pyr_to_cam;
        return true;
    }

    const FaceData& FaceTracker::GetFaceData()const{
        return _face_data;
    }
}