#include <includes.hpp>
#include <utils/common_utils.hpp>
#include <utils/FrameSource.hpp>
#include <fstream>
#include <opencv2/highgui.hpp>
using namespace opendms;

int main(int arc, char** argv){
    RegistLogger();
    FrameSource frame_source("../p_data/rgb_640x480.avi");
    while(1){
        cv::Mat frame = frame_source.frame();
        if(frame.empty()){
            break;
        }
        cv::imshow("img", frame);
        cv::waitKey(1);
    }
    lg->info("hello");
    lg->debug("debug info");
    std::string cfg_file = "../cfg.json";
    lg->info("reading config file from {}", cfg_file);
    std::ifstream f_stream(cfg_file);
    json j;
    f_stream >> j;
    lg->info("config file content:{}", j.dump(4));
    // lg->info("detector:{}", j["face_detector"]["model_path"]);

    return 0;
}