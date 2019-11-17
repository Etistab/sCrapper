/*
** Filename : main.c
**
** Made by  : Baptiste LEGO
**
** Description  : main file // entry point of the application
*/

#include "include/common.h"

int main(int argc, char **argv) {
    const char *type[1] = {"text/html"};
    int versioning = VERSIONING_ON;

    scrapWebsite("google", "https://www.google.com", 0, versioning, type, 1);

    return 0;
}
