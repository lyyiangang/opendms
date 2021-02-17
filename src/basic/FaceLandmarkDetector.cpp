#include <basic/FaceLandmarkDetector.hpp>
#include <opencv2/imgproc.hpp>
#include <memory>
namespace opendms
{
    FaceLandmarkDetector::FaceLandmarkDetector(){
        // MNN::Tensor dest_tensor;
        // float means[3] = {0, 0, 0.0};
        // float std[3] = {1.0/256, 1.0/ 256, 1.0/ 256};
        // std::unique_ptr<MNN::CV::ImageProcess> pre(
        //     MNN::CV::ImageProcess::create(MNN::CV::ImageFormat::BGR,
        //     MNN::CV::RGB, \
        //     means, \
        //     3,
        //     std, \
        //     3, \
        //     dest_tensor \
        //     )
        // );
    }

    FaceLandmarkDetector::~FaceLandmarkDetector(){

    }

    bool FaceLandmarkDetector::Process(const Frame& frame, const cv::Rect2f& face_box){
        return true;
    }

    void FaceLandmarkDetector::Preprocess(cv::Mat& img){
        cv::Mat rgb_img;
        cv::cvtColor(img, rgb_img, cv::COLOR_BGR2RGB);
        
    }
} // namespace opendms
