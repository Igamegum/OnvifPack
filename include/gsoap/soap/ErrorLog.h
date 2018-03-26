#ifndef PROCESS_EVENTLOG_H_
#define PROCESS_EVENTLOG_H_

#include<stdio.h>
#include<string.h>
#include<time.h>

#define MAX_MSG_LEN 1024

typedef unsigned int uint;

void processEventLog(char *fileName, uint lineNo, FILE *fp, const char *argList, ...);

void PrintErr(struct soap* _psoap);
#endif
