#pragma once

#define _DMSG(args...) \
	fprintf(stderr, args); \
	fflush(stderr);


#define DEBUG 0
#define MEMORY_DEBUG 0
#define STDLIB 0

#if DEBUG

extern int DLEVEL;

static inline int strlen(char* arg)
{
	register int toReturn = 0;
	while(arg[toReturn++]);
	return toReturn - 1;
}

static inline char* DEBUG_ptrToStr(void* argPtr)
{
	long arg = (long) argPtr;
	static char buffer[32];
	buffer[31] = 0;
	buffer[30] = '>';
	int position = 29;
	while(arg)
	{
		buffer[position] = arg % 16;
		if(buffer[position] < 10)
		{
			buffer[position] += '0';
		} else {
			buffer[position] += 'a' - 10;
		}
		position--;
		arg /= 16;
	}
	buffer[position--] = 'x';
	buffer[position--] = '0';
	buffer[position] = '<';
	return buffer + position;
}

#define DMSGS(arg) { \
	int i = 0; \
	char* obj = DEBUG_ptrToStr(_self); \
	while(i++ < DLEVEL) OSfileWrite(2, "\t", 1); \
	OSfileWrite(2, obj, strlen(obj)); \
	OSfileWrite(2, " - ", 3); \
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
#define DPUSHS(arg) {DMSGS(arg); DLEVEL++;}
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
