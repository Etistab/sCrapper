/*
** Filename : scraper.c
**
** Made by  : Baptiste LEGO
**
** Description  : scrap functions
*/

#include "../include/common.h"

void scrapWebsite(char *name, char *url, int maxDepth, int versioning) {
    int i;
    int depth = 0;
    int numberOfLinks = 0;
    char *path = NULL;
    char *html = NULL;
    char **links = NULL;

    do {
        path = scrapPage(name, url, versioning);
        if(path != NULL) {
            html = putFileInBuffer(path);
            verifyPointer(html, "Cannot fill html in memory\n");

            links = findLinks(html, &numberOfLinks);
            printf("%d links found\n", numberOfLinks);

            for(i = 0; i < numberOfLinks; i++) {
                printf("%s\n", links[i]);
                free(links[i]);
            }
            free(links);
            free(path);
            free(html);
        }
        depth++;
    }while(depth <= maxDepth);
}

char **findLinks(char *html, int *numberOfLinks) {
    char **res = NULL;
    char *firstOccurence = NULL;
    char *lastOccurence = NULL;
    int *indexs = NULL;
    int i;
    int sizeOfLink;
    char search[7] = "href=\"";

    indexs = indexOfSubStr(html, search, numberOfLinks);
    verifyPointer(indexs, "Cannot find substr");

    res = myAlloc(sizeof(char *) * *numberOfLinks, DEFAULT_ALLOC_ERR_MSG);

    for(i = 0; i < *numberOfLinks; i++) {
        firstOccurence = html + (indexs[i] + strlen(search));
        lastOccurence = strchr(firstOccurence, '"');
        sizeOfLink = lastOccurence - firstOccurence;
        res[i] = myAlloc(sizeof(char) * (sizeOfLink + 1), DEFAULT_ALLOC_ERR_MSG);
        strncpy(res[i], firstOccurence, sizeOfLink);
        res[i][sizeOfLink] = '\0';
    }

    free(indexs);
    return res;
}

char *scrapPage(char *name, char *url, int versioning) {
    char *path = myAlloc(sizeof(char) * 100, DEFAULT_ALLOC_ERR_MSG);
    char directory[80];
    FILE *file = NULL;
    struct tm tm;

    strcpy(path, name);
    if(versioning == VERSIONING_ON) {
        strcat(path, "/");
        strcat(path, getDatetimeFormated(&tm));
    }
    strcat(path, "/index.html");

    if (fileExist(path) == EXIT_FAILURE) {
        strcpy(directory, name);
        if(versioning == VERSIONING_ON) {
            strcat(directory, "/");
            strcat(directory, getDatetimeFormated(&tm));
        }
        createDirectory(directory);
        file = fopen(path, "w");
        httpGet(url, (void *)file);
        printf("File created\n");
        fclose(file);
        return path;
    }

    printf("File already exist\n");
    return NULL;
}
