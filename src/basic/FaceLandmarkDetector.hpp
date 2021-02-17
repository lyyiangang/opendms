#ifndef FaceLandmarkDetector_hpp
#define FaceLandmarkDetector_hpp
#include <includes.hpp>
#include <basic/Frame.hpp>
#include <opencv2/core.hpp>
#include <mnn/include/ImageProcess.hpp>
namespace opendms
{
    class FaceLandmarkDetector{
        public:
            FaceLandmarkDetector();
            ~FaceLandmarkDetector();
    
            bool Process(const Frame& frame, const cv::Rect2f& face_box);

        private:
            void Preprocess(cv::Mat& img);
    };
} // namespace opendms

#endif