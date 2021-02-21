#ifndef Didstraction_hpp
#define Didstraction_hpp
#include <includes.hpp>
#include <utils/common_utils.hpp>

namespace opendms
{
    class Distraction{
        public:
            Distraction(float warn_angle_threshold);
            ~Distraction();

            bool Process(const Frame& frame, const FaceData& face_data);

            bool is_distract;
        private:
            float _threshold;
    };
} // namespace opendms

#endif