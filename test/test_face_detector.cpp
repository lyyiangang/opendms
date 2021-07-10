//  Created by Linzaer on 2019/11/15.
//  Copyright © 2019 Linzaer. All rights reserved.

#include <basic/FaceDetector.hpp>
#include <utils/common_utils.hpp>
#include <includes.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>

int main(int argc, char **argv) {
    opendms::RegistLogger();
    std::ifstream mystream("../cfg.json");
    json js;
    mystream >> js;
    std::string path;
    try{
        path = js["pipeline"]["face_tracker"]["face_detector"]["model_path"];
        lg->info("model path:{}", path);
    }
    catch(json::exception& e){
        lg->critical("error when parse config file.messgae:{}, id:{}", e.what(), e.id);
        return 1;
    }
    opendms::FaceDetector ultraface(path, 320, 240, 4, 0.65); // config model input
    cv::Mat test_img = cv::imread("../data/1.jpg");
    std::vector<opendms::DetBox> det_results;
    int ret = ultraface.detect(test_img, det_results);
    ASSERT(ret == 0);
    lg->info("find {} faces on this image", det_results.size());
    for(auto result : det_results){
        cv::rectangle(test_img, result.rect, cv::Scalar(0, 255, 0), 2);
    }
    std::string output_file = "face_det_results.png";
    lg->info("writing det result to {}", output_file);
    cv::imwrite(output_file, test_img);
    return 0;
}
