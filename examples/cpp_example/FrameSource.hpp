#ifndef FrameSource_hpp
#define FrameSource_hpp

#include <string>
#include <memory>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <Frame.hpp>
namespace opendms
{
    class FrameSource{
        public:
            FrameSource(const std::string& video_name);
            ~FrameSource();

            Frame frame();

            FrameSource() = delete;
            FrameSource(const FrameSource&) = delete;

        private:
            std::unique_ptr<cv::VideoCapture> _cap;
    };
} // namespace opendms

#endif 