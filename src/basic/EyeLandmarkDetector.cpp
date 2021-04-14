#include "EyeLandmarkDetector.hpp"
#include <utils/common_utils.hpp>
#include <opencv2/imgproc.hpp>
#include <includes.hpp>

namespace opendms{
    EyeLandmarkDetector::EyeLandmarkDetector(const std::string& model_path){
        float means[3] = {0, 0, 0.0};
        float std[3] = {1.0/256, 1.0/ 256, 1.0/ 256};
        _preprocess.reset(
            MNN::CV::ImageProcess::create(MNN::CV::ImageFormat::BGR,
            MNN::CV::RGB, \
            means, \
            3, \
            std, \
            3)
        );
        lg->info("loading eye landmark detector model {}", model_path);
        _interpreter.reset(MNN::Interpreter::createFromFile(model_path.c_str()));
        MNN::ScheduleConfig cfg;
        _session = _interpreter->createSession(cfg);
    }

    EyeLandmarkDetector::~EyeLandmarkDetector(){

    }
    bool EyeLandmarkDetector::Predict(cv::Mat whole_img, \
                                        const cv::Mat& face_landmark_68, cv::Mat* corrected_face_landmarks){
        ASSERT(face_landmark_68.rows == 68);
        // left eye inner & outter corners, and right eye inner & outter corners
        std::vector<cv::Vec2i> eye_corner_idx = {
            {42, 45},
            {39, 36}
        };
        const int net_size[2] = {112, 112};
        *corrected_face_landmarks = face_landmark_68.clone();
        cv::Point2f pupil_centers[2];
        for(int ii = 0; ii < 2; ++ii){
            cv::Vec2i idx = eye_corner_idx[ii];
            cv::Point2f inner = face_landmark_68.at<cv::Point2f>(idx[0]);
            cv::Point2f outter = face_landmark_68.at<cv::Point2f>(idx[1]);
            cv::Point2f center = (inner + outter) / 2;
            float w = cv::norm(inner - outter) * 1.5;
            cv::Rect roi_rect(center.x - w /2 , center.y - w / 2, w, w);
            cv::Mat eye_img = Crop(whole_img, roi_rect);
            cv::resize(eye_img, eye_img, {net_size[0], net_size[1]});
            if(ii == 1){
                cv::flip(eye_img, eye_img, 1);
            }

            MNN::Tensor* input_ts = _interpreter->getSessionInput(_session, "input.1");
            _preprocess->convert(eye_img.data, net_size[0], net_size[1], 0, input_ts);
            _interpreter->runSession(_session); 
            MNN::Tensor* lnd_output_ts = _interpreter->getSessionOutput(_session, "86");
            MNN::Tensor host_ts(lnd_output_ts, MNN::Tensor::CAFFE);
            lnd_output_ts->copyToHostTensor(&host_ts);
            cv::Mat lnd_mat(7, 2, CV_32FC1, host_ts.host<float>());
            if(ii == 1){
                lnd_mat.col(0) = 1.0 - lnd_mat.col(0);
                lnd_mat.col(0) = lnd_mat.col(0) * w + roi_rect.x;
                lnd_mat.col(1) = lnd_mat.col(1) * w + roi_rect.y;
                std::vector<int> map_idx = {39, 38, 37, 36, 41, 40};
                for(int idx = 0; idx < map_idx.size(); ++idx){
                    corrected_face_landmarks->row(map_idx[idx]) = lnd_mat.row(idx);
                }
            }
            else{
                lnd_mat.col(0) = lnd_mat.col(0) * w + roi_rect.x;
                lnd_mat.col(1) = lnd_mat.col(1) * w + roi_rect.y;
                std::vector<int> map_idx = {42, 43, 44, 45, 46, 47};
                for(int idx = 0; idx < map_idx.size(); ++idx){
                    corrected_face_landmarks->row(map_idx[idx]) = lnd_mat.row(idx);
                }

            }
            pupil_centers[ii] = {lnd_mat.at<float>(6, 0), lnd_mat.at<float>(6, 1)};
        }
        return true;
    }
}