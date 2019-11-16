/*
** Filename : utils.c
**
** Made by  : Baptiste LEGO
**
** Description  : utils functions used in App
*/

#include "../include/common.h"
#include <sys/stat.h>
#include <unistd.h>

void verifyPointer(void *p, const char *message) {
    if(p == NULL) {
        printf("%s\n", message);
        exit(EXIT_FAILURE);
    }
}

void *myAlloc(int size, const char *errMessage) {
    void *p = malloc(size);
    verifyPointer(p, errMessage);

    return p;
}

int fileExist(char *path) {
    FILE *file = NULL;

    file = fopen(path, "r");
    if(file == NULL) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

long fileSize(char *path) {
    FILE *file = NULL;
    long size = 0;

    file = fopen(path, "r");

    if(file != NULL) {
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        fclose(file);
    }

    return size;
}

char *putFileInBuffer(char *path) {
    FILE *file = NULL;
    long size = fileSize(path);
    char *buffer = myAlloc(sizeof(char) * size, DEFAULT_ALLOC_ERR_MSG);

    file = fopen(path, "r");

    if(file != NULL) {
        fread(buffer, 1, size, file);
        fclose(file);
    }

    return buffer;
}

int createDirectory(char *name) {
    struct stat st;

    if (stat(name, &st) == -1) {
        mkdir(name);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

void curlSetDefaultOptions(CURL *curl, void *response) {
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
}

int httpGet(char *url, void *buffer) {
    CURL *curl = curl_easy_init();;
    CURLcode res;

    if (!curl) {
        printf(ERR_HTTP_INIT);
        return -1;
    }

    curlSetDefaultOptions(curl, buffer);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        printf(curl_easy_strerror(res));
        return res;
    }

    curl_easy_cleanup(curl);
    return CURLE_OK;
}

int *indexOfSubStr(const char *src, const char *search, int *size) {
    int *res = NULL;
    int count = 0, i;
    *size = 0;

    for(i = 0; i < strlen(src); i++) {
        if(count == strlen(search)) {
            count = 0;
            (*size)++;
            res = realloc(res, sizeof(int) * *size);
            res[*size - 1] = i - strlen(search);
        }
        if(src[i] != search[count] && count > 0) {
            count = 0;
        }
        if(src[i] == search[count]) {
            count++;
        }
    }

    return res;
}

char *intToStr(char *buffer, int value) {
    sprintf(buffer, "%d", value);
    return buffer;
}

void getDatetime(struct tm *tm) {
    time_t rawtime = time(NULL);
    *tm = *localtime ( &rawtime );
    tm->tm_year += 1900;
    tm->tm_mon++;
}

char *getDatetimeFormated(struct tm *tm) {
    char *res = myAlloc(sizeof(char) * 100, DEFAULT_ALLOC_ERR_MSG);
    char day[3], month[3], year[5], hour[3], min[3];

    getDatetime(tm);
    sprintf(day, "%d", tm->tm_mday);
    sprintf(month, "%d", tm->tm_mon);
    sprintf(year, "%d", tm->tm_year);
    sprintf(hour, "%d", tm->tm_hour);
    sprintf(min, "%d", tm->tm_min);

    sprintf(res, "%s_%s_%s_%sH%s", day, month, year, hour, min);

    return res;
}
