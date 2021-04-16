#include <basic/FaceLandmarkDetector.hpp>
#include <utils/common_utils.hpp>
#include "test_utils.hpp"
#include <includes.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <fstream>
#include <iostream>

int main(int argc, char** argv){
    opendms::RegistLogger();
    std::ifstream mystream("../cfg.json");
    json js;
    mystream >> js;
    std::string path;
    try{
        path = js["pipeline"]["face_tracker"]["face_landmark_detector"]["model_path"];
        lg->info("model path:{}", path);
    }
    catch(json::exception& e){
        lg->critical("error when parse config file.messgae:{}, id:{}", e.what(), e.id);
        return 1;
    }
    opendms::FaceLandmarkDetector detector(path);
    // std::string file_name = "../data/4.jpg";
    // cv::Rect face_bbox(cv::Point(181, 100), cv::Point(357, 240));
    std::string file_name = "../data/close_eyes.jpg";
    cv::Rect face_bbox(cv::Point(121, 28), cv::Point(344, 280));
    lg->info("face landmark detector model path:{}, reading {}", path, file_name);
    cv::Mat img = cv::imread(file_name);

    opendms::Frame frame(img);
    bool success = detector.Process(frame, face_bbox);
    ASSERT(success);
    cv::rectangle(img, face_bbox, {0, 0, 255}, 1);
    opendms::PlotLandmark(img, detector.landmark68, true);
    // std::string save_file = "../data/4.yml";
    std::string save_file = "../data/close_eyes.yml";
    std::cout<<"saving landmark to "<<save_file<<std::endl;
    cv::FileStorage file(save_file, cv::FileStorage::WRITE);
    file << "landmarks" << detector.landmark68;
    cv::imshow("img", img);
    cv::waitKey(0);
    return 0;
}