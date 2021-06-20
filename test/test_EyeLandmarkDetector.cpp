#include <basic/EyeLandmarkDetector.hpp>
#include <utils/common_utils.hpp>
#include <includes.hpp>
#include "test_utils.hpp"
#include <opencv2/highgui.hpp>
#include <fstream>
#include <iostream>

int main(int argn, const char** argv){
    opendms::RegistLogger();
    std::ifstream mystream("../cfg.json");
    json js;
    mystream >> js;
    std::string path;
    try{
        path = js["pipeline"]["face_tracker"]["eye_landmark_detector"]["model_path"];
        lg->info("model path:{}", path);
    }
    catch(json::exception& e){
        lg->critical("error when parse config file.messgae:{}, id:{}", e.what(), e.id);
        return 1;
    }
    cv::Mat img = cv::imread("../data/close_eyes.jpg");
    assert(!img.empty());
    cv::Mat ori_img = img.clone();
    cv::FileStorage file("../data/close_eyes.yml", cv::FileStorage::READ);
    cv::Mat face_landmark68 = file["landmarks"].mat();
    std::unique_ptr<opendms::EyeLandmarkDetector> eye_lnd_det = std::make_unique<opendms::EyeLandmarkDetector>(path);
    cv::Mat correct_face_land68;
    eye_lnd_det->Predict(img, face_landmark68, &correct_face_land68);
    std::cout<<"origin landmark:"<<face_landmark68<<std::endl;
    std::cout<<"correct landmark:"<<correct_face_land68<<std::endl;
    opendms::PlotLandmark(img, correct_face_land68);
    cv::imshow("after_correct", img);

    opendms::PlotLandmark(ori_img, face_landmark68);
    cv::imshow("ori", ori_img);
    
    cv::waitKey(0);
    return 0;
}