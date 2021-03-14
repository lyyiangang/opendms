#include "FrameSource.hpp"
#include <opencv2/videoio.hpp>
#include <stdexcept>
#include <fstream>
#include <iostream>

namespace opendms
{
    namespace{
        bool FileExists(const std::string& filename){
            std::ifstream s(filename);
            return s.is_open();
        }
    }
    FrameSource::FrameSource(const std::string& video_name){
        _cap.reset(new cv::VideoCapture());
        std::cout<<"loading video "<< video_name<<std::endl;
        if(!FileExists(video_name)){
            std::cout<<video_name <<" does not exists"<<std::endl;
        }
        if(!_cap->open(video_name)){
            std::cout<<"can not open "<< video_name<<std::endl;
        }
    }

    FrameSource::~FrameSource(){

    }

    Frame FrameSource::frame(){
        if(_cap->isOpened()){
            cv::Mat frame;
            bool success = _cap->read(frame);
            assert(success);
            double timestamp = _cap->get(cv::CAP_PROP_POS_MSEC);
            return Frame(frame, timestamp);
        }
        else{
            return Frame();
        }
    }    
} // namespace opendms
