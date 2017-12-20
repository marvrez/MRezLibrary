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
static char cda_logbuf[4096];

#define BT_SIZE  16
static void BACKTRACE() {
    int num_calls;
    void* bt_buffer[BT_SIZE];

    num_calls = backtrace(bt_buffer, BT_SIZE);

    backtrace_symbols_fd(bt_buffer, num_calls, STDERR_FILENO);
}
#undef BT_SIZE

static void LOG_CORE(char level, struct timeb* timebp, pid_t pid,
                     __typeof__(__FILE__) 	  file,
                     __typeof__(__LINE__)     line,
                     __typeof__(__FUNCTION__) func,
                     char* msgstring)
{
    ftime(timebp);
    struct tm* ptm = gmtime(&timebp->time);

    fprintf (stderr,
               (level=='I') ? GREEN_B
             : (level=='W') ? YELLOW_B
             : (level=='E') ? RED_B
             : (level=='D') ? CYAN_B
             : 				  RESET);

    fprintf (stderr, "%1c%02d%02d %02d:%02d:%02d.%03d %05d %s:%d] %s : %s\n", level,
             ptm->tm_mon, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec,
             timebp->millitm, pid, file, line, func, msgstring);

    fprintf (stderr, RESET);

}

#endif
