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
            FaceLandmarkDetector(const std::string& model_file);
            ~FaceLandmarkDetector();
    
            bool Process(const Frame& frame, const cv::Rect2f& face_box);

            cv::Mat landmark68, landmark68_3d;
            cv::Vec6d head_rt; // head_rt[:3]: rotation vector, head_rt[-3:]: translation vec
            cv::Vec3d pyr_to_cam; // head pose to camera coordinate system

        private:
            void Preprocess(cv::Mat& img);
            std::unique_ptr<MNN::CV::ImageProcess> _preprocess;
            std::unique_ptr<MNN::Interpreter> _interpreter;
            MNN::Session* _session;
    };
} // namespace opendms

#endif