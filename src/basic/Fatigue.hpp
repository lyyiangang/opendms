#ifndef Fatigue_hpp
#define Fatigue_hpp
#include <includes.hpp>

namespace opendms
{
    class Fatigue{
        public:
            Fatigue();
            ~Fatigue();
            //close eye? yawn? 
            bool Process(const Frame& frame, const FaceData& face_data);

            bool close_eye, yawn;
        private:
    };
} // namespace opendms

#endif