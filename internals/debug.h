#pragma once

#include <stdio.h>
#define _DMSG(args...) \
	fprintf(stderr, args); \
	fflush(stderr);


#define DEBUG 0
#define MEMORY_DEBUG 1

#if DEBUG
#include <stdio.h>

extern int DLEVEL;


#define DMSGS(args...) { \
	int i = 0; \
	while(i++ < DLEVEL) fprintf(stderr, "\t"); \
	fprintf(stderr, "%p --- ", _self); \
	fprintf(stderr, args); \
	fprintf(stderr, "\n"); \
	fflush(stderr);	\
}

#define DMSG(args...) { \
	int i = 0; \
	while(i++ < DLEVEL) fprintf(stderr, "\t"); \
	fprintf(stderr, args); \
	fprintf(stderr, "\n"); \
	fflush(stderr);	\
}

#define DPUSH(args...) {DMSG(args); DLEVEL++;}
#define DPOP(args...) {DLEVEL--; DMSG(args);}
#define DPUSHS(args...) {DMSGS(args); DLEVEL++;}
#define DPOPS(args...) {DLEVEL--; DMSGS(args);}
#define IMPOSSIBLE() DMSG("IMPOSSIBLE!!!")
#else

#define DMSGS(args...)
#define DMSG(args...)
#define DPUSHS(args...)
#define DPOPS(args...)
#define DPUSH(args...)
#define DPOP(args...)
#define IMPOSSIBLE()


#endif
