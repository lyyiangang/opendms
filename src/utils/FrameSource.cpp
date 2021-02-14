#include "FrameSource.hpp"
#include <opencv2/videoio.hpp>
#include <includes.hpp>
#include <stdexcept>

namespace opendms
{
    FrameSource::FrameSource(const std::string& video_name){
        _cap.reset(new cv::VideoCapture());
        lg->info("loading video {}", video_name);
        if(!_cap->open(video_name)){
            lg->critical("can not open {}", video_name);
        }
    }

    FrameSource::~FrameSource(){

    }

    cv::Mat FrameSource::frame(){
        if(!_cap->isOpened()){
            throw std::runtime_error("can not get frame");
        }
        else{
            cv::Mat frame;
            _cap->read(frame);
            return frame;
        }
    }    
} // namespace opendms
