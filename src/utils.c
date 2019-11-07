#include "../include/common.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void curlSetDefaultOptions(CURL *curl, void *response, size_t (*callback)(char *, size_t, size_t, void *)) {
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
    //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
}

size_t curlCallback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    return nmemb;
}

int httpGet(char *url, void *buffer, size_t (*callback)(char *, size_t, size_t, void *)) {
    CURL *curl = curl_easy_init();;
    CURLcode res;

    if (!curl) {
        printf(ERR_HTTP_INIT);
        return -1;
    }

    curlSetDefaultOptions(curl, buffer, callback);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        printf(curl_easy_strerror(res));
        return res;
    }

    curl_easy_cleanup(curl);
    return CURLE_OK;
}
