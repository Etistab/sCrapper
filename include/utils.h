/*
** Filename : utils.h
**
** Made by  : Baptiste LEGO
**
** Description  : utils functions used in App
*/

#ifndef UTILS_H

#define UTILS_H
#define VERSIONING_ON   1
#define VERSIONING_OFF  0

#include "curl/curl.h"

void verifyPointer(void *p, const char *message);
void *myAlloc(int size, const char *errMessage);
int fileExist(char *path);
long fileSize(char *path);
char *putFileInBuffer(char *path);
int createDirectory(char *name);
void curlSetDefaultOptions(CURL *curl, void *body);
int httpGet(char *url, void *body, const char **typeAllowed, int numberOfTypeAllowed);
char *getContentType(CURL *curl);
int contentTypeAllowed(const char *contentType, const char **typeAllowed, int numberOfTypesAllowed);
int *indexOfSubStr(const char *src, const char *search, int *size);
char *intToStr(char *buffer, int value);
void getDatetime(struct tm *tm);
char *getDatetimeFormated(struct tm *tm);

#endif

