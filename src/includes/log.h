#ifndef LOG_H
#define LOG_H

#define OUT_LOG "debug.log"

void init_log();
void write_log(const char* fmt, ...);

#endif
