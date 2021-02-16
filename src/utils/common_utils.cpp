#include "common_utils.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/cfg/env.h"
#include <fstream>
#include <memory>

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
} // namespace opendms
