#include "log.h"
#include <stdarg.h>
#include <stdio.h>

static FILE* logFile = 0;

void logOpen(char* name)
{
	if((logFile != 0) || (name == NULL))
		return;

#ifdef _WIN32
	fopen_s(&logFile, name, "wt");
#else
	logFile = fopen(name, "wt");
#endif
}

void logPrintf(char* text, ...)
{
	if(!logFile)
		return;

	va_list args;
	va_start(args, text);
	vfprintf(logFile, text, args);
	va_end(args);
}

void logClose()
{
	if(!logFile)
		return;
	fclose(logFile);
	logFile = 0;
}
