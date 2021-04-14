#include "test_utils.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

namespace opendms{
    void PlotLandmark(cv::Mat& img, const cv::Mat& landmarks){
        
        cv::Mat lnds;
        landmarks.convertTo(lnds, CV_32SC1);
        for(int ii = 0; ii < lnds.rows; ++ii){
            cv::Point pt = lnds.at<cv::Point>(ii);
            cv::circle(img, pt, 2, {0, 0, 255}, -1);
        }
    }
}