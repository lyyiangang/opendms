#include "visulizer.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <utils/common_utils.hpp>
#include <includes.hpp>
#include <iostream>
#include <iomanip>
namespace opendms
{
    Visulizer::Visulizer(){

    }

    Visulizer::~Visulizer(){

    }

    void Visulizer::Render(const Frame& frame, const FaceData& face_data ){
        _frame = frame;
        if(!face_data.found_face)
            return;
        cv::rectangle(_frame.img, face_data.face_bbox.rect, {0, 0, 255});
        Visulizer::DrawLandmark(_frame.img, face_data.landmark);
        cv::Vec3d pyr_deg = face_data.pyr_to_cam * 180 / M_PI;
        std::stringstream ss;
        int w = 6;
        ss << std::setprecision(3) <<"pitch:" << std::setw(w) <<pyr_deg[0]<<\
                                    " yaw:"<< std::setw(w) <<pyr_deg[1]<<\
                                    " roll:"<< std::setw(w) <<pyr_deg[2];
        cv::Point pos(0, 30);
        cv::putText(_frame.img, ss.str(), pos, cv::FONT_HERSHEY_COMPLEX, 1.0, {0, 0, 255});
        ss.str("");
        ss << "X:"<< face_data.head_rt[3]<<" Y:"<<face_data.head_rt[4]<<" Z:"<<face_data.head_rt[5];
        pos.y += 40;
        cv::putText(_frame.img, ss.str(), pos, cv::FONT_HERSHEY_COMPLEX, 1.0, {0, 0, 255});
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
        if(lnds.cols != 2){
            lnds = lnds.t();
        }
        lnds.forEach<cv::Point2f>([img](auto& pt, const int* idx){
            cv::circle(img, pt, 3, {0, 0, 255}, -1);
        });
    }
} // namespace opendms
