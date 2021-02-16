#include "visulizer.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
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
    }
    
    bool Visulizer::Show(int wait_key)const{
        cv::imshow("opendms", _frame.img);
        int key = cv::waitKey(wait_key);
        if(key == 'q'){
            return true;
        }
        return false;
    }
} // namespace opendms
