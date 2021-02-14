#include "common_utils.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/cfg/env.h"
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
} // namespace opendms
