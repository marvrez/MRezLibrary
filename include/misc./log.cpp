#include "log.h"

#include "string_utils.h"
#include "color.h"

Logger globalLogger;
const char* COLOR_TRACE = BOLDBLACK;
const char* COLOR_DEBUG = BOLDWHITE;
const char* COLOR_UNIMPLEMENTED = BOLDMAGENTA;
const char* COLOR_INFO = BOLDBLUE;
const char* COLOR_WARNING = BOLDYELLOW;
const char* COLOR_ERROR = BOLDRED;
const char* COLOR_RESET = RESET;

Logger::Logger() {}

void Logger::log(LogLevel level, const char* fmt, ...) {
    if (!shouldLog(level)) return;

    va_list args;
    va_start(args, fmt);
    std::string msg = str_utils::str_format(fmt, args);
    va_end(args);

    fprintf((level < LogLevel::Error) ? stdout : stderr,
        "%s| %s%s\n",
        levelColor(level), COLOR_RESET, msg.c_str());
}

void Logger::setLevel(LogLevel level) {
    currentLevel = level;
}

void Logger::enableTracing() {
    tracingEnabled = true;
}

bool Logger::shouldLog(LogLevel level) const {
    if (!tracingEnabled && level == LogLevel::Trace) return false;

    return enabled && (currentLevel <= level);
}

inline const char* Logger::levelColor(LogLevel level) const {
    switch (level) {
        case LogLevel::Trace: 			return COLOR_TRACE;
        case LogLevel::Debug: 			return COLOR_DEBUG;
        case LogLevel::Unimplemented: 	return COLOR_UNIMPLEMENTED;
        case LogLevel::Info: 			return COLOR_INFO;
        case LogLevel::Warning: 		return COLOR_WARNING;
        case LogLevel::Error: 			return COLOR_ERROR;
    }
}

void logSetLevel(LogLevel level) {
    globalLogger.setLevel(level);
}
