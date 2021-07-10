#include <iostream>
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/cfg/env.h"
#include <utils/common_utils.hpp>
#include <opencv2/core.hpp>

// void TestFunction(){
//     std::cout<<opendms::Clamp(1.8, 0.0, 1.0)<<"\n";
// }

int main(int arc, char** arv){
    // TestFunction();
    // return 0;
    cv::Mat mat;
    // export SPDLOG_LEVEL=info,mylogger=trace && ./demo
    spdlog::info("Welcome to spdlog version {}.{}.{}  !", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);

    spdlog::warn("Easy padding in numbers like {:08d}", 12);
    spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    spdlog::info("Support for floats {:03.2f}", 1.23456);
    spdlog::info("Positional args are {1} {0}..", "too", "supported");
    spdlog::info("{:>8} aligned, {:<8} aligned", "right", "left");

    // Runtime log levels
    spdlog::set_level(spdlog::level::info); // Set global log level to info
    spdlog::debug("This message should not be displayed!");
    spdlog::set_level(spdlog::level::trace); // Set specific logger's log level
    spdlog::debug("This message should be displayed..");

    auto log_level = spdlog::level::info;
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("log.txt", true);
    std::vector<spdlog::sink_ptr> sinks {console_sink, file_sink};
    auto my_logger= std::make_shared<spdlog::logger>("opendms",sinks.begin(), sinks.end());
    spdlog::register_logger(my_logger);
    spdlog::cfg::load_env_levels();
    my_logger->info("hello");
    my_logger->debug("debug info");
    // spdlog::logger logger("opendms", sinks.begin(), sinks.end());
    // auto t_logger = std::make_shared<spdlog::logger>("mylogger",{console_sink, file_sink});
    // auto t_logger = std::make_shared<spdlog::logger>("opendms", {console_sink, file_sink});
    // auto t_logger = new spdlog::logger("opendms", {console_sink, file_sink});
    // std::shared_ptr<spdlog::logger> logger(t_logger);
    // spdlog::register_logger(logger);
    // logger.set_level(log_level);

    // logger.warn("this should appear in both console and file");
    // logger.info("this message should not appear in the console, only in the file");

    return 0;
}