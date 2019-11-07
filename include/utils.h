#ifndef UTILS_H

#define UTILS_H

#include "curl/curl.h"

void curlSetDefaultOptions(CURL *curl, void *, size_t (*callback)(char *, size_t, size_t, void *));
size_t curlCallback(char *ptr, size_t size, size_t nmemb, void *userdata);
int httpGet(char *url, void *buffer, size_t (*callback)(char *, size_t, size_t, void *));

#endif

