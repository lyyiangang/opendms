#include "common_utils.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/cfg/env.h"
#include <fstream>
#include <memory>
#include <opencv2/core.hpp>
namespace opendms
{
    std::shared_ptr<spdlog::logger> RegistLogger(){
        // export SPDLOG_LEVEL=info
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("log.txt", true);
        std::vector<spdlog::sink_ptr> sinks {console_sink, file_sink};
        auto lg= std::make_shared<spdlog::logger>("opendms",sinks.begin(), sinks.end());
        spdlog::register_logger(lg);
        lg->set_level(spdlog::level::info); // set default log level
        spdlog::cfg::load_env_levels();
        return lg;
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
        cv::Rect img_rect(0, 0, w, h);
        if(!img_rect.contains(rect.tl()) && !img_rect.contains(rect.br()))
            return cv::Mat();
        cv::Mat sub_img = img(cv::Range(rect.tl().y, rect.br().y), cv::Range(rect.tl().x, rect.br().x));
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

} // namespace opendms
