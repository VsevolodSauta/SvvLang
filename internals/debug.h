#pragma once

#include <stdio.h>
#define _DMSG(args...) \
	fprintf(stderr, args); \
	fflush(stderr);


#define DEBUG 0
#define MEMORY_DEBUG 0

#if DEBUG
#include <stdio.h>

extern int DLEVEL;

static inline int strlen(char* arg)
{
	register int toReturn = 0;
	while(arg[toReturn++]);
	return toReturn - 1;
}

#define DMSGS(arg) { \
	int i = 0; \
	while(i++ < DLEVEL) OSfileWrite(2, "\t", 1); \
	OSfileWrite(2, arg, strlen(arg)); \
	OSfileWrite(2, "\n", 1); \
}

#define DMSG(arg) { \
	int i = 0; \
	while(i++ < DLEVEL) OSfileWrite(2, "\t", 1); \
	OSfileWrite(2, arg, strlen(arg)); \
	OSfileWrite(2, "\n", 1); \
}

#define DPUSH(arg) {DMSG(arg); DLEVEL++;}
#define DPOP(arg) {DLEVEL--; DMSG(arg);}
#define DPUSHS(arg) {DMSGS(args); DLEVEL++;}
#define DPOPS(arg) {DLEVEL--; DMSGS(arg);}
#define IMPOSSIBLE() DMSG("IMPOSSIBLE!!!")
#else

#define DMSGS(arg)
#define DMSG(arg)
#define DPUSHS(arg)
#define DPOPS(arg)
#define DPUSH(arg)
#define DPOP(arg)
#define IMPOSSIBLE()


#endif
