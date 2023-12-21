//
// Created by Aarch64 on 21/12/23.
//

#ifndef LOG_H
#define LOG_H

#define OUT_LOG "debug.log"

void init_log();
void write_log(const char* fmt, ...);

#endif
