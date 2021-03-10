#ifndef api_hpp
#define api_hpp
#include <string>

#include "FaceData.hpp"
#include "Frame.hpp"

namespace opendms
{
    class DMS{
        public:
            DMS();
            ~DMS();

            int init(const std::string& cfg_file);

            int ProcessOneFrame(const Frame& frame, FaceData* face_result);

        private:
    };
} // opendms 

#endif