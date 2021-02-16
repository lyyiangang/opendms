#include "FrameSource.hpp"
#include <opencv2/videoio.hpp>
#include <includes.hpp>
#include <utils/common_utils.hpp>
#include <stdexcept>

namespace opendms
{
    FrameSource::FrameSource(const std::string& video_name){
        _cap.reset(new cv::VideoCapture());
        lg->info("loading video {}", video_name);
        ASSERT(FileExists(video_name));
        if(!_cap->open(video_name)){
            lg->critical("can not open {}", video_name);
        }
    }

    FrameSource::~FrameSource(){

    }

    Frame FrameSource::frame(){
        if(_cap->isOpened()){
            cv::Mat frame;
            _cap->read(frame);
            double timestamp = _cap->get(cv::CAP_PROP_POS_MSEC);
            return Frame(frame, timestamp);
        }
        else{
            return Frame();
        }
    }    
} // namespace opendms
