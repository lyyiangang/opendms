#ifndef FaceTracker_hpp
#define FaceTracker_hpp
#include <includes.hpp>
#include <basic/FaceLandmarkDetector.hpp>
#include <basic/FaceDetector.hpp>
#include <utils/common_utils.hpp>
#include <memory>

namespace opendms{
    class FaceTracker{
    public:
        FaceTracker(const json& j);
        ~FaceTracker();

        bool ExtractFaceData(const Frame& frame);

        const FaceData& GetFaceData()const;

    private:
        std::unique_ptr<FaceDetector> _face_detector;
        std::unique_ptr<FaceLandmarkDetector> _face_lnd_detector;
        FaceData _face_data;

    };
}


#endif 