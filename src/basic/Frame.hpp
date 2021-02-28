#ifndef Frame_hpp
#define Frame_hpp
#include <opencv2/core.hpp>
namespace opendms{
    class Frame{
        public:
            Frame():timestamp(0){
            }

            Frame(const cv::Mat& img, double timestamp):img(img), timestamp(timestamp)
            {
            }
            Frame& operator=(const Frame& f){
                this->img = f.img;
                this->timestamp = f.timestamp;
                return *this;
            }
            cv::Mat img;
            double timestamp;//mili sec
    };
}
#endif 