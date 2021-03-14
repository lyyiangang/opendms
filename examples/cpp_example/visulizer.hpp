#ifndef visulizer_hpp
#define visulizer_hpp
#include <FaceData.hpp>
#include <Frame.hpp>

namespace opendms
{
    class Visulizer{
        public:
            Visulizer();
            ~Visulizer();

            void Render(const Frame& frame, const FaceData& face_data );

            void Show()const;

            static void DrawLandmark(cv::Mat& img, const cv::Mat& landmarks);
        private:
            Frame _frame;
    };
} // namespace opendms

#endif