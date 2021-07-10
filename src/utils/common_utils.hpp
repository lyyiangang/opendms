#ifndef common_utils_hpp
#define common_utils_hpp
#include "spdlog/spdlog.h"
#include <opencv2/core.hpp>
#include <vector>
#include <deque>
#include <FaceData.hpp>
namespace opendms
{
    std::shared_ptr<spdlog::logger> RegistLogger();
    
    //the number of faces appear could be greater than 1, just select the one close to image center
    DetBox SelectBestFace(const std::vector<DetBox>& boxes);

    bool FileExists(const std::string& filename);

    cv::Mat Crop(const cv::Mat& img, const cv::Rect& rect);

    cv::Rect2f Square(const cv::Rect2f& rect);

    cv::Mat NormFaceLandmark68();

    cv::Mat DefaultIntrinsicMat(const cv::Size& frame_size);

    cv::Mat Estimate3dLandmark(const cv::Mat& lnd_2d, const cv::Mat& template_face_mat, cv::Vec6d* landmark_3d,
        const cv::Mat& intrinsic = cv::Mat(), const cv::Mat& dist_coefs = cv::Mat());
    
    template <typename T>
    T Clamp(T input, T min, T max){
        if(input > max)
            return max;
        else if (input < min)
            return min;
        else
            return input;
    }

    // convert mili sec unit to sec
    static inline float Sec(double start_timestamp, double end_timestamp){return (end_timestamp - start_timestamp) * 1e-3;};

    static inline float Sec(double timestamp){return timestamp * 1e-3;}
    
    static inline cv::Point2f operator +(const cv::Point2f pt, float val){
        cv::Point2f new_pt = pt;
        new_pt.x += val;
        new_pt.y += val;
        return new_pt; 
    }

    static inline cv::Point2f operator -(const cv::Point2f& pt, float val){
        cv::Point2f new_pt = pt;
        new_pt.x -= val;
        new_pt.y -= val;
        return new_pt; 
    }


    class TimeSeries{
        public:
            TimeSeries();
            ~TimeSeries();

            void AddFrameData(double time, float val);

            bool AverageValueInTimeslice(float timeslice_sec, float* mean_val);

        private:
            struct TData{
                double timestamp;
                float val;
                TData(double t, float v):timestamp(t), val(v){}
            };
            std::deque<TData> _q;

    };
} // namespace opendms

#endif 