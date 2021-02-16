#ifndef Pipline_hpp
#define Pipline_hpp
#include <includes.hpp>
#include <basic/FaceTracker.hpp>
#include <utils/common_utils.hpp>
namespace opendms
{
    class Pipeline{
        public:
            Pipeline(const json& js);
            ~Pipeline();

            bool ProcessFrame(const Frame& frame);
            const FaceData& GetFaceData()const;

        private:
            std::unique_ptr<FaceTracker> _face_tracker;
            FaceData _face_data; 
    };
} // namespace opendms

#endif 