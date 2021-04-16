#ifndef test_utils_hpp
#define test_utils_hpp
#include <opencv2/highgui.hpp>

namespace opendms{

    void PlotLandmark(cv::Mat& img, const cv::Mat& landmarks, bool plot_idx = false);
}
#endif