#ifndef TIME_H
#define TIME_H

#include <string>
#include <cmath>
#include <chrono>

//constants
#define SECONDS_PER_YEAR = 31536000;
#define SECONDS_PER_MONTH = 2628000;
#define SECONDS_PER_DAY = 86400;
#define SECONDS_PER_HOUR = 3600;
#define SECONDS_PER_MINUTE = 60;

#define DAYS_PER_MONTH = 30.41666666666667;
#define MONTHS_PER_YAER = 12;
#define HOURS_PER_DAY = 24;
#define MINUTES_PER_HOUR = 60;

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

namespace time {

}

} //namespace humanize
#endif // TIME_H
