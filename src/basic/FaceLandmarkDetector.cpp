#include <basic/FaceLandmarkDetector.hpp>
#include <opencv2/imgproc.hpp>
// #include <opencv2/imgcodecs.hpp>
#include <memory>
#include <iostream>
#include <utils/common_utils.hpp>
namespace opendms
{
    FaceLandmarkDetector::FaceLandmarkDetector(){
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
        std::string model_file = "../models/landmark_detector/pfld_mb1.0.mnn";
        lg->info("loading face landmark detector model {}", model_file);
        _interpreter.reset(MNN::Interpreter::createFromFile(model_file.c_str()));
        MNN::ScheduleConfig cfg;
        _session = _interpreter->createSession(cfg);
    }

    FaceLandmarkDetector::~FaceLandmarkDetector(){

    }

    bool FaceLandmarkDetector::Process(const Frame& frame, const cv::Rect2f& face_box){
        cv::Rect2f square_face_rect = Square(face_box);
        cv::Mat face_img = Crop(frame.img, square_face_rect);
        // cv::imwrite("debug.png", face_img);
        // lg->debug("target rect:{}, out_img.size:{}", square_face_rect, face_img.size);
        // std::cout<<"target rect:"<<square_face_rect<<"out_img.size:"<< face_img.size<<std::endl;
        const int net_size[2] = {112, 112};
        cv::resize(face_img, face_img, {net_size[0], net_size[1]});
        MNN::Tensor* input_ts = _interpreter->getSessionInput(_session, "input.1");
        _preprocess->convert(face_img.data, net_size[0], net_size[1], 0, input_ts);
        _interpreter->runSession(_session); 
        MNN::Tensor* lnd_output_ts = _interpreter->getSessionOutput(_session, "442");
        MNN::Tensor host_ts(lnd_output_ts, MNN::Tensor::CAFFE);
        lnd_output_ts->copyToHostTensor(&host_ts);
        cv::Mat lnd_mat(68, 2, CV_32FC1, host_ts.host<float>());
        lnd_mat.col(0) = lnd_mat.col(0) * square_face_rect.width + square_face_rect.x;
        lnd_mat.col(1) = lnd_mat.col(1) * square_face_rect.height + square_face_rect.y;
        landmark68 = lnd_mat;
        return true;
    }

    void FaceLandmarkDetector::Preprocess(cv::Mat& img){
        // cv::Mat rgb_img;
        // cv::cvtColor(img, rgb_img, cv::COLOR_BGR2RGB);
        
    }
} // namespace opendms
