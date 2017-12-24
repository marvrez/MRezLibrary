#ifndef TIME_H
#define TIME_H

#include <string>
#include <cmath>
#include <chrono>

//constants
constexpr int SECONDS_PER_YEAR = 31536000;
constexpr int SECONDS_PER_MONTH = 2628000;
constexpr int SECONDS_PER_DAY = 86400;
constexpr int SECONDS_PER_HOUR = 3600;
constexpr int SECONDS_PER_MINUTE = 60;

constexpr double DAYS_PER_MONTH = 30.41666666666667;
constexpr int MONTHS_PER_YEAR = 12;
constexpr int HOURS_PER_DAY = 24;
constexpr int MINUTES_PER_HOUR = 60;


//TODO: maybe there is a more "elegant" way to do this in C++11?
#define MEASURE_TIME(a) \
    do { \
    double start = getCurrentTime(); \
    a; \
    printf("%s took: %f seconds\n", #a, getCurrentTime() - start); \
    } while (0)

double getCurrentTime() {
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_sec + now.tv_nsec*1e-9;
}

namespace humanize {
enum SuffixType {SHORT, LONG};
static const char* shortSuffixes[6] = {
    "y",
    "m",
    "d",
    "h",
    "m",
    "s",
};

static const char* singularLongSuffixes[6] = {
    "year",
    "month",
    "day",
    "hour",
    "minute",
    "second",
};

static const char* pluralLongSuffixes[6] = {
    "years",
    "months",
    "days",
    "hours",
    "minutes",
    "seconds",
};

struct TimeData {
    uint8_t amount;

    const char* singularLongSuffix;
    const char* pluralLongSuffix;
    const char* shortSuffix;

    TimeData(uint8_t amount, int idx)
        : amount(amount)
        , singularLongSuffix(singularLongSuffixes[idx])
        , pluralLongSuffix(pluralLongSuffixes[idx])
        , shortSuffix(shortSuffixes[idx])
    { }

    const char* getSuffix(SuffixType type) const {
        switch (type) {
            case SuffixType::LONG:
                return (this->amount == 1) ? singularLongSuffix : pluralLongSuffix;
                break;

            case SuffixType::SHORT:
                return this->shortSuffix;
                break;
        }
    }
};

template <class Rep, class Period, class = std::enable_if_t<
   std::chrono::duration<Rep, Period>::min() < std::chrono::duration<Rep, Period>::zero()>>
constexpr std::chrono::duration<Rep, Period> abs(std::chrono::duration<Rep, Period> d)
{
    return d >= d.zero() ? d : -d;
}

namespace time {

struct TimeResult {
    std::string str;
    int64_t secsDiff;

    enum {
        PAST,
        PRESENT,
        FUTURE,
    } resultType;


    bool operator==(const TimeResult& rhs) const {
        return this->secsDiff == rhs.secsDiff &&
               this->resultType == rhs.resultType;
    }

    bool operator!=(const TimeResult& rhs) const {
        return !(*this == rhs);
    }
};

template<typename Clock, class Duration = typename Clock::duration>
TimeResult relativeTime(const std::chrono::time_point<Clock, Duration>& start,
                        const std::chrono::time_point<Clock, Duration>& stop,
                        SuffixType sType = SuffixType::LONG, unsigned int maxPoints = 2)
{
    TimeResult res;

    auto diff = abs(std::chrono::duration_cast<std::chrono::seconds>(start-stop));

    int64_t secsDiff = diff.count();

    res.secsDiff = secsDiff;

    if(secsDiff == 0) {
        res.str = "present";
        res.resultType = TimeResult::PRESENT;
        return res;
    }

    if(secsDiff < 0) res.resultType = TimeResult::FUTURE;
    else res.resultType = TimeResult::PAST;

    TimeData td[] = {
    TimeData(static_cast<uint16_t>(trunc(secsDiff / SECONDS_PER_YEAR)),
             0),
    TimeData(static_cast<uint16_t>(trunc(secsDiff / SECONDS_PER_MONTH % MONTHS_PER_YEAR)),
             1),
    TimeData(static_cast<uint16_t>(trunc(fmod(secsDiff / SECONDS_PER_DAY, DAYS_PER_MONTH))),
             2),
    TimeData(static_cast<uint16_t>(trunc(secsDiff / SECONDS_PER_HOUR % HOURS_PER_DAY)),
             3),
    TimeData(static_cast<uint16_t>(trunc(secsDiff / SECONDS_PER_MINUTE % MINUTES_PER_HOUR)),
             4),
    TimeData(static_cast<uint16_t>(secsDiff % SECONDS_PER_MINUTE),
             5),
    };

    char str[1024];
    unsigned int len = 0, pointsUsed = 0;
    for (const TimeData& curTimeData : td) {
        if (pointsUsed >= maxPoints) break;

        if (curTimeData.amount == 0) continue;

        if (pointsUsed > 0) {
            if (sType == SuffixType::LONG) {
                if (pointsUsed == maxPoints - 1)
                    strcpy(str + len, ", and "), len += 6;
                else
                    strcpy(str + len, ", "), len += 2;
            }
        }

        if (sType == SuffixType::LONG) //spaces between amount and suffix if long suffixtype
            len += std::sprintf(str + len, "%d %s", curTimeData.amount,
                                curTimeData.getSuffix(sType));
        else //else no spaces
            len += std::sprintf(str + len, "%d%s", curTimeData.amount,
                                curTimeData.getSuffix(sType));
        pointsUsed++;
    }
    res.str = str;

    return res;
}

template <typename Clock>
TimeResult relativeTime(const std::chrono::time_point<Clock>& stop,
             SuffixType sType = SuffixType::LONG, unsigned int maxPoints = 2)
{
    return relativeTime(Clock::now(), stop, sType, maxPoints);
}

template <typename Duration, typename Clock = std::chrono::system_clock,
          typename = typename std::enable_if<std::chrono::__is_duration<Duration>::value>::type>
TimeResult relativeTime(const Duration &duration, SuffixType sType = SuffixType::LONG,
                        unsigned int maxPoints = 2)
{
    auto t1 = std::chrono::time_point_cast<Duration>(Clock::now());
    auto t2 = t1 + duration;

    return relativeTime(t1, t2, sType, maxPoints);
}

template <typename Clock, typename Duration = typename Clock::duration>
std::string diffTime(const std::chrono::time_point<Clock, Duration>& start,
   const std::chrono::time_point<Clock, Duration>& stop,
   SuffixType sType = SuffixType::LONG, unsigned int maxPoints = 2)
{
    return relativeTime(start, stop, sType, maxPoints).str;
}

template <typename Clock>
std::string diffTime(const std::chrono::time_point<Clock>& stop,
                     SuffixType sType = SuffixType::LONG, unsigned int maxPoints = 2)
{
    return relativeTime(Clock::now(), stop, sType, maxPoints).str;
}

template<typename Duration, typename Clock = std::chrono::system_clock,
         typename = typename std::enable_if<std::chrono::__is_duration<Duration>::value>::type>
std::string diffTime(const Duration& duration, SuffixType sType = SuffixType::LONG,
                     unsigned int maxPoints = 2)
{
    auto t1 = std::chrono::time_point_cast<Duration>(Clock::now());
    auto t2 = t1 + duration;
    return diffTime(t1, t2, sType, maxPoints);
}

} //namespace time
} //namespace humanize
#endif // TIME_H
