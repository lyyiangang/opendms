#ifndef FaceTracker_hpp
#define FaceTracker_hpp
#include <includes.hpp>
#include "FaceDetector.hpp"
#include <memory>

namespace opendms{
    class FaceTracker{
    public:
        FaceTracker(const json& j);
        ~FaceTracker();

    private:
        std::unique_ptr<FaceDetector> _face_detector;
    };
}


#endif 