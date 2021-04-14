#ifndef EyeLandmarkDetecotr_hpp
#define EyeLandmarkDetecotr_hpp
#include <opencv2/core.hpp>
#include <string>
#include <vector>
#include <MNN/ImageProcess.hpp>
#include <MNN/Interpreter.hpp>

namespace opendms{
    class EyeLandmarkDetector{
        public:
            EyeLandmarkDetector(const std::string& model_path);
            ~EyeLandmarkDetector();

            bool Predict(cv::Mat whole_img, const cv::Mat& face_landmark_68, cv::Mat* corrected_face_landmarks);

        private:
            std::unique_ptr<MNN::CV::ImageProcess> _preprocess;
            std::unique_ptr<MNN::Interpreter> _interpreter;
            MNN::Session* _session;
    };
}
#endif