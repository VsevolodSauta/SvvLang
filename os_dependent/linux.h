#pragma once

#if 0
#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2

#define O_RDONLY	0
#define O_WRONLY	1
#define O_RDWR		2
#endif

int OSexit(int code);
int OSfileOpen(char* name, int flags, ...);
int OSfileClose(int fd);
int OSfileRead(int fd, void* buffer, int length);
int OSfileWrite(int fd, void* buffer, int length);
int OSfileSeek(int fd, long offset, int origin);
int OSfileTruncate(int fd, long length);
void* OSmappingMap(void* addr, long length, long prot, long flags, long fd, long offset);
int OSmappingUnmap(void* addr, long length);
