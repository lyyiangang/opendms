#ifndef common_utils_hpp
#define common_utils_hpp
#include "spdlog/spdlog.h"
namespace opendms
{
    std::shared_ptr<spdlog::logger> RegistLogger();
} // namespace opendms

#endif 