#include "test_utils.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

namespace opendms{
    void PlotLandmark(cv::Mat& img, const cv::Mat& landmarks, bool plot_idx){
        
        cv::Mat lnds = landmarks.clone();
        lnds.convertTo(lnds, CV_32SC1);
        for(int ii = 0; ii < lnds.rows; ++ii){
            cv::Point pt = lnds.at<cv::Point>(ii);
            cv::circle(img, pt, 2, {0, 0, 255}, -1);
            if(plot_idx){
                cv::putText(img, std::to_string(ii), pt, cv::FONT_HERSHEY_SIMPLEX, 0.3, {255, 0, 0}, 1);
            }
        }
    }
}