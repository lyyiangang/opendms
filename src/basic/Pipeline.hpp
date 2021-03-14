#ifndef Pipline_hpp
#define Pipline_hpp
#include <includes.hpp>
#include <basic/FaceTracker.hpp>
#include <basic/Distraction.hpp>
#include <basic/Fatigue.hpp>
#include <utils/common_utils.hpp>

namespace opendms
{
    class Pipeline{
        public:
            Pipeline(const json& js);
            ~Pipeline();

            int ProcessFrame(const Frame& frame);
            const FaceData& GetFaceData()const;

        private:
            std::unique_ptr<FaceTracker> _face_tracker;
            std::unique_ptr<Distraction> _distract;
            std::unique_ptr<Fatigue> _fatigue;
            FaceData _face_data; 
    };
} // namespace opendms

#endif 