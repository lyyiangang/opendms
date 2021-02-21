#ifndef FaceLandmarkDetector_hpp
#define FaceLandmarkDetector_hpp
#include <includes.hpp>
#include <basic/Frame.hpp>
#include <opencv2/core.hpp>
#include <MNN/ImageProcess.hpp>
#include <MNN/Interpreter.hpp>
#include <utils/common_utils.hpp>

#include <memory>
namespace opendms
{
    class FaceLandmarkDetector{
        public:
            FaceLandmarkDetector();
            ~FaceLandmarkDetector();
    
            bool Process(const Frame& frame, const cv::Rect2f& face_box);

            cv::Mat landmark68;

        private:
            void Preprocess(cv::Mat& img);
            std::unique_ptr<MNN::CV::ImageProcess> _preprocess;
            std::unique_ptr<MNN::Interpreter> _interpreter;
            MNN::Session* _session;
    };
} // namespace opendms

#endif