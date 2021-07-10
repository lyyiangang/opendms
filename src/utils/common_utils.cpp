#include "common_utils.hpp"
#include <includes.hpp>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/cfg/env.h"
#include <fstream>
#include <memory>
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>
namespace opendms
{
    std::shared_ptr<spdlog::logger> RegistLogger(){
        // export SPDLOG_LEVEL=info
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("log.txt", true);
        std::vector<spdlog::sink_ptr> sinks {console_sink, file_sink};
        auto logger= std::make_shared<spdlog::logger>("opendms",sinks.begin(), sinks.end());
        spdlog::register_logger(logger);
        logger->set_level(spdlog::level::info); // set default log level
        spdlog::cfg::load_env_levels();
        return logger;
    }

    DetBox SelectBestFace(const std::vector<DetBox>& boxes){
        auto it = std::max_element(boxes.begin(), boxes.end(), [](auto& b1, auto& b2){
            return b1.rect.area() < b2.rect.area();
        });
        return *it;
    }

    bool FileExists(const std::string& filename){
        std::ifstream s(filename);
        return s.is_open();
    }

    cv::Mat Crop(const cv::Mat& img, const cv::Rect& rect){
        int w = img.cols;
        int h = img.rows;
        // cv::Rect img_rect(0, 0, w, h);
        // if(!img_rect.contains(rect.tl()) && !img_rect.contains(rect.br()))
        //     return cv::Mat();
        int start_y = Clamp(rect.tl().y, 0, h - 1);
        int end_y = Clamp(rect.br().y, 0, h -1);
        int start_x = Clamp(rect.tl().x, 0, w - 1);
        int end_x = Clamp(rect.br().x, 0, w - 1);
        cv::Mat sub_img = img(cv::Range(start_y, end_y), cv::Range(start_x, end_x));
        cv::Mat target(rect.height, rect.width, img.type());
        int top = rect.tl().y >= 0 ? 0 : -1 * rect.tl().y;
        int bottom = rect.br().y > (h - 1) ? (rect.br().y - (h - 1)) : 0;
        int left = rect.tl().x >= 0 ? 0 : -1 * rect.tl().x;
        int right = rect.br().x > ( w - 1) ? (rect.br().x - ( w - 1)) : 0;
        cv::copyMakeBorder(sub_img, target, top, bottom, left, right, cv::BORDER_CONSTANT);
        return target; 
    }

    cv::Rect2f Square(const cv::Rect2f& rect){
        cv::Point2f ctx = (rect.tl() + rect.br()) * 0.5;
        float size = std::max(rect.width, rect.height);
        cv::Point2f tl = ctx - size / 2;
        cv::Point2f br = ctx + size / 2;
        return cv::Rect2f(tl, br);
    }

