#ifndef LOG_H
#define LOG_H

#include <string>

enum class LogLevel {
    Trace,
    Debug,
    Unimplemented,
    Info,
    Warning,
    Error,
};

class Logger {
public:
    Logger();

    void log(LogLevel level, const char* fmt, ...);
    void setLevel(LogLevel level);

    void enableTracing();

private:
    bool shouldLog(LogLevel level) const;
    const char* levelColor(LogLevel level) const;

    LogLevel currentLevel = LogLevel::Debug;
    bool enabled = true;
    bool tracingEnabled = false;
};

extern Logger globalLogger;
extern const char* COLOR_TRACE;
extern const char* COLOR_DEBUG;
extern const char* COLOR_UNIMPLEMENTED;
extern const char* COLOR_INFO;
extern const char* COLOR_WARNING;
extern const char* COLOR_ERROR;
extern const char* COLOR_RESET;

#define log_trace(fmt, ...) globalLogger.log(LogLevel::Trace, fmt, ##__VA_ARGS__);
#define log_debug(fmt, ...) globalLogger.log(LogLevel::Debug, fmt, ##__VA_ARGS__);
#define log_unimplemented(fmt, ...) globalLogger.log(LogLevel::Unimplemented, fmt, ##__VA_ARGS__);
#define log_info(fmt, ...) globalLogger.log(LogLevel::Info, fmt, ##__VA_ARGS__);
#define log_warn(fmt, ...) globalLogger.log(LogLevel::Warning, fmt, ##__VA_ARGS__);
#define log_error(fmt, ...) globalLogger.log(LogLevel::Error, fmt, ##__VA_ARGS__);

extern void logSetLevel(LogLevel level);

#endif
