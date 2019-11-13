#ifndef UTILS_H

#define UTILS_H
#define DEFAULT_ALLOC_ERR_MSG "Full memory\n"

#include "curl/curl.h"

void verifyPointer(void *p, const char *message);
void *myAlloc(int size, const char *errMessage);
int fileExist(char *path);
long fileSize(char *path);
char *putFileInBuffer(char *path);
int createDirectory(char *name);
void curlSetDefaultOptions(CURL *curl, void *);
int httpGet(char *url, void *buffer);
int *indexOfSubStr(const char *src, const char *search, int *size);
#endif

