#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <sys/cdefs.h>

__attribute__((__noreturn__))
void abort(void);

__attribute__((__noreturn__))
void panic(const char *);

#endif