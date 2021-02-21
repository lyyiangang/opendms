#include "visulizer.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <utils/common_utils.hpp>
#include <includes.hpp>
namespace opendms
{
    Visulizer::Visulizer(){

    }

    Visulizer::~Visulizer(){

    }

    void Visulizer::Render(const Frame& frame, const FaceData& face_data ){
        _frame = frame;
        cv::rectangle(_frame.img, face_data.face_bbox.rect, {0, 0, 255});
        Visulizer::DrawLandmark(_frame.img, face_data.landmark);
    }
    
    bool Visulizer::Show(int wait_key)const{
        cv::imshow("opendms", _frame.img);
        int key = cv::waitKey(wait_key);
        if(key == 'q'){
            return true;
        }
        return false;
    }
    void Visulizer::DrawLandmark(cv::Mat& img, const cv::Mat& landmarks){
        cv::Mat lnds = landmarks;
        lnds.convertTo(lnds, CV_32SC2);
        if(lnds.rows != 2){
            lnds = lnds.t();
        }
        lnds.forEach<cv::Point>([img](cv::Point& pt, const int* idx){
            cv::circle(img, pt, 3, {0, 0, 255}, -1);
        });

    }
} // namespace opendms
