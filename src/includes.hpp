
#include "spdlog/spdlog.h"
#include <basic/Frame.hpp>
#include <json.hpp>
#include <memory>
#include <vector>

#define lg spdlog::get("opendms")
#ifdef DEBUG
#define ASSERT(x)                                            \
    {                                                            \
        int res = (x);                                           \
        if (!res) {                                              \
            lg->critical("Error for {}, {}", __FILE__, __LINE__); \
            assert(res);                                         \
        }                                                        \
    }
#else
#define ASSERT(x)                                            \
    {                                                            \
        int res = (x);                                           \
        if (!res) {                                              \
            lg->critical("Error for {}, {}", __FILE__, __LINE__); \
            abort();                                                \
        }                                                        \
    }
#endif

using json = nlohmann::json;
