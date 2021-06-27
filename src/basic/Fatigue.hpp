#ifndef Fatigue_hpp
#define Fatigue_hpp
#include <includes.hpp>
#include <utils/common_utils.hpp>
namespace opendms
{
    class Fatigue{
        public:
            Fatigue();
            ~Fatigue();
            //close eye? yawn? 
            bool Process(const Frame& frame, const FaceData& face_data);

            bool yawn;
            cv::Vec2f eye_openness;
        private:
    };
} // namespace opendms

#endif