    cv::Mat NormFaceLandmark68(){
        // https://github.com/yinguobing/image_utility.git
        cv::Mat lnd = (cv::Mat_<float>(68, 3) << \
        -73.3935 ,-29.8014 ,-47.6675, \
        -72.7750 ,-10.9498 ,-45.9094, \
        -70.5336 ,7.9298 ,-44.8426, \
        -66.8501 ,26.0743 ,-43.1411, \
        -59.7902 ,42.5644 ,-38.6353, \
        -48.3690 ,56.4811 ,-30.7506, \
        -34.1211 ,67.2470 ,-18.4565, \
        -17.8754 ,75.0569 ,-3.6090, \
        0.0987 ,77.0613 ,0.8817, \
        17.4770 ,74.7584 ,-5.1812, \
        32.6490 ,66.9290 ,-19.1766, \
        46.3724 ,56.3114 ,-30.7706, \
        57.3435 ,42.4191 ,-37.6286, \
        64.3885 ,25.4559 ,-40.8863, \
        68.2120 ,6.9908 ,-42.2814, \
        70.4864 ,-11.6662 ,-44.1426, \
        71.3758 ,-30.3652 ,-47.1404, \
        -61.1194 ,-49.3616 ,-14.2544, \
        -51.2876 ,-58.7698 ,-7.2681, \
        -37.8048 ,-61.9962 ,-0.4421, \
        -24.0228 ,-61.0334 ,6.6065, \
        -11.6357 ,-56.6868 ,11.9674, \
        12.0566 ,-57.3910 ,12.0512, \
        25.1063 ,-61.9022 ,7.3151, \
        38.3386 ,-62.7777 ,1.0230, \
        51.1910 ,-59.3023 ,-5.3494, \
        60.0539 ,-50.1903 ,-11.6157, \
        0.6539 ,-42.1938 ,13.3808, \
        0.8048 ,-30.9937 ,21.1509, \
        0.9922 ,-19.9446 ,29.2840, \
        1.2268 ,-8.4145 ,36.9481, \
        -14.7725 ,2.5983 ,20.1320, \
        -7.1802 ,4.7516 ,23.5367, \
        0.5559 ,6.5629 ,25.9444, \
        8.2725 ,4.6610 ,23.6957, \
        15.2144 ,2.6430 ,20.8582, \
        -46.0473 ,-37.4714 ,-7.0380, \
        -37.6747 ,-42.7305 ,-3.0212, \
        -27.8839 ,-42.7115 ,-1.3536, \
        -19.6483 ,-36.7547 ,0.1111, \
        -28.2730 ,-35.1345 ,0.1473, \
        -38.0824 ,-34.9190 ,-1.4766, \
        19.2659 ,-37.0323 ,0.6657, \
        27.8942 ,-43.3424 ,-0.2477, \
        37.4375 ,-43.1108 ,-1.6964, \
        45.1708 ,-38.0865 ,-4.8942, \
        38.1965 ,-35.5320 ,-0.2830, \
        28.7650 ,-35.4843 ,1.1727, \
        -28.9163 ,28.6127 ,2.2403, \
        -17.5332 ,22.1722 ,15.9343, \
        -6.6846 ,19.0291 ,22.6114, \
        0.3810 ,20.7211 ,23.7484, \
        8.3754 ,19.0355 ,22.7220, \
        18.8766 ,22.3941 ,15.6107, \
        28.7944 ,28.0799 ,3.2174, \
        19.0576 ,36.2982 ,14.9880, \
        8.9564 ,39.6346 ,22.5542, \
        0.3815 ,40.3956 ,23.5916, \
        -7.4289 ,39.8364 ,22.4061, \
        -18.1606 ,36.6779 ,15.1219, \
        -24.3775 ,28.6778 ,4.7857, \
        -6.8976 ,25.4760 ,20.8937, \
        0.3407 ,26.0143 ,22.2205, \
        8.4447 ,25.3262 ,21.0255, \
        24.4745 ,28.3230 ,5.7128, \
        8.4492 ,30.5962 ,20.6715, \
        0.2053 ,31.4087 ,21.9037, \
        -7.1983 ,30.8449 ,20.3280);
        return lnd.reshape(1, 68) * 1e-3;
    }

    cv::Mat DefaultIntrinsicMat(const cv::Size& frame_size){
        float focal_length = frame_size.width;
        return (cv::Mat_<double>(3, 3) << focal_length,      0,              frame_size.width/2,\
                                        0,                  focal_length,   frame_size.height / 2, \
                                        0,                  0,              1);
    }

    cv::Mat Estimate3dLandmark(const cv::Mat& lnd_2d, const cv::Mat& template_face_mat, cv::Vec6d* rtvec, \
        const cv::Mat& intrinsic, const cv::Mat& dist_coefs ){
        ASSERT(lnd_2d.cols == 2);
        ASSERT(template_face_mat.cols == 3);
        cv::Vec3d rvec, tvec;
        cv::Mat lnd_2d_double, template_face_double;
        lnd_2d.convertTo(lnd_2d_double, CV_64FC1);
        template_face_mat.convertTo(template_face_double, CV_64FC1);
        cv::solvePnP(template_face_double, lnd_2d_double, intrinsic, dist_coefs, rvec, tvec);//solvepnp need double array inputs
        for(int ii =0; ii < 3; ++ii){
            (*rtvec)[ii] = rvec[ii];
            (*rtvec)[3 + ii] = tvec[ii];
        }
        cv::Mat rmat;
        cv::Rodrigues(rvec, rmat);
        cv::Mat pose_mat;
        cv::hconcat(rmat, tvec, pose_mat);
        cv::Mat homo_template_face;
        cv::hconcat(template_face_double, cv::Mat::zeros(template_face_double.rows, 1, CV_64FC1), homo_template_face);
        return (pose_mat * homo_template_face.t()).t();
    }

    TimeSeries::TimeSeries(){

    }

    TimeSeries::~TimeSeries(){

    }

    void TimeSeries::AddFrameData(double time, float val){
        const int max_frames = 60;
        TData data(time, val);
        if(_q.size() > max_frames){
            _q.pop_front();
        }
        _q.push_back(data);
    }

    bool TimeSeries::AverageValueInTimeslice(float timeslice_sec, float* mean_val){
        ASSERT(timeslice_sec > 0);
        if(_q.empty())
            return false;
        float cur_time = _q.back().timestamp;
        auto it = std::find_if(_q.rbegin(), _q.rend(), [cur_time, timeslice_sec](auto d){return Sec(cur_time - d.timestamp) > timeslice_sec;});
        if(it == _q.rend())
            return false;
        float sum = 0;
        for(auto cur_it = _q.rbegin(); cur_it != it; ++cur_it){
            sum += cur_it->val;
        }
        *mean_val = sum / std::distance(_q.rbegin(), it);
    }

} // namespace opendms
