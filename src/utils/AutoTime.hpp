#ifndef AutoTime_hpp
#define AutoTime_hpp

#include <stdint.h>
#include <stdio.h>

namespace opendms {

class Timer {
public:
    Timer();
    ~Timer();
    Timer(const Timer&)  = delete;
    Timer(const Timer&&) = delete;
    Timer& operator=(const Timer&)  = delete;
    Timer& operator=(const Timer&&) = delete;
    
    // reset timer
    void reset();
    // get duration (us) from init or latest reset.
    uint64_t durationInUs();
    
protected:
    uint64_t mLastResetTime;
};

/** time tracing util. prints duration between init and deinit. */
class AutoTime : Timer {
public:
    AutoTime(int line, const char* func);
    ~AutoTime();
    AutoTime(const AutoTime&)  = delete;
    AutoTime(const AutoTime&&) = delete;
    AutoTime& operator=(const AutoTime&) = delete;
    AutoTime& operator=(const AutoTime&&) = delete;

private:
    int mLine;
    char* mName;
};
} 

#ifdef OPEN_TIME_TRACE
#define AUTOTIME opendms::AutoTime ___t(__LINE__, __func__)
#else
#define AUTOTIME
#endif

#endif /* AutoTime_hpp */
