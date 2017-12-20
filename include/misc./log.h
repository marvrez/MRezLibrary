#ifndef LOG_H
#define LOG_H

#include "color.h"

#include <string>
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <execinfo.h>
#include <sys/timeb.h>

static struct timeb timeb_s;
static char logbuffer[4096];

#define BT_SIZE  16
static void _BACKTRACE() {
    int num_calls;
    void* bt_buffer[BT_SIZE];

    num_calls = backtrace(bt_buffer, BT_SIZE);

    backtrace_symbols_fd(bt_buffer, num_calls, STDERR_FILENO);
}
#undef BT_SIZE

static void _LOG_CORE(char level, struct timeb* timebp, pid_t pid,
                     __typeof__(__FILE__) 	  file,
                     __typeof__(__LINE__)     line,
                     __typeof__(__FUNCTION__) func,
                     char* msgstring)
{
    ftime(timebp);
    struct tm* ptm = localtime(&timebp->time);

    //Sets color to message
    fprintf (stderr,
               (level=='I') ? BOLDGREEN
             : (level=='W') ? BOLDYELLOW
             : (level=='E') ? BOLDRED
             : (level=='D') ? BOLDCYAN
             : 				  RESET);

    //actual message formatting
    fprintf (stderr, "[%1c%02d%02d %02d:%02d:%02d.%03d %05d %s:%d] %s : %s\n", level,
             ptm->tm_mon+1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec,
             timebp->millitm, pid, file, line, func, msgstring);

    fprintf (stderr, RESET);
}

//API
#define LOG_DEBUG(msg) do { \
_LOG_CORE ('D', &timeb_s, getpid(), __FILE__, __LINE__, __FUNCTION__, ((msg))); \
} while (0)

#define LOG_INFO(msg) do { \
_LOG_CORE ('I', &timeb_s, getpid(), __FILE__, __LINE__, __FUNCTION__, ((msg))); \
} while (0)

#define LOG_WARN(msg) do { \
_LOG_CORE ('W', &timeb_s, getpid(), __FILE__, __LINE__, __FUNCTION__, ((msg))); \
} while (0)

#define LOG_ERROR(msg) do { \
_LOG_CORE ('E', &timeb_s, getpid(), __FILE__, __LINE__, __FUNCTION__, ((msg))); \
_BACKTRACE(); \
} while (0)

#define LOG_DEBUGF(...) do { \
snprintf (logbuffer, 4095, ##__VA_ARGS__); \
LOG_DEBUG (logbuffer); \
} while (0)

#define LOG_INFOF(...) do { \
snprintf (logbuffer, 4095, ##__VA_ARGS__); \
LOG_INFO (logbuffer); \
} while (0)

#define LOG_WARNF(...) do { \
snprintf (logbuffer, 4095, ##__VA_ARGS__); \
LOG_WARN (logbuffer); \
} while (0)

#define LOG_ERRORF(...) do { \
snprintf (logbuffer, 4095, ##__VA_ARGS__); \
LOG_ERROR (logbuffer); \
} while (0)

#endif
