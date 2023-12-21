//
// Created by Aarch64 on 21/12/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

FILE *log_d;

void init_log()
{
    if ((log_d = fopen(OUT_LOG, "w")) == NULL)
    {
      fprintf(stderr, "log.c: init_log: Write file error\n");
      fprintf(stderr, "Failed in init log!\n");
      exit(1);
    }
}

void write_log(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    vfprintf(log_d, fmt, args);

    va_end(args);
}
