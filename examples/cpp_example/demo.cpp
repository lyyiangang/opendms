#include <api.hpp>
#include <fstream>
#include <iostream>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <includes.hpp>
#include "visulizer.hpp"
#include <error_code.hpp>
using namespace opendms;

int main(int argc, char** argv){
    DMS dms;
    std::string cfg_file = "../cfg.json";
    int ret = dms.init(cfg_file);
    if(ret != 0){
        std::cout<<"Error, can not init dms lib. error code:"<<ret <<std::endl;
        return 1;
    }
    if(argc <2){
        std::cout<<"Error. you should set 1 input argument.e.g. demo.out ../data/test.mp4\n";
        return 1;
    }
    std::string video_file = argv[1];
    cv::VideoCapture cap(video_file);
    if(!cap.isOpened()){
        std::cout<<"can not open video "<<video_file<<std::endl;
        return 1;
    }
    Visulizer vis;
    while(1){
        cv::Mat img;
        bool success = cap.read(img);
        if(!success){
            std::cout<<" can not extract frame from file"<<std::endl;
            break;
        }
        double timestamp = cap.get(cv::CAP_PROP_POS_MSEC);
        Frame frame(img, timestamp);
        FaceData face_data;
        int error = dms.ProcessOneFrame(frame, &face_data);
        if(error != ERROR_SUCCESS){
            std::cout<<"Error occur in process, code:"<<error<<std::endl;
            break;
        }
        vis.Render(frame, face_data);
        vis.Show();
        int key = cv::waitKey(1);
        if(key == 'q'){
            break;
        }
    };
    return 0;
}