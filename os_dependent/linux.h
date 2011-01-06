#pragma once

int OSexit(int code);
int OSfileOpen(char* name, int flags, ...);
int OSfileClose(int fd);
int OSfileRead(int fd, void* buffer, int length);
int OSfileWrite(int fd, void* buffer, int length);
int OSfileSeek(int fd, long offset, int origin);
int OSfileTruncate(int fd, long length);
void* OSmappingMap(void* addr, long length, long prot, long flags, long fd, long offset);
int OSmappingUnmap(void* addr, long length);
