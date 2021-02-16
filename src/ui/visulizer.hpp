#ifndef visulizer_hpp
#define visulizer_hpp
#include <utils/common_utils.hpp>
#include <basic/Frame.hpp>

namespace opendms
{
    class Visulizer{
        public:
            Visulizer();
            ~Visulizer();

            void Render(const Frame& frame, const FaceData& face_data );

            bool Show(int wait_key = 1)const;
        private:
            Frame _frame;
    };
} // namespace opendms

#endif