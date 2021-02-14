#ifndef Pipline_hpp
#define Pipline_hpp
#include <includes.hpp>

namespace opendms
{
    class Pipeline{
        public:
            Pipeline(const json& js);
            ~Pipeline();

            bool ProcessFrame();

        private:
    };
} // namespace opendms

#endif 