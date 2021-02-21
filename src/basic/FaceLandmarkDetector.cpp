#include <basic/FaceLandmarkDetector.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
// #include <opencv2/imgcodecs.hpp>
#include <memory>
#include <iostream>
#include <utils/common_utils.hpp>
namespace opendms
{
    FaceLandmarkDetector::FaceLandmarkDetector(const std::string& model_file){
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
        
        // estimate 3d face
        landmark68_3d = Estimate3dLandmark(lnd_mat, NormFaceLandmark68(), &head_rt, DefaultIntrinsicMat(frame.img.size()));
        cv::Mat rmat;
        cv::Rodrigues(cv::Mat(3, 1, CV_64FC1, head_rt.val), rmat);
        cv::Mat mtxR, mtxQ;
        pyr_to_cam = cv::RQDecomp3x3(rmat, mtxR, mtxQ) * M_PI / 180.0;//get head pose
        return true;
    }

    void FaceLandmarkDetector::Preprocess(cv::Mat& img){
        // cv::Mat rgb_img;
        // cv::cvtColor(img, rgb_img, cv::COLOR_BGR2RGB);
        
    }
} // namespace opendms
